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

/**
 * Registers the calling plugin for events and, if called for the
 * first time, initializes the library.
 */
SAMPGDK_API(int, sampgdk_init(void **plugin_data));

/**
 * Same as sampgdk_init() but explicitly specifies the plugin.
 */
SAMPGDK_API(int, sampgdk_init_plugin(void *plugin, void **plugin_data));

/**
 * Unregisters the calling plugin and, if this is the last remaining
 * plugin, it performs the final cleanup.
 */
SAMPGDK_API(int, sampgdk_cleanup(void));

/**
 * Same as sampgdk_cleanup() but explicitly specifies the plugin.
 */
SAMPGDK_API(int, sampgdk_cleanup_plugin(void *plugin));

/**
 * Prints a message to the server log. The format string is of the
 * space format as in printf().
 *
 * The resulting message cannot be longer than 1024 characters.
 */
SAMPGDK_API(void, sampgdk_logprintf(const char *format, ...));

/**
 * This is a va_list version of sampgdk_logprintf().
 */
SAMPGDK_API(void, sampgdk_vlogprintf(const char *format, va_list args));

/**
 * Registers a plugin for receiving events (e.g. SA-MP callbacks).
 * All subsequent calls to this function will be ignored.
 *
 * This function is implicitly called by sampgdk_init() and
 * sampgdk_init_plugin().
 */
SAMPGDK_API(int, sampgdk_register_plugin(void *plugin));

/**
 * The reverse of sampgdk_register_plugin(). Unsubscribes a plugin
 * from all events.
 *
 * This function is implicitly called by sampgdk_cleanup() and
 * sampgdk_cleanup_plugin().
 */
SAMPGDK_API(int, sampgdk_unregister_plugin(void *plugin));

/**
 * Returns the handle for a plugin that owns the specified address.
 */
SAMPGDK_API(void *, sampgdk_get_plugin_handle(void *address));

/**
 * Finds a symbol defined in plugin by its name. Returns NULL if the
 * symbol is not found.
 */
SAMPGDK_API(void *, sampgdk_get_plugin_symbol(void *plugin, const char *name));

/**
 * Processes timers created by the calling plugin.
 */
SAMPGDK_API(void, sampgdk_process_timers(void));

/**
 * Processes timers created by the specified plugin. If plugin
 * is NULL it processes ALL timers.
 */
SAMPGDK_API(void, sampgdk_process_plugin_timers(void *plugin));

/**
 * Returns a pointer the array of currently registered native
 * functions. You can use sampgdk_get_num_natives() to get the
 * size of the returned array.
 */
SAMPGDK_API(const AMX_NATIVE_INFO *, sampgdk_get_natives(void));

/**
 * Returns the number of currently registered native functions. It
 * can be used to retrieve the the number of elements in the array
 * returned by sampgdk_get_natives().
 */
SAMPGDK_API(int, sampgdk_get_num_natives(void));

/**
 * Finds a native function by name and returns its address or NULL
 * if the function is not found. The native function must be already
 * registered with amx_Register() prior to the call.
 *
 * It works for all SA-MP functions as well as for those provided by
 * third-party plugins.
 */
SAMPGDK_API(AMX_NATIVE, sampgdk_find_native(const char *name));

/**
 * Calls a native function with arguments specified in params and
 * returns the result.
 *
 * The first element of params should contain the number of arguments
 * multiplied by sizeof(cell). If the are no arguments, params may be
 * NULL.
 *
 */
SAMPGDK_API(cell, sampgdk_call_native(AMX_NATIVE native, cell *params));

/**
 * Calls a native function with the specified arguments and returns
 * the result.
 *
 * The argument types are specified by the format string. Each
 * character of the format string, or "specifier", corresponds to
 * a single argument.
 *
 * The following format specifiers are supported:
 *
 * +------+---------------+-----------------------------------------+
 * | Spec | C/C++ type    | Description                             |
 * +------+---------------+-----------------------------------------+
 * | 'i'  | int           | an integer value                        |
 * | 'd'  | int           | an integer value (same as 'i')          |
 * | 'b'  | bool          | a boolean value                         |
 * | 'f'  | float, double | a floating-point value                  |
 * | 'r'  | const cell *  | a const reference                       |
 * | 'R'  | cell *        | a non-const reference (output)          |
 * | 's'  | const char *  | a string of character                   |
 * | 'S'  | char *        | a string of character (output)          |
 * |      |               | size must be passed in next argument    |
 * +------+---------------+-----------------------------------------+
 */
SAMPGDK_API(cell, sampgdk_invoke_native(AMX_NATIVE native,
                                        const char *format, ...));

/**
 * Defines the signature of the public hook function.
 *
 * See sampgdk_set_public_hook() and sampgdk_get_public_hook() below.
 */
typedef bool (SAMPGDK_CALL *sampgdk_public_hook)(AMX *amx, const char *name,
                                                 cell *params);

/**
 * Sets the public hook. If the hook is already set it will be
 * overridden.
 *
 * The public hook is shared by all plugins, which means
 * you should save the previous value before calling this function
 * and call it manually (unless you're sure there are no other
 * plugins running).
 */
SAMPGDK_API(void, sampgdk_set_public_hook(sampgdk_public_hook hook));

/**
 * Returns the current public hook if it's set or NULL if not.
 */
SAMPGDK_API(sampgdk_public_hook, sampgdk_get_public_hook(void));

#endif /* !SAMPGDK_CORE_H */
