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

#ifndef HOOK_H
#define HOOK_H

#include <cstdint>

void SetJump(uint32_t from, uint32_t to, unsigned char (&oldCode)[5]);

#endif
