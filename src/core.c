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
#include "internal/plugin.h"
#include "internal/timer.h"

static void init(void **plugin_data) {
  int error;

  sampgdk_logprintf_impl = plugin_data[PLUGIN_DATA_LOGPRINTF];
  sampgdk_amx_api_ptr = plugin_data[PLUGIN_DATA_AMX_EXPORTS];

  error = sampgdk_module_init();
  if (error  < 0) {
    sampgdk_log_error_code(error);
  }
}

static int init_plugin(void *plugin, void **plugin_data) {
  int error;

  if (sampgdk_plugin_get_list() == NULL) {
    init(plugin_data);
  }

  error = sampgdk_plugin_register(plugin);
  if (error < 0) {
    sampgdk_log_error_code(error);
  }

  return error;
}

static void cleanup(void) {
  sampgdk_module_cleanup();
}

static void cleanup_plugin(void *plugin) {
  int error;

  error = sampgdk_plugin_unregister(plugin);
  if (error < 0) {
    sampgdk_log_error_code(error);
  }

  if (sampgdk_plugin_get_list() == NULL) {
    cleanup();
  }
}

SAMPGDK_API(unsigned int, sampgdk_Supports(void)) {
  return SUPPORTS_VERSION;
}

SAMPGDK_API(void *, sampgdk_GetPluginHandle(void *address)) {
  return sampgdk_plugin_get_handle(address);
}

SAMPGDK_API(bool, sampgdk_Load(void *plugin, void **ppData)) {
  return init_plugin(plugin, ppData) >= 0;
}

SAMPGDK_API(void, sampgdk_Unload(void *plugin)) {
  cleanup_plugin(plugin);
}

SAMPGDK_API(void, sampgdk_ProcessTick(void *plugin)) {
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
