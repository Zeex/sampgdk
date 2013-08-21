; Copyright (C) 2012-2013 Zeex
;
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
;     http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.

global sampgdk_get_ret_addr
global sampgdk_call_func_cdecl
global sampgdk_call_func_stdcall

section .text

sampgdk_get_ret_addr:
  mov eax, dword [esp + 4]
  cmp eax, 0
  jnz .init
  mov eax, ebp
.init:
  mov ecx, dword [esp + 8]
  mov edx, 0
.loop:
  cmp ecx, 0
  jl .exit
  mov edx, dword [eax + 4]
  mov eax, dword [eax]
  dec ecx
  jmp .loop
.exit:
  mov eax, edx
  ret

sampgdk_call_func_cdecl:
  push ebp
  mov ebp, esp
  push esi
  push edi
  push ebx
  mov eax, dword [ebp + 8]
  mov esi, dword [ebp + 12]
  mov ebx, dword [ebp + 16]
  mov ecx, ebx
  sub esp, ecx
  mov edi, esp
  rep movsb
  call eax
  add esp, ebx
  pop ebx
  pop edi
  pop esi
  pop ebp
  ret

sampgdk_call_func_stdcall:
  push ebp
  mov ebp, esp
  push esi
  push edi
  push ebx
  mov eax, dword [ebp + 8]
  mov esi, dword [ebp + 12]
  mov ebx, dword [ebp + 16]
  mov ecx, ebx
  sub esp, ecx
  mov edi, esp
  rep movsb
  call eax
  pop ebx
  pop edi
  pop esi
  pop ebp
  ret
