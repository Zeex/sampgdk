/* Copyright (C) 2011-2013 Zeex
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

#include <sampgdk/amx.h>
#include <sampgdk/bool.h>
#include <sampgdk/export.h>

/* Deprecated. Use sampgdk_init() or sampgdk_init_plugin() instead. */
SAMPGDK_DEPRECATED(SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_initialize(void **data));
/* Deprecated. Use sampgdk_cleanup() or sampgdk_cleanup_plugin() instead. */
SAMPGDK_DEPRECATED(SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_finalize(void));

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_init(void **data);
SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_init_plugin(void *plugin, void **data);
SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_cleanup(void);
SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_cleanup_plugin(void *plugin);

SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_register_plugin(void *plugin);
SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_unregister_plugin(void *plugin);

SAMPGDK_EXPORT void **SAMPGDK_CALL sampgdk_get_plugin_data(void);
SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_handle(void *symbol);
SAMPGDK_EXPORT void *SAMPGDK_CALL sampgdk_get_plugin_symbol(void *plugin, const char *name);

/* Deprecated. Use sampgdk_init() or sampgdk_init_plugin() instead. */
#define sampgdk_initialize_plugin sampgdk_initialize

SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_timers(void);
SAMPGDK_EXPORT void SAMPGDK_CALL sampgdk_process_plugin_timers(void *plugin);

SAMPGDK_EXPORT const AMX_NATIVE_INFO *SAMPGDK_CALL sampgdk_get_natives();
SAMPGDK_EXPORT int SAMPGDK_CALL sampgdk_num_natives(void);

typedef void (*sampgdk_logprintf_t)(const char *format, ...);
SAMPGDK_EXPORT sampgdk_logprintf_t sampgdk_logprintf;

typedef void (*sampgdk_vlogprintf_t)(const char *format, va_list args);
SAMPGDK_EXPORT sampgdk_vlogprintf_t sampgdk_vlogprintf;

#ifdef __cplusplus
  #include <sampgdk/core.hpp>
#endif

#endif /* !SAMPGDK_CORE_H */
