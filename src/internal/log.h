/* Copyright (C) 2012-2014 Zeex
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

#ifndef SAMPGDK_INTERNAL_LOG_H
#define SAMPGDK_INTERNAL_LOG_H

void sampgdk_log_info(const char *format, ...);
void sampgdk_log_trace(const char *format, ...);
void sampgdk_log_warning(const char *format, ...);
void sampgdk_log_error(const char *format, ...);
void sampgdk_log_error_code(int error);

#endif /* !SAMPGDK_INTERNAL_LOG_H */
