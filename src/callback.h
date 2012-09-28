/* Copyright (C) 2012 Zeex
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

#ifndef SAMPGDK_CALLBACK_H_
#define SAMPGDK_CALLBACK_H_

#include <sampgdk/amx.h>
#include <sampgdk/bool.h>

typedef bool (*callback_handler)(AMX *amx, void *callback, cell *retval);

int callback_init();
void callback_cleanup();

int callback_add_handler(const char *name, callback_handler handler);
bool callback_invoke(AMX *amx, const char *name, cell *retval);

#endif /* !SAMPGDK_CALLBACK_H */
