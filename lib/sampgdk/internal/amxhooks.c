/* Copyright (C) 2011-2018 Zeex
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <assert.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <sampgdk/bool.h>
#include <sampgdk/core.h>
#include <sampgdk/sdk.h>

#include "amx.h"
#include "array.h"
#include "callback.h"
#include "fakeamx.h"
#include "init.h"
#include "log.h"
#include "native.h"
#include "param.h"
#include "hook.h"

static AMX *_sampgdk_amxhooks_main_amx;

#define _SAMPGDK_AMXHOOKS_FUNC_LIST(C) \
  C(Register) \
  C(FindPublic) \
  C(Exec) \
  C(Allot)

#define _SAMPGDK_AMXHOOKS_DEFINE_HOOK(name) \
  static sampgdk_hook_t _sampgdk_amxhooks_##name##_hook;
_SAMPGDK_AMXHOOKS_FUNC_LIST(_SAMPGDK_AMXHOOKS_DEFINE_HOOK)
#undef _SAMPGDK_AMXHOOKS_DEFINE_HOOK

/* The "funcidx" native uses amx_FindPublic() to get the public function's
 * index but our FindPublic always returns success regardless of the actual
 * result. So here's a fixed version.
 *
 * Thanks to Incognito for finding this bug!
 */
static cell AMX_NATIVE_CALL _sampgdk_amxhooks_funcidx(AMX *amx, cell *params) {
  char *funcname;
  int index;
  int error;

  amx_StrParam(amx, params[1], funcname);
  if (funcname == NULL) {
    return -1;
  }

  error = amx_FindPublic(amx, funcname, &index);
  if (error != AMX_ERR_NONE || index <= AMX_EXEC_GDK) {
    return -1;
  }

  return index;
}

static int AMXAPI _sampgdk_amxhooks_Register(AMX *amx,
                                             const AMX_NATIVE_INFO *nativelist,
                                             int number) {
  int i;
  int count = 0;
  AMX_HEADER *hdr;
  AMX_FUNCSTUBNT *natives;

  sampgdk_log_debug("amx_Register(%p, %p, %d)", amx, nativelist, number);

  hdr = (AMX_HEADER *)amx->base;
  natives = (AMX_FUNCSTUBNT *)(amx->base + hdr->natives);

  if (amx_FindNative(amx, "funcidx", &i) == AMX_ERR_NONE) {
    natives[i].address = (ucell)_sampgdk_amxhooks_funcidx;
  }

  for (i = 0; (i < number || number == -1) && nativelist[i].name != NULL; i++) {
    if (sampgdk_native_register(nativelist[i].name, nativelist[i].func) >= 0) {
      sampgdk_log_debug("Registered native: %s @ %p",
                        nativelist[i].name, nativelist[i].func);
      count++;
    }
  }

  if (count > 0) {
    sampgdk_log_info("Registered %d natives", count);
  }

  return SAMPGDK_HOOK_CALL_CC(_sampgdk_amxhooks_Register_hook, int, AMXAPI,
                              (AMX *, const AMX_NATIVE_INFO *, int), (amx, nativelist, number));
}

