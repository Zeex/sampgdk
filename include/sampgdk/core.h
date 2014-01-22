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

/**
 * \file core.h
 * The core sampgdk types and functions.
 */

#ifndef SAMPGDK_CORE_H
#define SAMPGDK_CORE_H

#include <stdarg.h>

#include <sampgdk/bool.h>
#include <sampgdk/export.h>
#include <sampgdk/sdk.h>

/**
 * \addtogroup core
 * @{
 */

/**
 * \brief Initializes the library and the calling plugin.
 * 
 * When called for the first time, this function sets up the internal global
 * structures and registers the calling plugin for receiving certain events
 * e.g. SA-MP callbacks. All suebsequent calls are ignored.
 *
 * If for some reason this function fails it additionally may output an error
 * message to the serrver log describing the error.
 *
 * \param plugin_data the plugin data array passed to Load()
 *
 * \returns A non-negative value on success or an error code on failure.
 * The error code can be converted to a string using strerror().
 *
 * \see sampgdk_cleanup()
 */
SAMPGDK_API(int, sampgdk_init(void **plugin_data));

/**
 * \brief Same as sampgdk_init() but explicitly specifies the plugin.
 *
 * \param plugin the plugin handle
 * \param plugin_data the plugin data array passed to Load()
 
 * \returns A non-negative value on success or an error code on failure.
 * The error code can be converted to a string using strerror().
 *
 * \see sampgdk_cleanup_plugin()
 */
SAMPGDK_API(int, sampgdk_init_plugin(void *plugin, void **plugin_data));

/**
 * \brief Unregisters the calling plugin and, if this is the last remaining
 * plugin, it performs the final cleanup.
 *
 * \return A non-negative value on success or an error code on failure.
 * The error code can be converted to a string using strerror().
 *
 * \see sampgdk_init()
 */
SAMPGDK_API(int, sampgdk_cleanup(void));

/**
 * \brief Same as sampgdk_cleanup() but explicitly specifies the plugin.
 *
 * \param plugin the plugin handle
 *
 * \return A non-negative value on success or an error code on failure.
 * The error code can be converted to a string using strerror().
 * 
 * \see sampgdk_init_plugin()
 */
SAMPGDK_API(int, sampgdk_cleanup_plugin(void *plugin));

/**
 * \brief Prints a message to the server log. The format string is of the
 * space format as in printf().
 *
 * \note The resulting message cannot be longer than 1024 characters.
 *
 * \param format a printf-like format string
 * \param ... further arguments to logprintf()
 *
 * \see sampgdk_vlogprintf()
 */
SAMPGDK_API(void, sampgdk_logprintf(const char *format, ...));

/**
 * \brief This is a va_list version of sampgdk_logprintf().
 *
 * \param format a printf-like format string
 * \param args further arguments to logprintf()
 *
 * \see sampgdk_logprintf()
 */
SAMPGDK_API(void, sampgdk_vlogprintf(const char *format, va_list args));

/**
 * \brief Registers a plugin for receiving events (e.g. SA-MP callbacks).
 *
 * Subsequent calls to are ignored.
 *
 * This function is implicitly called by sampgdk_init() and
 * sampgdk_init_plugin().
 *
 * \param plugin the plugin handle
 *
 * \return A non-negative value on success or an error code on failure.
 * The error code can be converted to a string using strerror().
 *
 * \see sampgdk_unregister_plugin()
 */
SAMPGDK_API(int, sampgdk_register_plugin(void *plugin));

/**
 * \brief The reverse of sampgdk_register_plugin(). Unsubscribes a plugin
 * from all events.
 *
 * This function is implicitly called by sampgdk_cleanup() and
 * sampgdk_cleanup_plugin().
 *
 * \param plugin the plugin handle
 *
 * \return A non-negative value on success or an error code on failure.
 * The error code can be converted to a string using strerror().
 *
 * \see sampgdk_register_plugin()
 */
SAMPGDK_API(int, sampgdk_unregister_plugin(void *plugin));

/**
 * \brief Returns the handle for a plugin that owns the specified address.
 *
 * \param address any address within te plugin's address space
 *
 * \returns The plugin handle.
 *
 * \see sampgdk_get_plugin_symbol()
 */
SAMPGDK_API(void *, sampgdk_get_plugin_handle(void *address));

/**
 * \brief Finds a symbol defined in plugin by its name.
 *
 * \param plugin the plugin handle
 * \param name the name of the symbol
 *
 * \returns The address of the symbol or \c NULL if not found.
 *
 * \see sampgdk_get_plugin_handle()
 */
