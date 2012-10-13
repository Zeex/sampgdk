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

__asm__ (
".globl "ASM_PREFIX"get_return_address\n"
);

__asm__ (
ASM_PREFIX"get_return_address:\n"

"	movl 4(%esp), %eax\n"
"	cmpl $0, %eax\n"
"	jnz gra_init\n"
"	movl %ebp, %eax\n"

"gra_init:\n"
"	movl 8(%esp), %ecx\n"
"	movl $0, %edx\n"

"gra_loop:\n"
"	cmpl $0, %ecx\n"
"	jl gra_exit\n"
"	movl 4(%eax), %edx\n"
"	movl (%eax), %eax\n"
"	decl %ecx\n"
"	jmp gra_loop\n"

"gra_exit:\n"
"	movl %edx, %eax\n"
"	ret\n"
);
