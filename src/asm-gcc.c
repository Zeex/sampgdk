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

#define SYMBOL(x) ASM_PREFIX x

#define GLOBAL(x) ".globl "SYMBOL(x)"\n"

#define BEGIN_GLOBAL(x) \
	GLOBAL(x) \
	x":\n"

#define FUNC "get_ret_addr"
__asm__ (
	BEGIN_GLOBAL(FUNC)
	"	movl 4(%esp), %eax\n"
	"	cmpl $0, %eax\n"
	"	jnz "FUNC"_init\n"
	"	movl %ebp, %eax\n"
	FUNC"_init:\n"
	"	movl 8(%esp), %ecx\n"
	"	movl $0, %edx\n"
	FUNC"_begin_loop:\n"
	"	cmpl $0, %ecx\n"
	"	jl "FUNC"_exit\n"
	"	movl 4(%eax), %edx\n"
	"	movl (%eax), %eax\n"
	"	decl %ecx\n"
	"	jmp "FUNC"_begin_loop\n"
	FUNC"_exit:\n"
	"	movl %edx, %eax\n"
	"	ret\n"
);
#undef FUNC

#define FUNC "call_func_cdecl"
__asm__ (
	BEGIN_GLOBAL(FUNC)
	"	movl 4(%esp), %eax\n"
	"	movl 8(%esp), %edx\n"
	"	movl 12(%esp), %ecx\n"
	"	pushl %edi\n"
	"	movl %ecx, %edi\n"
	"	sal $2, %edi\n"
	"	pushl %esi\n"
	FUNC"_begin_loop:"
	"	cmpl $0, %ecx\n"
	"	jle "FUNC"_end_loop\n"
	"	dec %ecx\n"
	"	movl (%edx, %ecx, 4), %esi\n"
	"	pushl %esi\n"
	"	jmp "FUNC"_begin_loop\n"
	FUNC"_end_loop:"
	"	call *%eax\n"
	"	addl %edi, %esp\n"
	"	popl %esi\n"
	"	popl %edi\n"
	"	ret\n"
);
#undef FUNC

#define FUNC "call_func_stdcall"
__asm__ (
	BEGIN_GLOBAL(FUNC)
	"	movl 4(%esp), %eax\n"
	"	movl 8(%esp), %edx\n"
	"	movl 12(%esp), %ecx\n"
	"	pushl %esi\n"
	FUNC"_begin_loop:"
	"	cmpl $0, %ecx\n"
	"	jle "FUNC"_end_loop\n"
	"	dec %ecx\n"
	"	movl (%edx, %ecx, 4), %esi\n"
	"	pushl %esi\n"
	"	jmp "FUNC"_begin_loop\n"
	FUNC"_end_loop:"
	"	call *%eax\n"
	"	popl %esi\n"
	"	ret\n"
);
#undef FUNC
