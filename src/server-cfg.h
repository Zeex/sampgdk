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

#ifndef SAMPGDK_SERVER_CFG_H_
#define SAMPGDK_SERVER_CFG_H_

#include <sampgdk/config.h>

typedef int (*server_cfg_callback)(const char *key, const char *value, void *param);

int server_cfg_parse(server_cfg_callback callback, void *param, int buffer_size);

#endif /* !SAMPGDK_SERVER_CFG_H_ */
