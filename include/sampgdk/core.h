/* Copyright (C) 2011-2015 Zeex
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
 * \defgroup core      Core
 * \defgroup interop   Interop
 * \defgroup version   Version
 * \defgroup sdk       SA-MP SDK
 * \defgroup natives   SA-MP Natives
 * \defgroup callbacks SA-MP Callbacks
 */

/**
 * \addtogroup core
 * @{
 */

/**
 * \brief Hidden parameter type, do not use this
 */
typedef int sampgdk_hidden_t;

/**
 * \brief Returns supported SDK version
 *
 * This function always returns SUPPORTS_VERSION. Its sole purpose is to
 * make sure that the version of the SDK is compatible with the one that
 * was used for building the library.
 *
 * \code
 * PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
 *   return sampgdk_Supports() | SUPPORTS_PROCESS_TICK;
 * }
 * \endcode
 *
 * \returns SUPPORTS_VERSION
 */
SAMPGDK_API(unsigned int, sampgdk_Supports(void));

/**
 * \brief Initializes the library
 *
 * Allocates memory for internal data structures and sets everything
 * up. Also keeps track of currently loaded plugins and registers the
 * calling plugin for callback handling.
 *
 * This function should be called from Load().
 *
 * \param ppData pointer to plugin data as passed to Load()
 *
 * \returns \c true on success and \c false otherwise
 *
 * \see sampgdk_Unload()
 */
SAMPGDK_API(bool, sampgdk_Load(void **ppData, sampgdk_hidden_t));

/**
 * \brief Shuts everything down, opposite of sampgdk_Load()
 *
 * This function should be called from Unload().
 *
 * \see sampgdk_Load()
 */
SAMPGDK_API(void, sampgdk_Unload(sampgdk_hidden_t));

/**
 * \brief Processes timers created by the calling plugin
 *
 * Goes through the list of created timers and, if necessary, fires
 * them one by one in the order of increasing IDs.
 *
 * If timer precision is important it's better to call this function
 * on every server tick. The plugin's ProcessTick() function might be
 * a good place for that.
 */
SAMPGDK_API(void, sampgdk_ProcessTick(sampgdk_hidden_t));

/**
 * \brief Prints a message to the server log
 *
 * \note The resulting message cannot be longer than 1024 characters.
 *
 * \param format printf-style format string
 * \param ... further arguments to logprintf()
 *
 * \see sampgdk_vlogprintf()
 */
SAMPGDK_API(void, sampgdk_logprintf(const char *format, ...));

/**
 * \brief Prints a message to the server log
 *
 * This function is identica to sampgdk_logprintf() except it takes
 * a \c va_list instead of variable arguments.
 *
 * \param format printf-style format string
 * \param args further arguments to logprintf()
 *
 * \see sampgdk_logprintf()
 */
SAMPGDK_API(void, sampgdk_vlogprintf(const char *format, va_list args));

/** @} */

#define sampgdk_Load(ppData)  sampgdk_Load(ppData, 0)
#define sampgdk_Unload()      sampgdk_Unload(0)
#define sampgdk_ProcessTick() sampgdk_ProcessTick(0)

#ifdef __cplusplus

/**
 * \brief Main namespace
 */
namespace sampgdk {

/**
 * \addtogroup core
 * @{
 */

/// \brief C++ wrapper around sampgdk_Supports()
inline unsigned int Supports() {
  return sampgdk_Supports();
}

/// \brief C++ wrapper around sampgdk_Load()
inline bool Load(void **ppData) {
  return sampgdk_Load(ppData);
}

/// \brief C++ wrapper around sampgdk_Unload()
inline void Unload() {
  sampgdk_Unload();
}

/// \brief C++ wrapper around sampgdk_ProcessTick()
inline void ProcessTick() {
  sampgdk_ProcessTick();
}

/// \brief C++ wrapper around sampgdk_logprintf()
inline void logprintf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  sampgdk_vlogprintf(format, args);
  va_end(args);
}

/// \brief C++ wrapper around sampgdk_vlogprintf()
inline void vlogprintf(const char *format, va_list args) {
  sampgdk_vlogprintf(format, args);
}

/** @} */

} // namespace sampgdk

#endif /* __cplusplus */

#endif /* !SAMPGDK_CORE_H */
