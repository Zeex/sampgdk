; Copyright (C) 2013 Zeex
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

%include "amx.inc"

global amx_exports
global amx_Align16
global amx_Align32
global amx_Align64
global amx_Allot
global amx_Callback
global amx_Cleanup
global amx_Clone
global amx_Exec
global amx_FindNative
global amx_FindPublic
global amx_FindPubVar
global amx_FindTagId
global amx_Flags
global amx_GetAddr
global amx_GetNative
global amx_GetPublic
global amx_GetPubVar
global amx_GetString
global amx_GetTag
global amx_GetUserData
global amx_Init
global amx_InitJIT
global amx_MemInfo
global amx_NameLength
global amx_NativeInfo
global amx_NumNatives
global amx_NumPublics
global amx_NumPubVars
global amx_NumTags
global amx_Push
global amx_PushArray
global amx_PushString
global amx_RaiseError
global amx_Register
global amx_Release
global amx_SetCallback
global amx_SetDebugHook
global amx_SetString
global amx_SetUserData
global amx_StrLen
global amx_UTF8Check
global amx_UTF8Get
global amx_UTF8Len
global amx_UTF8Put
	
section .text 

amx_Align16:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_ALIGN16 * 4]
	
amx_Align32:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_ALIGN32 * 4]	

amx_Align64:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_ALIGN64 * 4]

amx_Allot:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_ALLOT * 4]
	
amx_Callback:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_CALLBACK * 4]
	
amx_Cleanup:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_CLEANUP * 4]
	
amx_Clone:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_CLONE * 4]			
amx_Exec:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_EXEC * 4]
	
amx_FindNative:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_FINDNATIVE * 4]
	
amx_FindPublic:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_FINDPUBLIC * 4]
	
amx_FindPubVar:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_FINDPUBVAR * 4]

amx_FindTagId:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_FINDTAGID * 4]
	
amx_Flags:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_FLAGS * 4]
	
amx_GetAddr:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_GETADDR * 4]
	
amx_GetNative:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_GETNATIVE * 4]

amx_GetPublic:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_GETPUBLIC * 4]
	
amx_GetPubVar:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_GETPUBVAR * 4]
	
amx_GetString:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_GETSTRING * 4]
	
amx_GetTag:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_GETTAG * 4]
	
amx_GetUserData:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_GETUSERDATA * 4]
	
amx_Init:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_INIT * 4]
	
amx_InitJIT:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_INITJIT * 4]
	
amx_MemInfo:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_MEMINFO * 4]						
	
amx_NameLength:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_NAMELENGTH * 4]			
	
amx_NativeInfo:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_NATIVEINFO * 4]			
	
amx_NumNatives:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_NUMNATIVES * 4]			
	
amx_NumPublics:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_NUMPUBLICS * 4]							
	
amx_NumPubVars:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_NUMPUBVARS * 4]				
	
amx_NumTags:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_NUMTAGS * 4]				
	
amx_Push:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_PUSH * 4]				
	
amx_PushArray:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_PUSHARRAY * 4]				
	
amx_PushString:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_PUSHSTRING * 4]				
	
amx_RaiseError:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_RAISEERROR * 4]				
	
amx_Register:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_REGISTER * 4]				
	
amx_Release:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_RELEASE * 4]				
	
amx_SetCallback:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_SETCALLBACK * 4]				
	
amx_SetDebugHook:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_SETDEBUGHOOK * 4]				
	
amx_SetString:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_SETSTRING * 4]				
	
amx_SetUserData:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_SETUSERDATA * 4]				
	
amx_StrLen:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_STRLEN * 4]				
	
amx_UTF8Check:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_UTF8CHECK * 4]			
	
amx_UTF8Get:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_UTF8GET * 4]			
		
amx_UTF8Len:
	mov eax, [amx_exports]	
	jmp dword [eax + 42*4]	
				
amx_UTF8Put:
	mov eax, [amx_exports]
	jmp dword [eax + AMX_EXPORT_UTF8PUT * 4]

section .data

amx_exports: dd 0