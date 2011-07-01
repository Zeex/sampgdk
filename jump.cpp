// This file is part of SA:MP crashdetect plugin 
//
// Copyright 2011 Sergey Zolotarev
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cstdint>
#include <cstring>

#ifdef WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/mman.h>
#endif

static void Unprotect(uint32_t address, size_t size) {
#ifdef WIN32
    DWORD oldProtect;
    VirtualProtect((LPVOID)address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
#else
    int pagesize = getpagesize();
    int where = ((address / pagesize) * pagesize);
    int howmany = (size / pagesize) * pagesize + pagesize * 2;
    mprotect((void*)where, howmany, PROT_READ | PROT_WRITE | PROT_EXEC);
#endif
}

void SetJump(uint32_t from, uintptr_t to, unsigned char (&oldCode)[5]) {
    Unprotect(from, 5);
    memcpy(oldCode, (void*)from, 5);
    unsigned char JMP = 0xE9;
    memcpy((void*)from, &JMP, 1);
    uint32_t offset = to - (from + 5);
    memcpy((void*)(from + 1), &offset, 4);
}
