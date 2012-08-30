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

#if defined __MINGW32__ || defined __CYGWIN__
	#define PREFIX "_"
#else
	#define PREFIX
#endif

__asm__ (
PREFIX"get_return_address:"
".globl "PREFIX"get_return_address;"

"	movl 4(%esp), %eax;"
"	cmpl $0, %eax;"
"	jnz gra_init;"
"	movl %ebp, %eax;"

"gra_init:"
"	movl 8(%esp), %ecx;"
"	movl $0, %edx;"

"gra_loop:"
"	cmpl $0, %ecx;"
"	jl gra_exit;"
"	movl 4(%eax), %edx;"
"	movl (%eax), %eax;"
"	decl %ecx;"
"	jmp gra_loop;"

"gra_exit:"
"	movl %edx, %eax;"
"	ret;"
);

