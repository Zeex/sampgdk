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

#ifndef JUMP_H
#define JUMP_H

#include <cstring>
#include <map>

// Modifies code at 'from' to make it JMP to 'to'.
void SetJump(void *from, void *to);
void SetJump(void *from, void *to, unsigned char (&oldCode)[5]);

class Jump {
public:
    inline void Install(void *from, void *to) {
        from_ = from; to_ = to;
        SetJump(from_, to_, code_);
    }

    inline void Remove() {
        std::memcpy(from_, code_, 5);
    }

    inline void Reinstall() {
        SetJump(from_, to_, code_);
    }

private:
    void *from_;
    void *to_;
    unsigned char code_[5];
};

#endif