static int AMXAPI _sampgdk_amxhooks_FindPublic(AMX *amx,
                                               const char *name,
                                               int *index) {
  int error;
  int index_internal;
  int index_real;

  sampgdk_log_debug("amx_FindPublic(%p, \"%s\", %p)", amx, name, index);

  error = SAMPGDK_HOOK_CALL_CC(_sampgdk_amxhooks_FindPublic_hook, int, AMXAPI,
                               (AMX *, const char *, int *), (amx, name, index));
  sampgdk_log_debug("amx_FindPublic returned %d", error);

  /* We are interested in intercepting public calls against the following
   * AMX instances:
   *
   * - the main AMX (the gamemode)
   * - the fake AMX (this is needed for HTTP() to work)
   */
  if (amx != _sampgdk_amxhooks_main_amx &&
      amx != sampgdk_fakeamx_amx()) {
    return error;
  }

  /* If the public was really found (and I mean REALLY) there's no need
   * to mess with the index.
   */
  if (error == AMX_ERR_NONE && *index >= 0) {
    return AMX_ERR_NONE;
  }

  /* OK, this public officially doesn't exist. Register it in our internal
   * callback table and return success. The table will allow us to keep track
   * of forged publics in amx_Exec().
   */
  index_internal = sampgdk_callback_register(name, NULL);
  index_real = AMX_EXEC_GDK - index_internal;

  if (index_internal < 0) {
    sampgdk_log_error("Error registering callback: %s",
                      strerror(-index_internal));
  } else if (error == AMX_ERR_NONE && *index < 0) {
    /* If there are other plugins running they better return the same
     * index as we do. Otherwise it would be a total mess and we can't
     * let that happen.
     */
    if (*index != index_real) {
      error = AMX_ERR_NOTFOUND;
      sampgdk_log_warning("Index mismatch for %s (%d != %d)",
                          name, *index, index_real);
    }
  } else if (error != AMX_ERR_NONE) {
    error = AMX_ERR_NONE, *index = index_real;
    sampgdk_log_debug("Registered callback: %s, index = %d", name, *index);
  }

  return error;
}

static int AMXAPI _sampgdk_amxhooks_Exec(AMX *amx, cell *retval, int index) {
  int paramcount;
  int error = AMX_ERR_NONE;
  bool do_exec = true;
  bool do_cleanup = false;

  sampgdk_log_debug("amx_Exec(%p, %p, %d), paramcount = %d, stk = %d",
      amx, retval, index, amx->paramcount, amx->stk);

  /* We have to reset amx->paramcount at this point so if the callback
   * itself calls amx_Exec() it won't pop our arguments off the stack.
   */
  paramcount = amx->paramcount;
  amx->paramcount = 0;

  /* Since filterscripts don't use main() we can assume that the AMX
   * that executes main() is indeed the main AMX i.e. the gamemode.
   */
  if (index == AMX_EXEC_MAIN) {
    /* This extra check is needed in order to stop OnGameModeInit()
     * from being called twice in a row after a gmx.
     */
    if (amx != NULL && _sampgdk_amxhooks_main_amx != amx) {
      _sampgdk_amxhooks_main_amx = amx;

      sampgdk_log_info("Found main AMX, callbacks should work now");
      sampgdk_log_debug("Main AMX instance: %p", amx);

      /* For some odd reason OnGameModeInit() is called before main().
       * Normally callbacks are handled below but this creates an exception.
       */
      sampgdk_callback_invoke(amx, "OnGameModeInit", paramcount, retval);
    }
  } else if (index != AMX_EXEC_CONT && (amx == _sampgdk_amxhooks_main_amx ||
                                        amx == sampgdk_fakeamx_amx())) {
    char *name = NULL;

    if (index <= AMX_EXEC_GDK) {
      sampgdk_callback_get(AMX_EXEC_GDK - index, &name);
    } else {
      AMX *main_amx = _sampgdk_amxhooks_main_amx;
      AMX_FUNCSTUBNT *publics = (AMX_FUNCSTUBNT *)(main_amx->base +
          ((AMX_HEADER *)main_amx->base)->publics);
      name = (char *)(publics[index].nameofs + amx->base);
    }

    if (name != NULL) {
      do_exec = sampgdk_callback_invoke(amx, name, paramcount, retval);
    } else {
      sampgdk_log_warning("Unknown callback, index = %d", index);
    }
  }

  if (do_exec) {
    amx->paramcount = paramcount;
    error = SAMPGDK_HOOK_CALL_CC(_sampgdk_amxhooks_Exec_hook, int, AMXAPI,
                                 (AMX *, cell *, int), (amx, retval, index));
    sampgdk_log_debug("amx_Exec returned %d", error);
  }

  /* Suppress the error and also let the other plugin(s) know that we
   * handle the cleanup (see below).
   */
  if (error == AMX_ERR_INDEX && index <= AMX_EXEC_GDK) {
    error = AMX_ERR_NONE;
    do_cleanup = true;
  }

  /* Someone has to clean things up if amx_Exec() didn't run after all.
   */
  if (!do_exec || do_cleanup) {
    amx->paramcount = 0;
    amx->stk += paramcount * sizeof(cell);
    sampgdk_log_debug("Popped %d parameter(s), stk = %d", paramcount, amx->stk);
  }

  return error;
}

