// Copyright (C) 2011-2012, Zeex
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

#ifndef JUMP_X86_H
#define JUMP_X86_H

#if !defined _M_IX86 && !defined __i386__
	#error "Unsupported architecture"
#endif

class JumpX86 {
public:
	static const int kJmpInstrSize = 5;

	JumpX86();
	JumpX86(void *src, void *dst);
	~JumpX86();

	bool Install();
	bool Install(void *src, void *dst);
	bool Remove();

	bool IsInstalled() const;

	// Returns a E9 JMP destination as an aboluste address
	static void *GetTargetAddress(void *jmp);

	// Temporary Remove()
	class ScopedRemove {
	public:
		ScopedRemove(JumpX86 *jmp)
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
		JumpX86 *jmp_;
		bool removed_;
	};

	// Temporary Install()
	class ScopedInstall {
	public:
		ScopedInstall(JumpX86 *jmp)
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
		JumpX86 *jmp_;
		bool installed_;
	};

private:
	void *src_;
	void *dst_;
	unsigned char code_[5];
	bool installed_;
};

#endif

