// Copyright (c) 2011 Zeex
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <cstring>

#if defined WIN32 || defined _WIN32
	#include <windows.h>
	typedef unsigned __int32 uint32_t;
#else
	#include <stdint.h>
	#include <unistd.h>
	#include <sys/mman.h>
#endif

static void Unprotect(void *address, int size) {
#if defined WIN32 || defined _WIN32
	DWORD oldProtect;
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
#else
	// Both address and size must be multiples of page size
	size_t pagesize = getpagesize();
	size_t where = ((reinterpret_cast<uint32_t>(address) / pagesize) * pagesize);
	size_t count = (size / pagesize) * pagesize + pagesize * 2;
	mprotect(reinterpret_cast<void*>(where), count, PROT_READ | PROT_WRITE | PROT_EXEC);
#endif
}

void SetJump(void *from, void *to, unsigned char (&oldCode)[5]) {
	Unprotect(from, 5);
	// Store the code we are going to overwrite (probably to copy it back later)
	memcpy(oldCode, from, 5);
	// E9 - jump near, relative
	unsigned char JMP = 0xE9;
	memcpy(from, &JMP, 1);
	// Jump address is relative to the next instruction's address
	size_t offset = (uint32_t)to - ((uint32_t)from + 5);
	memcpy((void*)((uint32_t)from + 1), &offset, 4);
}

void SetJump(void *from, void *to) {
	unsigned char dummy[5];
	SetJump(from, to, dummy);
}

