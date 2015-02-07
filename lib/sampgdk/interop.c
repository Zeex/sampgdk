/* Copyright (C) 2013-2015 Zeex
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

#include <sampgdk/export.h>
#include <sampgdk/sdk.h>

#include "internal/native.h"

SAMPGDK_API(const AMX_NATIVE_INFO *, sampgdk_GetNatives(int *number)) {
  return sampgdk_native_get_natives(number);
}

SAMPGDK_API(AMX_NATIVE, sampgdk_FindNative(const char *name)) {
  if (name != NULL) {
    return sampgdk_native_find(name);
  }
  return NULL;
}

SAMPGDK_API(cell, sampgdk_CallNative(AMX_NATIVE native, cell *params)) {
  return sampgdk_native_call(native, params);
}

SAMPGDK_API(cell, sampgdk_InvokeNative(AMX_NATIVE native,
                                       const char *format, ...)) {
  cell retval;
  va_list args;

  va_start(args, format);
  retval = sampgdk_native_invoke(native, format, args);
  va_end(args);

  return retval;
}

SAMPGDK_API(cell, sampgdk_InvokeNativeV(AMX_NATIVE native,
                                        const char *format, va_list args)) {
  return sampgdk_native_invoke(native, format, args);
}

SAMPGDK_API(cell, sampgdk_InvokeNativeArray(AMX_NATIVE native,
                                            const char *format, void **args)) {
  return sampgdk_native_invoke_array(native, format, args);
}
