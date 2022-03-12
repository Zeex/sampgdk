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

#ifndef SAMPGDK_INTERNAL_LOG_H
#define SAMPGDK_INTERNAL_LOG_H

#define SAMPGDK_LOG_DEBUG   0
#define SAMPGDK_LOG_INFO    1
#define SAMPGDK_LOG_WARNING 2
#define SAMPGDK_LOG_ERROR   3

/* The SAMPGDK_MIN_LOG_LEVEL macro allows you to remove calls to logging
 * functions of certain levels from the resulting machine code at compile
 * time if you think that you will never need such log verbosity at run
 * time.
 */
#ifndef SAMPGDK_MIN_LOG_LEVEL
  #ifdef NDEBUG
    #define SAMPGDK_MIN_LOG_LEVEL SAMPGDK_LOG_INFO
  #else
    #define SAMPGDK_MIN_LOG_LEVEL SAMPGDK_LOG_DEBUG
  #endif
#endif

#if SAMPGDK_LOG_DEBUG >= SAMPGDK_MIN_LOG_LEVEL
  #define sampgdk_log_debug(...) \
    sampgdk_log_message(SAMPGDK_LOG_DEBUG, __VA_ARGS__)
#else
  #define sampgdk_log_debug(...)
#endif

#if SAMPGDK_LOG_INFO >= SAMPGDK_MIN_LOG_LEVEL
  #define sampgdk_log_info(...) \
    sampgdk_log_message(SAMPGDK_LOG_INFO, __VA_ARGS__)
#else
  #define sampgdk_log_info(...)
#endif

#if SAMPGDK_LOG_WARNING >= SAMPGDK_MIN_LOG_LEVEL
  #define sampgdk_log_warning(...) \
    sampgdk_log_message(SAMPGDK_LOG_WARNING, __VA_ARGS__)
#else
  #define sampgdk_log_warning(...)
#endif

#if SAMPGDK_LOG_ERROR >= SAMPGDK_MIN_LOG_LEVEL
  #define sampgdk_log_error(...) \
    sampgdk_log_message(SAMPGDK_LOG_ERROR, __VA_ARGS__)
#else
  #define sampgdk_log_error(...)
#endif

void sampgdk_log_message(int level, const char *format, ...);

#endif /* !SAMPGDK_INTERNAL_LOG_H */
