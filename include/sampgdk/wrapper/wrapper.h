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

#include <map>
#include <string>

#include <sampgdk/plugin/plugin.h>

namespace sampgdk {

typedef std::basic_string<cell> cstring;

class PublicHook {
public:
    typedef cell (*Handler)(AMX *amx);

    PublicHook(Handler handler, cell breakingReturn);

    bool Execute(AMX *amx, cell *retval) const;

private:
    Handler handler_;
    cell breakingReturn_;
};

class Wrapper {
public:
    static Wrapper *GetInstance();

    void Initialize(void **ppPluginData);

    void SetNative(const std::string &name, AMX_NATIVE native);
    AMX_NATIVE GetNative(const std::string &name) const;

    void SetPublicHook(const std::string &name, PublicHook handler);
    bool ExecutePublicHook(AMX *amx, cell *retval, const std::string &name) const;

private:
    Wrapper();

    std::map<std::string, AMX_NATIVE> natives_;
    std::map<std::string, PublicHook> publicHooks_;
};

} // namespace sampgdk

#endif

