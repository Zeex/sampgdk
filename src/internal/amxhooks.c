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
static char _sampgdk_amxhooks_public_name[_SAMPGDK_AMXHOOKS_MAX_PUBLIC_NAME];

#define _SAMPGDK_AMXHOOKS_LIST(C) \
  C(Register) \
  C(FindPublic) \
  C(Exec) \
  C(Callback) \
  C(Allot)

#define _SAMPGDK_AMXHOOKS_LIST_2(C) \
  C(Register) \
  C(FindPublic) \
  C(Exec) \
  C(Allot)

#define _SAMPGDK_AMXHOOKS_DEFINE_HOOK(name) \
  static sampgdk_hook_t _sampgdk_amxhooks_##name##_hook;
_SAMPGDK_AMXHOOKS_LIST(_SAMPGDK_AMXHOOKS_DEFINE_HOOK)
#undef _SAMPGDK_AMXHOOKS_DEFINE_HOOK

/* The "funcidx" native uses amx_FindPublic() to get public function index
 * but our FindPublic always succeeds regardless of public existence, so
 * here's a fixed version.
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
  if (error != AMX_ERR_NONE || (error == AMX_ERR_NONE &&
      index == AMX_EXEC_GDK)) {
    return -1;
  }

  return index;
}

static void _sampgdk_amxhooks_hook_native(AMX *amx,
                                          const char *name,
                                          AMX_NATIVE address) {
  int index;
  AMX_HEADER *hdr = (AMX_HEADER *)amx->base;
  AMX_FUNCSTUBNT *natives = (AMX_FUNCSTUBNT *)(amx->base + hdr->natives);

  if (amx_FindNative(amx, name, &index) == AMX_ERR_NONE) {
    natives[index].address = (ucell)address;
  }
}

static int AMXAPI _sampgdk_amxhooks_Register(AMX *amx,
                                             const AMX_NATIVE_INFO *nativelist,
                                             int number) {
  int i;
  int error;

  sampgdk_hook_remove(_sampgdk_amxhooks_Register_hook);

  _sampgdk_amxhooks_hook_native(amx, "funcidx", _sampgdk_amxhooks_funcidx);

  for (i = 0; nativelist[i].name != 0 && (i < number || number == -1); i++) {
    sampgdk_native_register(nativelist[i].name, nativelist[i].func);
  }

  error = amx_Register(amx, nativelist, number);
  sampgdk_hook_install(_sampgdk_amxhooks_Register_hook);

  return error;
}

/* The SA-MP server always makes a call to amx_FindPublic() before executing
 * a callback and depending the return value it may or may not run amx_Exec().
 *
 * In order to have amx_Exec() called for *all* publics i.e. regardless of
 * whether they actually exist in the gamemode, we can simply always return
 * success.
 *
 * Now you might be thinking "OK, that sounds like it should work", but there
 * is one fundamental flaw in this "algorithm": if the caller didn't bother
 * to initialize the retval variable prior to the call to amx_Exec(), which
 * makes perfect sense, it will end up with random garbage and you might get
 * unexpected results.
 */
static int AMXAPI _sampgdk_amxhooks_FindPublic(AMX *amx,
                                               const char *name,
                                               int *index) {
  bool proceed;
  int error;

  sampgdk_hook_remove(_sampgdk_amxhooks_FindPublic_hook);

  /* We are interested in calling publics against two AMX instances:
   * - the main AMX (the gamemode)
   * - the fake AMX (this is needed for HTTP() to work)
   */
  proceed = (amx == _sampgdk_amxhooks_main_amx ||
             amx == sampgdk_fakeamx_amx());
  error = amx_FindPublic(amx, name, index);

  if (proceed) {
    sampgdk_strcpy(_sampgdk_amxhooks_public_name,
                   name,
                   sizeof(_sampgdk_amxhooks_public_name));
    if (error != AMX_ERR_NONE) {
      error = AMX_ERR_NONE;
      *index = AMX_EXEC_GDK;
    }
  }

  sampgdk_hook_install(_sampgdk_amxhooks_FindPublic_hook);

  return error;
}

