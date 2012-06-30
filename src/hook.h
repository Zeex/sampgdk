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

#ifndef HOOK_H
#define HOOK_H

#if !defined _M_IX86 && !defined __i386__
	#error Unsupported architecture
#endif

class Hook {
public:
	static const int kJmpInstrSize = 5;

	Hook();
	Hook(void *src, void *dst);
	~Hook();

	bool Install();
	bool Install(void *src, void *dst);
	bool IsInstalled() const;
	bool Remove();

	static void *GetTargetAddress(void *jmp);

	// Temporary Remove()
	class ScopedRemove {
	public:
		ScopedRemove(Hook *jmp) 
			: jmp_(jmp)
			, removed_(jmp->Remove())
		{
			// nothing
		}

		~ScopedRemove() {
			if (removed_) {
				jmp_->Install();
			}
		}

	private:		
		Hook *jmp_;
		bool removed_;
	};

	// Temporary Install() 
	class ScopedInstall {
	public:
		ScopedInstall(Hook *jmp) 
			: jmp_(jmp)
			, installed_(jmp->Install())
		{
			// nothing
		}

		~ScopedInstall() {
			if (installed_) {
				jmp_->Remove();
			}
		}

	private:
		Hook *jmp_;
		bool installed_;
	};

private:
	static void Unprotect(void *address, int size);

private:
	void *src_;
	void *dst_;
	unsigned char code_[5];
	bool installed_;
};

#endif

