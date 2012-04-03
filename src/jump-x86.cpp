// Copyright (c) 2011 Zeex
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

#include <cstring>

#include "jump-x86.h"

#if defined WIN32 || defined _WIN32

#include <windows.h>
typedef unsigned __int32 uint32_t;

static void Unprotect(void *address, int size) {
	DWORD oldProtect;
	VirtualProtect(address, size, PAGE_EXECUTE_READWRITE, &oldProtect);
}

#else

#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>

static void Unprotect(void *address, int size) {
	// Both address and size must be multiples of page size...
	size_t pagesize = getpagesize();
	size_t where = ((reinterpret_cast<uint32_t>(address) / pagesize) * pagesize);
	size_t count = (size / pagesize) * pagesize + pagesize * 2;
	mprotect(reinterpret_cast<void*>(where), count, PROT_READ | PROT_WRITE | PROT_EXEC);
}

#endif

JumpX86::JumpX86()
	: src_(0)
	, dst_(0)
	, installed_(false)
{}

JumpX86::JumpX86(void *src, void *dst)
	: src_(0)
	, dst_(0)
	, installed_(false)
{
	Install(src, dst);
}

JumpX86::~JumpX86() {
	Remove();
}

bool JumpX86::Install() {
	if (installed_) {
		return false;
	}

	// Set write permission
	Unprotect(src_, kJmpInstrSize);

	// Store the code we are going to overwrite (probably to copy it back later)
	memcpy(code_, src_, kJmpInstrSize);

	// E9 - jump near, relative
	unsigned char JMP = 0xE9;
	memcpy(src_, &JMP, 1);

	// Jump address is relative to the next instruction's address
	size_t offset = (uint32_t)dst_ - ((uint32_t)src_ + kJmpInstrSize);
	memcpy((void*)((uint32_t)src_ + 1), &offset, kJmpInstrSize - 1);

	installed_ = true;
	return true;
}

bool JumpX86::Install(void *src, void *dst) {
	if (installed_) {
		return false;
	}

    src_ = src;
	dst_ = dst;
	return Install();
}

bool JumpX86::Remove() {
	if (!installed_) {
		return false;
	}

	std::memcpy(src_, code_, kJmpInstrSize);
	installed_ = false;
	return true;
}

bool JumpX86::IsInstalled() const {
	return installed_;
}

// static
void *JumpX86::GetTargetAddress(void *jmp) {
	if (*reinterpret_cast<char*>(jmp) == 0xE9) {
		uint32_t next_instr = reinterpret_cast<uint32_t>(reinterpret_cast<char*>(jmp) + kJmpInstrSize);
		uint32_t rel_addr = *reinterpret_cast<uint32_t*>(reinterpret_cast<char*>(jmp) + 1);
		uint32_t abs_addr = rel_addr + next_instr;
		return reinterpret_cast<void*>(abs_addr);
	}
	return 0;
}