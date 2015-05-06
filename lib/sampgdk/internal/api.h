/* Copyright (C) 2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_API_H
#define SAMPGDK_INTERNAL_API_H

#include "amx.h"

struct sampgdk_api {
  int (*get_version)();
  const char *(*get_version_string)();
  int (*register_callback)(const char *name);
  bool (*get_callback)(int index, char **name);
};

extern struct sampgdk_api *sampgdk_api;

int sampgdk_api_set(AMX *amx);
int sampgdk_api_get(AMX *amx, struct sampgdk_api **api);

#endif /* !SAMPGDK_INTERNAL_API_H */
