/* Copyright (C) 2012-2019 Zeex
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

#ifndef SAMPGDK_INTERNAL_LOGPRINTF_H
#define SAMPGDK_INTERNAL_LOGPRINTF_H

#include <stdarg.h>

#define SAMPGDK_LOGPRINTF_BUFFER_SIZE 1024

typedef void (*logprintf_t)(const char *format, ...);

extern logprintf_t sampgdk_logprintf_impl;

void sampgdk_do_vlogprintf(const char *format, va_list va);

#endif /* !SAMPGDK_INTERNAL_LOGPRINTF_H */
