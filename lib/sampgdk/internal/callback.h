/* Copyright (C) 2012-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_CALLBACK_H
#define SAMPGDK_INTERNAL_CALLBACK_H

#include <sampgdk/bool.h>
#include <sampgdk/sdk.h>

/* Callback handler function. */
typedef bool (*sampgdk_callback)(AMX *amx, void *func, cell *retval);

/* Register and unregister a callback in the global callback table.
 *
 * This is usually done only from generated init and cleanup functions of a_*
 * modules. Currently the only module that defines callbacks is a_samp.
 */
int sampgdk_callback_register(const char *name, sampgdk_callback handler);
void sampgdk_callback_unregister(const char *name);

/* Gets the name of the callback with the specified index,
 * similar to amx_GetPublic().
 */
bool sampgdk_callback_get(int index, char **name);

/* Executes the callback handler registered for the specified callback.
 *
 * The return value indicates whether the callback returned a "bad" value,
 * i.e. whether the gamemode is allowed to execute the associated public
 * function. This value is specified in the IDL files via the callback's
 * "badret" attribute.
 */
bool sampgdk_callback_invoke(AMX *amx, const char *name,
    int paramcount, cell *retval);

#endif /* !SAMPGDK_INTERNAL_CALLBACK_H */