static int AMXAPI _sampgdk_amxhooks_Exec(AMX *amx, cell *retval, int index) {
  bool proceed = true;
  int error = AMX_ERR_NONE;

  /* Since filterscripts don't use main() we can assume that the AMX
   * that executes main() is indeed the main AMX i.e. the gamemode.
   */
  if (index == AMX_EXEC_MAIN) {
    /* This extra check is needed in order to stop OnGameModeInit()
     * from being called twice in a row after a gmx.
     */
    if (_sampgdk_amxhooks_main_amx != amx && amx != NULL) {
      sampgdk_callback_invoke(amx, "OnGameModeInit", retval);
      _sampgdk_amxhooks_main_amx = amx;
    }
  } else {
    if (index != AMX_EXEC_CONT
        && (amx == _sampgdk_amxhooks_main_amx || amx == sampgdk_fakeamx_amx())) {
      proceed = sampgdk_callback_invoke(amx,
                                        _sampgdk_amxhooks_public_name,
                                        retval);
    }
  }

  sampgdk_hook_remove(_sampgdk_amxhooks_Exec_hook);
  sampgdk_hook_install(_sampgdk_amxhooks_Callback_hook);

  if (proceed && index != AMX_EXEC_GDK) {
    error = amx_Exec(amx, retval, index);
  } else {
    amx->stk += amx->paramcount * sizeof(cell);
  }

  amx->paramcount = 0;

  sampgdk_hook_remove(_sampgdk_amxhooks_Callback_hook);
  sampgdk_hook_install(_sampgdk_amxhooks_Exec_hook);

  return error;
}

static int AMXAPI _sampgdk_amxhooks_Callback(AMX *amx,
                                             cell index,
                                             cell *result,
                                             cell *params) {
  int error;

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

  sampgdk_hook_remove(_sampgdk_amxhooks_Allot_hook);

  /* There is a bug in amx_Allot() where it returns success even though
   * there's no enough space on the heap:
   *
   * if (amx->stk - amx->hea - cells*sizeof(cell) < STKMARGIN)
   *   return AMX_ERR_MEMORY;
   *
   * The expression on the left is always positive because of the conversion
   * to size_t, which is unsigned.
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
    if (sampgdk_fakeamx_resize_heap(new_size) >= 0) {
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
                         (void*)_sampgdk_amxhooks_##name)) == NULL) \
      goto no_memory;
  _SAMPGDK_AMXHOOKS_LIST(_SAMPGDK_AMXHOOKS_CREATE_HOOK)
  return 0;
no_memory:
  return -ENOMEM;
  #undef _SAMPGDK_AMXHOOKS_CREATE_HOOK
}

static void _sampgdk_amxhooks_destroy(void) {
  #define _SAMPGDK_AMXHOOKS_DESTROY_HOOK(name) \
    sampgdk_hook_free(_sampgdk_amxhooks_##name##_hook);
  _SAMPGDK_AMXHOOKS_LIST(_SAMPGDK_AMXHOOKS_DESTROY_HOOK)
  #undef _SAMPGDK_AMXHOOKS_DESTROY_HOOK
}

static void _sampgdk_amxhooks_install(void) {
  #define _SAMPGDK_AMXHOOKS_INSTALL_HOOK(name) \
    sampgdk_hook_install(_sampgdk_amxhooks_##name##_hook);
  _SAMPGDK_AMXHOOKS_LIST_2(_SAMPGDK_AMXHOOKS_INSTALL_HOOK)
  #undef _SAMPGDK_AMXHOOKS_INSTALL_HOOK
}

static void _sampgdk_amxhooks_remove(void) {
  #define _SAMPGDK_AMXHOOKS_REMOVE_HOOK(name) \
    sampgdk_hook_remove(_sampgdk_amxhooks_##name##_hook);
  _SAMPGDK_AMXHOOKS_LIST_2(_SAMPGDK_AMXHOOKS_REMOVE_HOOK)
  #undef _SAMPGDK_AMXHOOKS_REMOVE_HOOK
}

SAMPGDK_MODULE_INIT(amxhooks) {
  int error;

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
