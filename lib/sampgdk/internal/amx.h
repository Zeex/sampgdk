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

#ifndef SAMPGDK_INTERNAL_AMX_H
#define SAMPGDK_INTERNAL_AMX_H

#include <sampgdk/sdk.h>

#define AMX_EXEC_GDK (-10000)

struct sampgdk_amx_api {
  uint16_t *(AMXAPI *Align16)(uint16_t *v);
  uint32_t *(AMXAPI *Align32)(uint32_t *v);
  uint64_t *(AMXAPI *Align64)(uint64_t *v);
  int (AMXAPI *Allot)(AMX *amx, int cells, cell *amx_addr, cell **phys_addr);
  int (AMXAPI *Callback)(AMX *amx, cell index, cell *result, cell *params);
  int (AMXAPI *Cleanup)(AMX *amx);
  int (AMXAPI *Clone)(AMX *amxClone, AMX *amxSource, void *data);
  int (AMXAPI *Exec)(AMX *amx, cell *retval, int index);
  int (AMXAPI *FindNative)(AMX *amx, const char *name, int *index);
  int (AMXAPI *FindPublic)(AMX *amx, const char *funcname, int *index);
  int (AMXAPI *FindPubVar)(AMX *amx, const char *varname, cell *amx_addr);
  int (AMXAPI *FindTagId)(AMX *amx, cell tag_id, char *tagname);
  int (AMXAPI *Flags)(AMX *amx,uint16_t *flags);
  int (AMXAPI *GetAddr)(AMX *amx,cell amx_addr,cell **phys_addr);
  int (AMXAPI *GetNative)(AMX *amx, int index, char *funcname);
  int (AMXAPI *GetPublic)(AMX *amx, int index, char *funcname);
  int (AMXAPI *GetPubVar)(AMX *amx, int index, char *varname, cell *amx_addr);
  int (AMXAPI *GetString)(char *dest,const cell *source, int use_wchar,
                          size_t size);
  int (AMXAPI *GetTag)(AMX *amx, int index, char *tagname, cell *tag_id);
  int (AMXAPI *GetUserData)(AMX *amx, long tag, void **ptr);
  int (AMXAPI *Init)(AMX *amx, void *program);
  int (AMXAPI *InitJIT)(AMX *amx, void *reloc_table, void *native_code);
  int (AMXAPI *MemInfo)(AMX *amx, long *codesize, long *datasize,
                        long *stackheap);
  int (AMXAPI *NameLength)(AMX *amx, int *length);
  AMX_NATIVE_INFO *(AMXAPI *NativeInfo)(const char *name, AMX_NATIVE func);
  int (AMXAPI *NumNatives)(AMX *amx, int *number);
  int (AMXAPI *NumPublics)(AMX *amx, int *number);
  int (AMXAPI *NumPubVars)(AMX *amx, int *number);
  int (AMXAPI *NumTags)(AMX *amx, int *number);
  int (AMXAPI *Push)(AMX *amx, cell value);
  int (AMXAPI *PushArray)(AMX *amx, cell *amx_addr, cell **phys_addr,
                          const cell array[], int numcells);
  int (AMXAPI *PushString)(AMX *amx, cell *amx_addr, cell **phys_addr,
                           const char *string, int pack, int use_wchar);
  int (AMXAPI *RaiseError)(AMX *amx, int error);
  int (AMXAPI *Register)(AMX *amx, const AMX_NATIVE_INFO *nativelist,
                         int number);
  int (AMXAPI *Release)(AMX *amx, cell amx_addr);
  int (AMXAPI *SetCallback)(AMX *amx, AMX_CALLBACK callback);
  int (AMXAPI *SetDebugHook)(AMX *amx, AMX_DEBUG debug);
  int (AMXAPI *SetString)(cell *dest, const char *source, int pack,
                          int use_wchar, size_t size);
  int (AMXAPI *SetUserData)(AMX *amx, long tag, void *ptr);
  int (AMXAPI *StrLen)(const cell *cstring, int *length);
  int (AMXAPI *UTF8Check)(const char *string, int *length);
  int (AMXAPI *UTF8Get)(const char *string, const char **endptr, cell *value);
  int (AMXAPI *UTF8Len)(const cell *cstr, int *length);
  int (AMXAPI *UTF8Put)(char *string, char **endptr, int maxchars, cell value);
};

extern struct sampgdk_amx_api *sampgdk_amx_api;

#define amx_Align16      sampgdk_amx_api->Align16
#define amx_Align32      sampgdk_amx_api->Align32
#define amx_Align64      sampgdk_amx_api->Align64
#define amx_Allot        sampgdk_amx_api->Allot
#define amx_Callback     sampgdk_amx_api->Callback
#define amx_Cleanup      sampgdk_amx_api->Cleanup
#define amx_Clone        sampgdk_amx_api->Clone
#define amx_Exec         sampgdk_amx_api->Exec
#define amx_FindNative   sampgdk_amx_api->FindNative
#define amx_FindPublic   sampgdk_amx_api->FindPublic
#define amx_FindPubVar   sampgdk_amx_api->FindPubVar
#define amx_FindTagId    sampgdk_amx_api->FindTagId
#define amx_Flags        sampgdk_amx_api->Flags
#define amx_GetAddr      sampgdk_amx_api->GetAddr
#define amx_GetNative    sampgdk_amx_api->GetNative
#define amx_GetPublic    sampgdk_amx_api->GetPublic
#define amx_GetPubVar    sampgdk_amx_api->GetPubVar
#define amx_GetString    sampgdk_amx_api->GetString
#define amx_GetTag       sampgdk_amx_api->GetTag
#define amx_GetUserData  sampgdk_amx_api->GetUserData
#define amx_Init         sampgdk_amx_api->Init
#define amx_InitJIT      sampgdk_amx_api->InitJIT
#define amx_MemInfo      sampgdk_amx_api->MemInfo
#define amx_NameLength   sampgdk_amx_api->NameLength
#define amx_NativeInfo   sampgdk_amx_api->NativeInfo
#define amx_NumNatives   sampgdk_amx_api->NumNatives
#define amx_NumPublics   sampgdk_amx_api->NumPublics
#define amx_NumPubVars   sampgdk_amx_api->NumPubVars
#define amx_NumTags      sampgdk_amx_api->NumTags
#define amx_Push         sampgdk_amx_api->Push
#define amx_PushArray    sampgdk_amx_api->PushArray
#define amx_PushString   sampgdk_amx_api->PushString
#define amx_RaiseError   sampgdk_amx_api->RaiseError
#define amx_Register     sampgdk_amx_api->Register
#define amx_Release      sampgdk_amx_api->Release
#define amx_SetCallback  sampgdk_amx_api->SetCallback
#define amx_SetDebugHook sampgdk_amx_api->SetDebugHook
#define amx_SetString    sampgdk_amx_api->SetString
#define amx_SetUserData  sampgdk_amx_api->SetUserData
#define amx_StrLen       sampgdk_amx_api->StrLen
#define amx_UTF8Check    sampgdk_amx_api->UTF8Check
#define amx_UTF8Get      sampgdk_amx_api->UTF8Get
#define amx_UTF8Len      sampgdk_amx_api->UTF8Len
#define amx_UTF8Put      sampgdk_amx_api->UTF8Put

#endif /* !SAMPGDK_INTERNAL_AMX_H */
