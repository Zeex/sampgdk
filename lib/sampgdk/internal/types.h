/* Copyright (C) 2014-2015 Zeex
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

#ifndef SAMPGDK_INTERNAL_TYPES_H
#define SAMPGDK_INTERNAL_TYPES_H

#if defined _MSC_VER && _MSC_VER <= 1600
  typedef __int8 int8_t;
  typedef unsigned __int8 uint8_t;
  typedef __int16 int16_t;
  typedef unsigned __int16 uint16_t;
  typedef __int32 int32_t;
  typedef unsigned __int32 uint32_t;
#else
  #include <stdint.h>
#endif

#if SAMPGDK_WINDOWS
  #ifndef PRId32
    #define PRId32 "I32d"
  #endif
  #ifndef PRId64
    #define PRId64 "I64d"
  #endif
#else
  #include <inttypes.h>
#endif

#endif /* !SAMPGDK_INTERNAL_TYPES_H */
