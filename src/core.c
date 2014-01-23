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

#include <sampgdk/bool.h>
#include <sampgdk/core.h>
#include <sampgdk/sdk.h>

#include "internal/amx.h"
#include "internal/init.h"
#include "internal/log.h"
#include "internal/logprintf.h"
#include "internal/native.h"
#include "internal/plugin.h"
#include "internal/timer.h"

#ifdef _MSC_VER
  #define RETURN_ADDRESS() _ReturnAddress()
#else
  #define RETURN_ADDRESS() __builtin_return_address(0)
#endif

static sampgdk_public_hook public_hook;

static int init(void **plugin_data) {
  sampgdk_logprintf_impl = plugin_data[PLUGIN_DATA_LOGPRINTF];
  sampgdk_amx_api_ptr = plugin_data[PLUGIN_DATA_AMX_EXPORTS];
  return sampgdk_module_init();
}

static void cleanup(void) {
  sampgdk_module_cleanup();
}

SAMPGDK_API(int, sampgdk_init(void **plugin_data)) {
  void *handle = sampgdk_plugin_get_handle(RETURN_ADDRESS());
  return sampgdk_init_plugin(handle, plugin_data);
}

SAMPGDK_API(int, sampgdk_init_plugin(void *handle, void **plugin_data)) {
  if (sampgdk_plugin_get_list() == NULL) {
    int error = init(plugin_data);
    if (error < 0) {
      sampgdk_log_error_code(error);
      return error;
    }
  }
  return sampgdk_plugin_register(handle);
}

SAMPGDK_API(int, sampgdk_cleanup(void)) {
  void *handle = sampgdk_plugin_get_handle(RETURN_ADDRESS());
  return sampgdk_cleanup_plugin(handle);
}

SAMPGDK_API(int, sampgdk_cleanup_plugin(void *handle)) {
  int error = sampgdk_plugin_unregister(handle);
  if (sampgdk_plugin_get_list() == NULL) {
    cleanup();
  }
  return error;
}

SAMPGDK_API(void, sampgdk_logprintf(const char *format, ...)) {
  va_list args;
  va_start(args, format);
  sampgdk_do_vlogprintf(format, args);
  va_end(args);
}

SAMPGDK_API(void, sampgdk_vlogprintf(const char *format, va_list args)) {
  sampgdk_do_vlogprintf(format, args);
}

SAMPGDK_API(int, sampgdk_register_plugin(void *handle)) {
  return sampgdk_plugin_register(handle);
}

SAMPGDK_API(int, sampgdk_unregister_plugin(void *handle)) {
  return sampgdk_plugin_unregister(handle);
}

SAMPGDK_API(void *, sampgdk_get_plugin_handle(void *address)) {
  return sampgdk_plugin_get_handle(address);
}

SAMPGDK_API(void *, sampgdk_get_plugin_symbol(void *handle,
                                              const char *name)) {
  return sampgdk_plugin_get_symbol(handle, name);
}

SAMPGDK_API(void, sampgdk_process_timers(void)) {
  void *handle = sampgdk_plugin_get_handle(RETURN_ADDRESS());
  sampgdk_timer_process_timers(handle);
}

SAMPGDK_API(void, sampgdk_process_plugin_timers(void *handle)) {
  sampgdk_timer_process_timers(handle);
}

SAMPGDK_API(const AMX_NATIVE_INFO *, sampgdk_get_natives(void)) {
  return sampgdk_native_get_natives();
}

SAMPGDK_API(int, sampgdk_get_num_natives(void)) {
  return sampgdk_native_get_num_natives();
}

SAMPGDK_API(AMX_NATIVE, sampgdk_find_native(const char *name)) {
  return sampgdk_native_find(name);
}

SAMPGDK_API(cell, sampgdk_call_native(AMX_NATIVE native, cell *params)) {
  return sampgdk_native_call(native, params);
}

SAMPGDK_API(cell, sampgdk_invoke_native(AMX_NATIVE native,
                                        const char *format, ...)) {
  va_list args;
  cell retval;

  va_start(args, format);
  retval = sampgdk_native_invoke(native, format, args);
  va_end(args);

  return retval;
}

SAMPGDK_API(sampgdk_public_hook, sampgdk_get_public_hook(void)) {
  return public_hook;
}

SAMPGDK_API(void, sampgdk_set_public_hook(sampgdk_public_hook hook)) {
  public_hook = hook;
}
