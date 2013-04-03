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

%ifndef AMX_INC
%define AMX_INC

%define AMX_EXPORT_ALIGN16       0
%define AMX_EXPORT_ALIGN32       1
%define AMX_EXPORT_ALIGN64       2
%define AMX_EXPORT_ALLOT         3
%define AMX_EXPORT_CALLBACK      4
%define AMX_EXPORT_CLEANUP       5
%define AMX_EXPORT_CLONE         6
%define AMX_EXPORT_EXEC          7
%define AMX_EXPORT_FINDNATIVE    8
%define AMX_EXPORT_FINDPUBLIC    9
%define AMX_EXPORT_FINDPUBVAR    10
%define AMX_EXPORT_FINDTAGID     11
%define AMX_EXPORT_FLAGS         12
%define AMX_EXPORT_GETADDR       13
%define AMX_EXPORT_GETNATIVE     14
%define AMX_EXPORT_GETPUBLIC     15
%define AMX_EXPORT_GETPUBVAR     16
%define AMX_EXPORT_GETSTRING     17
%define AMX_EXPORT_GETTAG        18
%define AMX_EXPORT_GETUSERDATA   19
%define AMX_EXPORT_INIT          20
%define AMX_EXPORT_INITJIT       21
%define AMX_EXPORT_MEMINFO       22
%define AMX_EXPORT_NAMELENGTH    23
%define AMX_EXPORT_NATIVEINFO    24
%define AMX_EXPORT_NUMNATIVES    25
%define AMX_EXPORT_NUMPUBLICS    26
%define AMX_EXPORT_NUMPUBVARS    27
%define AMX_EXPORT_NUMTAGS       28
%define AMX_EXPORT_PUSH          29
%define AMX_EXPORT_PUSHARRAY     30
%define AMX_EXPORT_PUSHSTRING    31
%define AMX_EXPORT_RAISEERROR    32
%define AMX_EXPORT_REGISTER      33
%define AMX_EXPORT_RELEASE       34
%define AMX_EXPORT_SETCALLBACK   35
%define AMX_EXPORT_SETDEBUGHOOK  36
%define AMX_EXPORT_SETSTRING     37
%define AMX_EXPORT_SETUSERDATA   38
%define AMX_EXPORT_STRLEN        39
%define AMX_EXPORT_UTF8CHECK     40
%define AMX_EXPORT_UTF8GET       41
%define AMX_EXPORT_UTF8LEN       42
%define AMX_EXPORT_UTF8PUT       43

%endif // !AMX_INC
