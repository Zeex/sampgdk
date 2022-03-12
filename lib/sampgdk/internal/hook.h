/* Copyright (C) 2012-2016 Zeex
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

#ifndef SAMPGDK_INTERNAL_HOOK_H
#define SAMPGDK_INTERNAL_HOOK_H

struct _sampgdk_hook;
typedef struct _sampgdk_hook *sampgdk_hook_t;

sampgdk_hook_t sampgdk_hook_new(void *src, void *dst);
void sampgdk_hook_free(sampgdk_hook_t hook);
void *sampgdk_hook_trampoline(sampgdk_hook_t hook);

#define SAMPGDK_HOOK_CALL(hook, return_type, args) \
  ((return_type (*)())sampgdk_hook_code(hook))args

#define SAMPGDK_HOOK_CALL_CC(hook, return_type, callconv, types, args) \
  ((return_type (callconv *)types)sampgdk_hook_trampoline(hook))args

#endif /* !SAMPGDK_INTERNAL_HOOK_H */
