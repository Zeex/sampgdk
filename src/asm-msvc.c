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

__declspec(naked) void *get_ret_addr(void *frame, int depth) {
	__asm mov eax, dword ptr [esp + 4]
	__asm cmp eax, 0
	__asm jnz init
	__asm mov eax, ebp

init:
	__asm mov ecx, dword ptr [esp + 8]
	__asm mov edx, 0

begin_loop:
	__asm cmp ecx, 0
	__asm jl exit
	__asm mov edx, dword ptr [eax + 4]
	__asm mov eax, dword ptr [eax]
	__asm dec ecx
	__asm jmp begin_loop

exit:
	__asm mov eax, edx
	__asm ret
}

__declspec(naked) void *call_func_cdecl(void *func, const void *const *args, int nargs)
{
	__asm mov eax, dword ptr [esp + 4]
	__asm mov edx, dword ptr [esp + 8]
	__asm mov ecx, dword ptr [esp + 12]
	__asm push edi
	__asm mov edi, ecx
	__asm sal edi, 2
	__asm push esi
begin_loop:
	__asm cmp ecx, 0
	__asm jle end_loop
	__asm dec ecx
	__asm mov esi, dword ptr [edx + ecx * 4]
	__asm push esi
	__asm jmp begin_loop
end_loop:
	__asm call eax
	__asm add esp, edi
	__asm pop esi
	__asm pop edi
	__asm ret
	}

__declspec(naked) void *call_func_stdcall(void *func, const void *const *args, int nargs)
{
	__asm mov eax, dword ptr [esp + 4]
	__asm mov edx, dword ptr [esp + 8]
	__asm mov ecx, dword ptr [esp + 12]
	__asm push esi
begin_loop:
	__asm cmp ecx, 0
	__asm jle end_loop
	__asm dec ecx
	__asm mov esi, dword ptr [edx + ecx * 4]
	__asm push esi
	__asm jmp begin_loop
end_loop:
	__asm call eax
	__asm pop esi
	__asm ret
}
