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

#ifndef SAMP_WRAPPER_H
#define SAMP_WRAPPER_H

#include <string>
#include <unordered_map>

#include "plugin/amx/amx.h"

namespace samp {

typedef std::basic_string<cell> cstring;

class Wrapper {
public:
    static Wrapper *GetInstance();

    void Initialize(void **ppPluginData);

    void SetNative(const std::string &name, AMX_NATIVE native);
    AMX_NATIVE GetNative(const std::string &name) const;

private:
    Wrapper();

    std::unordered_map<std::string, AMX_NATIVE> natives_;
};

} // namespace samp

#endif