static int AMXAPI _sampgdk_amxhooks_Allot(AMX *amx,
                                          int cells,
                                          cell *amx_addr,
                                          cell **phys_addr) {
  int error;

  sampgdk_log_debug("amx_Allot(%p, %d, %p, %p)", amx, cells, amx_addr,
                                                 phys_addr);

  /* There is a bug in amx_Allot() where it returns success even though
   * there's not enough space on the heap:
   *
   * if (amx->stk - amx->hea - cells*sizeof(cell) < STKMARGIN)
   *   return AMX_ERR_MEMORY;
   *
   * The expression on the left is always positive because of the conversion
   * to size_t, which is unsigned.
   *
   * The code below code should fix this.
   */
  #define STKMARGIN (cell)(16 * sizeof(cell))
  if ((size_t)amx->stk < (size_t)(amx->hea + cells*sizeof(cell) + STKMARGIN)) {
    error =  AMX_ERR_MEMORY;
  } else {
    error = SAMPGDK_HOOK_CALL_CC(_sampgdk_amxhooks_Allot_hook, int, AMXAPI,
                                 (AMX *, int, cell *, cell **), (amx, cells, amx_addr, phys_addr));
    sampgdk_log_debug("amx_Allot returned %d", error);
  }

  /* If called against the fake AMX and failed to allocate the requested
   * amount of space, grow the heap and try again.
   */
  if (error == AMX_ERR_MEMORY && amx == sampgdk_fakeamx_amx()) {
    cell new_size = ((amx->hea + STKMARGIN) / sizeof(cell)) + cells + 2;
    cell resize;

    sampgdk_log_debug("Growing fake AMX heap to %d bytes = %d = %d", new_size);
    resize = sampgdk_fakeamx_resize_heap(new_size);

    if (resize >= 0) {
      error = SAMPGDK_HOOK_CALL_CC(_sampgdk_amxhooks_Allot_hook, int, AMXAPI,
                                   (AMX *, int, cell *, cell **), (amx, cells, amx_addr, phys_addr));
    }
  }

  return error;
}

static int _sampgdk_amxhooks_create(void) {
  #define _SAMPGDK_AMXHOOKS_CREATE_HOOK(name) \
    if ((_sampgdk_amxhooks_##name##_hook = \
        sampgdk_hook_new((void *)sampgdk_amx_api->name, \
                         (void *)_sampgdk_amxhooks_##name)) == NULL) \
      goto no_memory;
  _SAMPGDK_AMXHOOKS_FUNC_LIST(_SAMPGDK_AMXHOOKS_CREATE_HOOK)
  return 0;
no_memory:
  return -ENOMEM;
  #undef _SAMPGDK_AMXHOOKS_CREATE_HOOK
}

static void _sampgdk_amxhooks_destroy(void) {
  #define _SAMPGDK_AMXHOOKS_DESTROY_HOOK(name) \
    sampgdk_hook_free(_sampgdk_amxhooks_##name##_hook);
  _SAMPGDK_AMXHOOKS_FUNC_LIST(_SAMPGDK_AMXHOOKS_DESTROY_HOOK)
  #undef _SAMPGDK_AMXHOOKS_DESTROY_HOOK
}

SAMPGDK_MODULE_INIT(amxhooks) {
  int error;

  error = _sampgdk_amxhooks_create();
  if (error < 0) {
    _sampgdk_amxhooks_destroy();
    return error;
  }

  return 0;
}

SAMPGDK_MODULE_CLEANUP(amxhooks) {
  _sampgdk_amxhooks_destroy();
}
