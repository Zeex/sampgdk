// Copyright (c) 2012, Zeex
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met: 
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution. 
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <cstring>

#include "hook.h"

Hook::Hook() 
	: src_(0)
	, dst_(0)
	, installed_(false)
{}

Hook::Hook(void *src, void *dst) 
	: src_(0)
	, dst_(0)
	, installed_(false)
{
	Install(src, dst);
}

Hook::~Hook() {
	Remove();
}

bool Hook::Install() {
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
	size_t offset = (int)dst_ - ((int)src_ + kJmpInstrSize);
	memcpy((void*)((int)src_ + 1), &offset, kJmpInstrSize - 1);

	installed_ = true;
	return true;
}

bool Hook::Install(void *src, void *dst) {
	if (installed_) {
		return false;
	}

    src_ = src; 
	dst_ = dst;
	return Install();
}

bool Hook::Remove() {
	if (!installed_) {
		return false;
	}

	std::memcpy(src_, code_, kJmpInstrSize);
	installed_ = false;
	return true;
}

bool Hook::IsInstalled() const {
	return installed_;
}

// static 
void *Hook::GetTargetAddress(void *jmp) {
	if (*reinterpret_cast<unsigned char*>(jmp) == 0xE9) {
		int next_instr = reinterpret_cast<int>(reinterpret_cast<char*>(jmp) + kJmpInstrSize);
		int rel_addr = *reinterpret_cast<int*>(reinterpret_cast<char*>(jmp) + 1);
		int abs_addr = rel_addr + next_instr;
		return reinterpret_cast<void*>(abs_addr);
	}
	return 0;
}
