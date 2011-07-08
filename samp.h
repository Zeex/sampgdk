#ifndef SAMP_H
#define SAMP_H

#include <string>
#include <unordered_map>

#include "amx/amx.h"

typedef std::basic_string<cell> cellstring;

class SAMPWrapper {
public:
    static SAMPWrapper &GetInstance();

    void Initialize(void **ppPluginData);

    void SetNative(const std::string &name, AMX_NATIVE native);
    AMX_NATIVE GetNative(const std::string &name) const;

private:
    SAMPWrapper();

    std::unordered_map<std::string, AMX_NATIVE> natives_;
};

bool SetGameModeText(const std::string &text);
bool SendClientMessage(int playerid, long color, const std::string &message);

#endif