/* Copyright (C) 2011-2019 Zeex
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
#include <string.h>

#include <sampgdk/bool.h>
#include <sampgdk/core.h>
#include <sampgdk/sdk.h>
#include <sampgdk/version.h>

#include "internal/amx.h"
#include "internal/init.h"
#include "internal/log.h"
#include "internal/logprintf.h"
#include "internal/plugin.h"
#include "internal/timer.h"

#undef sampgdk_Load
#undef sampgdk_Unload
#undef sampgdk_ProcessTick

#ifdef _MSC_VER
  #include <intrin.h>
  #define _SAMPGDK_RETURN_ADDRESS() _ReturnAddress()
#else
  #define _SAMPGDK_RETURN_ADDRESS() __builtin_return_address(0)
#endif

#ifdef SAMPGDK_EMBEDDED
  #define _SAMPGDK_CALLER_HANDLE() \
    sampgdk_plugin_get_handle(((void *)_sampgdk_init))
#else
  #define _SAMPGDK_CALLER_HANDLE() \
    sampgdk_plugin_get_handle(_SAMPGDK_RETURN_ADDRESS())
#endif

static void _sampgdk_init(void **plugin_data) {
  int error;

  sampgdk_logprintf_impl = (logprintf_t)plugin_data[PLUGIN_DATA_LOGPRINTF];
  sampgdk_amx_api =
      (struct sampgdk_amx_api *)plugin_data[PLUGIN_DATA_AMX_EXPORTS];

  error = sampgdk_module_init();
  if (error  < 0) {
    sampgdk_log_error("Initialization failed: %s", strerror(-error));
  }

  sampgdk_log_info("GDK version: " SAMPGDK_VERSION_STRING);
}

static int _sampgdk_init_plugin(void *plugin, void **plugin_data) {
  int error;
  int num_plugins;

  assert(plugin != NULL);

  (void)sampgdk_plugin_get_plugins(&num_plugins);
  if (num_plugins == 0) {
    _sampgdk_init(plugin_data);
  }

  error = sampgdk_plugin_register(plugin);
  if (error < 0) {
    sampgdk_log_error("Error registering plugin: %s", strerror(-error));
  }

  return error;
}

static void _sampgdk_cleanup(void) {
  sampgdk_module_cleanup();
}

static void _sampgdk_cleanup_plugin(void *plugin) {
  int error;
  int num_plugins;

  assert(plugin != NULL);

  error = sampgdk_plugin_unregister(plugin);
  if (error < 0) {
    sampgdk_log_error("Error unregistering plugin: %s", strerror(-error));
  }

  (void)sampgdk_plugin_get_plugins(&num_plugins);
  if (num_plugins == 0) {
    _sampgdk_cleanup();
  }
}

SAMPGDK_API(unsigned int, sampgdk_Supports(void)) {
  return SUPPORTS_VERSION;
}

SAMPGDK_API(bool, sampgdk_Load(void **ppData, sampgdk_hidden_t hidden)) {
  return _sampgdk_init_plugin(_SAMPGDK_CALLER_HANDLE(), ppData) >= 0;
}

SAMPGDK_API(void, sampgdk_Unload(sampgdk_hidden_t hidden)) {
  _sampgdk_cleanup_plugin(_SAMPGDK_CALLER_HANDLE());
}

SAMPGDK_API(void, sampgdk_ProcessTick(sampgdk_hidden_t hidden)) {
  sampgdk_timer_process_timers(_SAMPGDK_CALLER_HANDLE());
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
