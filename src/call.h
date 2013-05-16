/* Copyright (C) 2012-2013 Zeex
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

#ifndef SAMPGDK_CALL_H_
#define SAMPGDK_CALL_H_

void *sampgdk_get_ret_addr(void *frame, int depth);
void *sampgdk_call_func_cdecl(void *func, const void *const *args, int nargs);
void *sampgdk_call_func_stdcall(void *func, const void *const *args, int nargs);

#endif /* !SAMPGDK_CALL_H_ */
