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

#ifndef SAMPGDK_CORE_H
#define SAMPGDK_CORE_H

#include <stdarg.h>

#include <sampgdk/bool.h>
#include <sampgdk/export.h>
#include <sampgdk/sdk.h>

SAMPGDK_API(int, sampgdk_init(void **plugin_data));
SAMPGDK_API(int, sampgdk_init_plugin(void *plugin, void **plugin_data));

SAMPGDK_API(int, sampgdk_cleanup(void));
SAMPGDK_API(int, sampgdk_cleanup_plugin(void *plugin));

SAMPGDK_API(void, sampgdk_logprintf(const char *format, ...));
SAMPGDK_API(void, sampgdk_vlogprintf(const char *format, va_list args));

SAMPGDK_API(int, sampgdk_register_plugin(void *plugin));
SAMPGDK_API(int, sampgdk_unregister_plugin(void *plugin));

SAMPGDK_API(void *, sampgdk_get_plugin_handle(void *symbol));
SAMPGDK_API(void *, sampgdk_get_plugin_symbol(void *plugin, const char *name));

SAMPGDK_API(void, sampgdk_process_timers(void));
SAMPGDK_API(void, sampgdk_process_plugin_timers(void *plugin));

SAMPGDK_API(const AMX_NATIVE_INFO *, sampgdk_get_natives(void));
SAMPGDK_API(int, sampgdk_get_num_natives(void));

SAMPGDK_API(AMX_NATIVE, sampgdk_find_native(const char *name));
SAMPGDK_API(cell, sampgdk_call_native(AMX_NATIVE native, cell *params));
SAMPGDK_API(cell, sampgdk_invoke_native(AMX_NATIVE native, const char *format, ...));

typedef bool (SAMPGDK_CALL *sampgdk_public_hook)(AMX *amx, const char *name, cell *params);

SAMPGDK_API(sampgdk_public_hook, sampgdk_get_public_hook(void));
SAMPGDK_API(void, sampgdk_set_public_hook(sampgdk_public_hook hook));

#endif /* !SAMPGDK_CORE_H */
