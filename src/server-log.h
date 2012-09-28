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

#ifndef SAMPGDK_SERVER_LOG_H_
#define SAMPGDK_SERVER_LOG_H_

#include <stdarg.h>

void server_log_printf(const char *format, ...);
void server_log_vprintf(const char *format, va_list args);

#endif /* !SAMPGDK_SERVER_LOG_H */
