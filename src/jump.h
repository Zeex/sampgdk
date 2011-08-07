// Copyright (c) 2011 SA:MP GDK Project
// See file LICENSE for license details.

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

