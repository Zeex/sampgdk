/* Copyright (C) 2011-2014 Zeex
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
#include "utils.h"

#define _SAMPGDK_AMXHOOKS_MAX_PUBLIC_NAME 32

static AMX *_sampgdk_amxhooks_main_amx;
static struct sampgdk_array _sampgdk_amxhooks_found_publics;

#define _SAMPGDK_AMXHOOKS_FUNC_LIST(C) \
  C(Register) \
  C(FindPublic) \
  C(Exec) \
  C(Callback) \
  C(Allot)

#define _SAMPGDK_AMXHOOKS_FUNC_LIST_2(C) \
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
  if (error != AMX_ERR_NONE || index == AMX_EXEC_GDK) {
    return -1;
  }

  return index;
}

static int AMXAPI _sampgdk_amxhooks_Register(AMX *amx,
                                             const AMX_NATIVE_INFO *nativelist,
                                             int number) {
  int i;
  int error;
  AMX_HEADER *hdr;
  AMX_FUNCSTUBNT *natives;

  sampgdk_log_trace("amx_Register(%p, %p, %d)", amx, nativelist, number);

  sampgdk_hook_remove(_sampgdk_amxhooks_Register_hook);

  hdr = (AMX_HEADER *)amx->base;
  natives = (AMX_FUNCSTUBNT *)(amx->base + hdr->natives);

  if (amx_FindNative(amx, "funcidx", &i) == AMX_ERR_NONE) {
    natives[i].address = (ucell)_sampgdk_amxhooks_funcidx;
  }

  for (i = 0; nativelist[i].name != 0 && (i < number || number == -1); i++) {
    sampgdk_log_info("Registering native: %s @ %p", nativelist[i].name,
                                                    nativelist[i].func);
    sampgdk_native_register(nativelist[i].name, nativelist[i].func);
  }

  error = amx_Register(amx, nativelist, number);
  sampgdk_hook_install(_sampgdk_amxhooks_Register_hook);

  return error;
}

/* The SA-MP server always makes a call to amx_FindPublic() before executing
 * a callback and calls amx_Exec() depending on the returned error code.
 * This allows us to force it to call amx_Exec() regardless of whether the
 * public function was previously found by returning AMX_ERR_NONE from our
 * version of amx_FindPublic().
 *
 * Although this system works in most cases it's obviously very fragile, and
 * if they suddenly decide to change something in this find-exec scheme (e.g.
 * by caching callback indices), the whole thing willl stop working. So be
 * prepared for bugs!
 */
static int AMXAPI _sampgdk_amxhooks_FindPublic(AMX *amx,
                                               const char *name,
                                               int *index) {
  bool proceed;
  int error;
  int found = *index;

  sampgdk_log_trace("amx_FindPublic(%p, %s, %p)", amx, name, index);

  sampgdk_hook_remove(_sampgdk_amxhooks_FindPublic_hook);

  error = amx_FindPublic(amx, name, &found);

  /* We are interested in calling publics against two AMX instances:
   * - the main AMX (the gamemode)
   * - the fake AMX (this is needed for HTTP() to work)
   */
  if (amx == _sampgdk_amxhooks_main_amx ||
      amx == sampgdk_fakeamx_amx()) {
    char name_trunc[_SAMPGDK_AMXHOOKS_MAX_PUBLIC_NAME];
    bool append;

    sampgdk_strcpy(name_trunc, name, sizeof(name_trunc));

    sampgdk_log_trace("New publics stack entry: %s", name_trunc);
    append = sampgdk_array_append(&_sampgdk_amxhooks_found_publics, name_trunc);

    if (append < 0) {
      error = AMX_ERR_MEMORY;
    } else if (error != AMX_ERR_NONE) {
      error = AMX_ERR_NONE;
      found = AMX_EXEC_GDK;
    }
  }

  if (error == AMX_ERR_NONE) {
    *index = found;
  }

  sampgdk_hook_install(_sampgdk_amxhooks_FindPublic_hook);

  return error;
}

