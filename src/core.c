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

#include <sampgdk/bool.h>
#include <sampgdk/core.h>
#include <sampgdk/sdk.h>

#include "internal/amx.h"
#include "internal/callback.h"
#include "internal/init.h"
#include "internal/log.h"
#include "internal/logprintf.h"
#include "internal/plugin.h"
#include "internal/timer.h"

#undef sampgdk_Load
#undef sampgdk_Unload
#undef sampgdk_ProcessTick

#ifdef _MSC_VER
  #define _SAMPGDK_RETURN_ADDRESS() _ReturnAddress()
#else
  #define _SAMPGDK_RETURN_ADDRESS() __builtin_return_address(0)
#endif

static void _sampgdk_init(void **plugin_data) {
  int error;

  sampgdk_logprintf_impl = plugin_data[PLUGIN_DATA_LOGPRINTF];
  sampgdk_amx_api_ptr = plugin_data[PLUGIN_DATA_AMX_EXPORTS];

  error = sampgdk_module_init();
  if (error  < 0) {
    sampgdk_log_error_code(error);
  }
}

static int _sampgdk_init_plugin(void *plugin, void **plugin_data) {
  int error;

  assert(plugin != NULL);

  if (sampgdk_plugin_count() == 0) {
    _sampgdk_init(plugin_data);
  }

  error = sampgdk_plugin_register(plugin);
  if (error < 0) {
    sampgdk_log_error_code(error);
  }

  sampgdk_callback_scan_plugin(plugin);

  return error;
}

static void _sampgdk_cleanup(void) {
  sampgdk_module_cleanup();
}

static void _sampgdk_cleanup_plugin(void *plugin) {
  int error;

  assert(plugin != NULL);

  error = sampgdk_plugin_unregister(plugin);
  if (error < 0) {
    sampgdk_log_error_code(error);
  }

  sampgdk_callback_forget_plugin(plugin);

  if (sampgdk_plugin_count() == 0) {
    _sampgdk_cleanup();
  }
}

SAMPGDK_API(unsigned int, sampgdk_Supports(void)) {
  return SUPPORTS_VERSION;
}

SAMPGDK_API(bool, sampgdk_Load(void **ppData, sampgdk_hidden_t hidden)) {
  void *plugin = sampgdk_plugin_get_handle(_SAMPGDK_RETURN_ADDRESS());
  return _sampgdk_init_plugin(plugin, ppData) >= 0;
}

SAMPGDK_API(void, sampgdk_Unload(sampgdk_hidden_t hidden)) {
  void *plugin = sampgdk_plugin_get_handle(_SAMPGDK_RETURN_ADDRESS());
  _sampgdk_cleanup_plugin(plugin);
}

SAMPGDK_API(void, sampgdk_ProcessTick(sampgdk_hidden_t hidden)) {
  void *plugin = sampgdk_plugin_get_handle(_SAMPGDK_RETURN_ADDRESS());
  sampgdk_timer_process_timers(plugin);
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
