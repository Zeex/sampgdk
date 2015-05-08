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

/* Since version 4.3.1 the library exports a table of pointers to some
 * internal functions (called an internal API here or simply an API)
 * that helps plugins that are compiled with different version of the
 * library to cooperate.
 *
 * Currently this is needed to keep SA-MP callback indices in sync but
 * it may be also used for something else in the future.
 */
static struct sampgdk_api _sampgdk_api_local = {
  _sampgdk_api_get_version,
  _sampgdk_api_get_version_string,
  _sampgdk_api_register_callback,
  _sampgdk_api_get_callback
};

struct sampgdk_api *sampgdk_api = &_sampgdk_api_local;

static void _sampgdk_api_get(AMX *amx, struct sampgdk_api **api) {
  amx_GetUserData(amx, _SAMPGDK_API_TAG, (void **)api);
}

static void _sampgdk_api_set(AMX *amx, struct sampgdk_api *api) {
  amx_SetUserData(amx, _SAMPGDK_API_TAG, api);
}

void sampgdk_api_check(AMX *amx) {
  struct sampgdk_api *api = NULL;
  int version;
  int current_version;

  _sampgdk_api_get(amx, &api);

  if (api == NULL) {
    sampgdk_log_info("No existing API found, posting local version %s",
                     sampgdk_api->get_version_string());
    _sampgdk_api_set(amx, sampgdk_api);
    return;
  }

  version = api->get_version();
  current_version = sampgdk_api->get_version();

  if (version < current_version) {
    sampgdk_log_info("Overriding older API version %s",
                     sampgdk_api->get_version_string());
    _sampgdk_api_set(amx, sampgdk_api);
  } else if (version > current_version) {
    sampgdk_log_info("Switching to newer API version %s",
                     api->get_version_string());
    sampgdk_api = api;
  }
}
