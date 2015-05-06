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

#include <sampgdk/version.h>

#include "api.h"
#include "callback.h"

#define _SAMPGDK_API_TAG \
  AMX_USERTAG('G', 'D', 'K', '0' + SAMPGDK_VERSION_MAJOR)

static int _sampgdk_api_get_version() {
  return SAMPGDK_VERSION_ID;
}

static const char *_sampgdk_api_get_version_string() {
  return SAMPGDK_VERSION_STRING;
}

static int _sampgdk_api_register_callback(const char *name) {
  return sampgdk_callback_register(name, NULL);
}

static bool _sampgdk_api_get_callback(int index, char **name) {
  return sampgdk_callback_get(index, name);
}

static struct sampgdk_api _sampgdk_api_obj = {
  _sampgdk_api_get_version,
  _sampgdk_api_get_version_string,
  _sampgdk_api_register_callback,
  _sampgdk_api_get_callback
};

struct sampgdk_api *sampgdk_api = &_sampgdk_api_obj;

int sampgdk_api_set(AMX *amx) {
  return -amx_SetUserData(amx, _SAMPGDK_API_TAG, sampgdk_api);
}

int sampgdk_api_get(AMX *amx, struct sampgdk_api **api) {
  return -amx_GetUserData(amx, _SAMPGDK_API_TAG, (void **)api);
}