static int AMXAPI _sampgdk_amxhooks_Exec(AMX *amx, cell *retval, int index) {
  int paramcount;
  int error = AMX_ERR_NONE;
  bool do_exec = true;
  bool do_cleanup = false;

  sampgdk_log_trace("amx_Exec(%p, %p, %d), paramcount = %d", amx, retval, index,
                                                             amx->paramcount);

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
      sampgdk_log_info("Main AMX instance: %p", amx);
      sampgdk_callback_invoke(amx, "OnGameModeInit", paramcount, retval);
    }
  } else if (index != AMX_EXEC_CONT && (amx == _sampgdk_amxhooks_main_amx ||
                                        amx == sampgdk_fakeamx_amx())) {
    if (_sampgdk_amxhooks_found_publics.count > 0) {
      char name[_SAMPGDK_AMXHOOKS_MAX_PUBLIC_NAME];

      sampgdk_strcpy(name, sampgdk_array_last(&_sampgdk_amxhooks_found_publics),
                     sizeof(name));
      sampgdk_array_remove_last(&_sampgdk_amxhooks_found_publics);

      sampgdk_log_trace("Invoking callback: %s", name);
      do_exec = sampgdk_callback_invoke(amx, name, paramcount, retval);

      if (retval != NULL) {
        sampgdk_log_trace("%s returned %d", name, *retval);
      }
    } else {
      sampgdk_log_warning("Unexpected public call, index = %d", index);
    }
  }

  sampgdk_hook_remove(_sampgdk_amxhooks_Exec_hook);
  sampgdk_hook_install(_sampgdk_amxhooks_Callback_hook);

  if (do_exec) {
    sampgdk_log_trace("Calling real amx_Exec()");
    amx->paramcount = paramcount;
    error = amx_Exec(amx, retval, index);
  }

  /* Suppress the error and also let the other plugin(s) know that we
   * handle the cleanup (see below).
   */
  if (error == AMX_ERR_INDEX && index == AMX_EXEC_GDK) {
    error = AMX_ERR_NONE;
    do_cleanup = true;
  }

  /* Someone has to clean things up if amx_Exec() didn't run after all.
   */
  if (!do_exec || do_cleanup) {
    sampgdk_log_trace("Doing parameter cleanup");
    amx->paramcount = 0;
    amx->stk += paramcount * sizeof(cell);
  }

  sampgdk_hook_remove(_sampgdk_amxhooks_Callback_hook);
  sampgdk_hook_install(_sampgdk_amxhooks_Exec_hook);

  return error;
}

static int AMXAPI _sampgdk_amxhooks_Callback(AMX *amx,
                                             cell index,
                                             cell *result,
                                             cell *params) {
  int error;

  sampgdk_log_trace("amx_Callback(%p, %d, %p, %p)", amx, index, result, params);

  sampgdk_hook_remove(_sampgdk_amxhooks_Callback_hook);
  sampgdk_hook_install(_sampgdk_amxhooks_Exec_hook);

  /* Prevent the default AMX callback from replacing SYSREQ.C instructions
   * with SYSREQ.D.
   */
  amx->sysreq_d = 0;

  error = amx_Callback(amx, index, result, params);

  sampgdk_hook_remove(_sampgdk_amxhooks_Exec_hook);
  sampgdk_hook_install(_sampgdk_amxhooks_Callback_hook);

  return error;
}

static int AMXAPI _sampgdk_amxhooks_Allot(AMX *amx,
                                          int cells,
                                          cell *amx_addr,
                                          cell **phys_addr) {
  int error;

  sampgdk_log_trace("amx_Allot(%p, %d, %p, %p)", amx, cells, amx_addr,
                                                 phys_addr);

  sampgdk_hook_remove(_sampgdk_amxhooks_Allot_hook);

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
    error = amx_Allot(amx, cells, amx_addr, phys_addr);
  }

  /* If called against the fake AMX and failed to allocate the requested
   * amount of space, grow the heap and try again.
   */
  if (error == AMX_ERR_MEMORY && amx == sampgdk_fakeamx_amx()) {
    cell new_size = ((amx->hea + STKMARGIN) / sizeof(cell)) + cells + 2;
    cell resize;

    sampgdk_log_info("Growing fake AMX heap to %d bytes = %d = %d", new_size);
    resize = sampgdk_fakeamx_resize_heap(new_size);

    if (resize >= 0) {
      error = amx_Allot(amx, cells, amx_addr, phys_addr);
    }
  }

  sampgdk_hook_install(_sampgdk_amxhooks_Allot_hook);

  return error;
}

static int _sampgdk_amxhooks_create(void) {
  #define _SAMPGDK_AMXHOOKS_CREATE_HOOK(name) \
    if ((_sampgdk_amxhooks_##name##_hook = \
        sampgdk_hook_new(sampgdk_amx_api_ptr->name, \
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

static void _sampgdk_amxhooks_install(void) {
  #define _SAMPGDK_AMXHOOKS_INSTALL_HOOK(name) \
    sampgdk_hook_install(_sampgdk_amxhooks_##name##_hook);
  _SAMPGDK_AMXHOOKS_FUNC_LIST_2(_SAMPGDK_AMXHOOKS_INSTALL_HOOK)
  #undef _SAMPGDK_AMXHOOKS_INSTALL_HOOK
}

static void _sampgdk_amxhooks_remove(void) {
  #define _SAMPGDK_AMXHOOKS_REMOVE_HOOK(name) \
    sampgdk_hook_remove(_sampgdk_amxhooks_##name##_hook);
  _SAMPGDK_AMXHOOKS_FUNC_LIST_2(_SAMPGDK_AMXHOOKS_REMOVE_HOOK)
  #undef _SAMPGDK_AMXHOOKS_REMOVE_HOOK
}

SAMPGDK_MODULE_INIT(amxhooks) {
  int error;

  error = sampgdk_array_new(&_sampgdk_amxhooks_found_publics,
                            1,
                            _SAMPGDK_AMXHOOKS_MAX_PUBLIC_NAME);
  if (error < 0) {
    return error;
  }

  error = _sampgdk_amxhooks_create();
  if (error < 0) {
    _sampgdk_amxhooks_destroy();
    return error;
  }

  _sampgdk_amxhooks_install();
  return 0;
}

SAMPGDK_MODULE_CLEANUP(amxhooks) {
  _sampgdk_amxhooks_remove();
  _sampgdk_amxhooks_destroy();
}
