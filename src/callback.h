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

struct callback_info {
	const char       *name;
	callback_handler  handler;
};

/*
 * Initializes the API. Returns 0 on success and a negative value on error.
 */
int callback_init();

/*
 * Frees allocated resources.
 */
void callback_cleanup();

/*
 * Adds a new callback handler. Returns 0 on success and a negative
 * value on error.
 */
int callback_add_handler(const char *name, callback_handler handler);

/*
 * Invokes a callback by name and stores return value in retval
 * if retval is not NULL. Returns false if there is no callback
 * with such a name.
 */
bool callback_invoke(AMX *amx, const char *name, cell *retval);

#endif /* !SAMPGDK_CALLBACK_H_ */
