// Calling SA:MP natives from C++

#include "samp/samp.h"
#include "samp/wrapper.h"
#include "samp/plugin/plugin.h"

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()  {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData)  {
    samp::Wrapper::GetInstance()->Initialize(ppPluginData);
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
    samp::SetGameModeText("Hello from C++!!");
    return AMX_ERR_NONE;
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
    return AMX_ERR_NONE;
}