SAMPGDK_API(void *, sampgdk_get_plugin_symbol(void *plugin, const char *name));

/**
 * \brief Processes timers created by the calling plugin.
 *
 * \see sampgdk_process_plugin_timers()
 */
SAMPGDK_API(void, sampgdk_process_timers(void));

/**
 * \brief Processes timers created by the specified plugin.
 *
 * If \p plugin is \c NULL this function processes *all* created timers (i.e.
 * for all registered plugins).
 *
 * \param plugin the plugin handle
 *
 * \see sampgdk_process_timers()
 */
SAMPGDK_API(void, sampgdk_process_plugin_timers(void *plugin));

/**
 * \brief Gets all currently registered native functions.
 *
 * The return array is not null-terminated. Use sampgdk_get_num_natives()
 * to retreive the size of the array.
 *
 * \returns A pointer to the internal array of native functions.
 *
 * \see sampgdk_get_num_natives()
 */
SAMPGDK_API(const AMX_NATIVE_INFO *, sampgdk_get_natives(void));

/**
 * \brief Gets the total number of native functions.
 *
 * \returns The number of natives currently registered.
 *
 * \see sampgdk_get_natives()
 */
SAMPGDK_API(int, sampgdk_get_num_natives(void));

/**
 * \brief Finds a native function by name.
 *
 * The function must be already registered with amx_Register() prior
 * to the call.
 *
 * \warning It is not recommended to call this function before OnGameModeInit().
 *
 * \param name the name of the native function
 *
 * \returns The function's address or \c NULL if not found.
 *
 * \see sampgdk_get_natives()
 * \see sampgdk_call_native()
 * \see sampgdk_invoke_native()
 */
SAMPGDK_API(AMX_NATIVE, sampgdk_find_native(const char *name));

/**
 * \brief Calls a native function.
 *
 * \note The first element of \p params should contain the number of arguments
 * multiplied by \c sizeof(cell). If the function takes no arguments, \p params
 * may be \c NULL.
 *
 * \param native the native function
 * \param params the \c params array passsed to the function
 *
 * \returns The value returned by the function.
 *
 * \see sampgdk_find_native()
 * \see sampgdk_invoke_native()
 */
SAMPGDK_API(cell, sampgdk_call_native(AMX_NATIVE native, cell *params));

/**
 * \brief Invokes a native function with the specified arguments.
 *
 * The argument types are specified via \p format where each character,
 * or specifier, corresponds to a single argument.
 *
 * The following format specifiers are supported:
 *
 * Specifier | C/C++ type    | Description
 * :-------- | :------------ | :-----------------------------
 * i         | int           | an integer value
 * d         | int           | an integer value (same as 'i')
 * b         | bool          | a boolean value
 * f         | float, double | a floating-point value
 * r         | const cell *  | a const reference
 * R         | cell *        | a non-const reference (output)
 * s         | const char *  | a string of character
 * S         | char *        | a string of character (output)
 *
 * \note For the 'S' specifier the argument next to it specifies the maximum
 * length of the string. This convention is followed by all SA-MP functions.
 *
 * \param native the native function
 * \param format the format string specifying the argument types
 * \param ... the arguments themselves
 *
 * \returns The value returned by the function.
 *
 * \see sampgdk_find_native()
 * \see sampgdk_call_native()
 */
SAMPGDK_API(cell, sampgdk_invoke_native(AMX_NATIVE native,
                                        const char *format, ...));

/**
 * \brief Defines the signature of the public hook function.
 *
 * \param amx a pointer to the AMX instance on the public function is called
 * \param name the name of the function
 * \param params a pointer to the function's arguments on the stack
 *
 * \see sampgdk_set_public_hook()
 * \see sampgdk_get_public_hook()
 */
typedef bool (SAMPGDK_CALL *sampgdk_public_hook)(AMX *amx, const char *name,
                                                 cell *params);

/**
 * \brief Sets or overrides the public hook.
 *
 * The public hook is shared by all plugins, which means you should save the
 * previous value before calling this function and call it manually (unless
 * you're sure that there are no other plugins running).
 *
 * \param hook the hook function
 *
 * \see sampgdk_get_public_hook()
 */
SAMPGDK_API(void, sampgdk_set_public_hook(sampgdk_public_hook hook));

/**
 * \brief Gets current public hook.
 *
 * \returns Current public hook or \c NULL if not set.
 *
 * \see sampgdk_set_plugin_hook()
 */
SAMPGDK_API(sampgdk_public_hook, sampgdk_get_public_hook(void));

/** @} */

#endif /* !SAMPGDK_CORE_H */
