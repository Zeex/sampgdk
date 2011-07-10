#ifndef SAMP_WRAPPER_H
#define SAMP_WRAPPER_H

#include <string>
#include <unordered_map>

#include "plugin/amx/amx.h"

namespace samp {

typedef std::basic_string<cell> cstring;

typedef cell (*PublicHandler)(AMX *amx);

class Wrapper {
public:
    static Wrapper *GetInstance();

    void Initialize(void **ppPluginData);

    void SetNative(const std::string &name, AMX_NATIVE native);
    AMX_NATIVE GetNative(const std::string &name) const;

    void SetPublicHandler(const std::string &name, PublicHandler handler);
    cell CallPublic(AMX *amx, const std::string &name) const;

private:
    Wrapper();

    std::unordered_map<std::string, AMX_NATIVE> natives_;
    std::unordered_map<std::string, PublicHandler> publicHandlers_;
};

} // namespace samp

#endif