#include <stdio.h>
#include <string.h>

#include <sampgdk/a_players.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/core.h>
#include <sampgdk/sdk.h>

using sampgdk::logprintf;

extern void *pAMXFunctions;

AMX * a;

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
  sampgdk::ProcessTick();
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
    return sampgdk::Supports() | SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    return sampgdk::Load(ppData);
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
    sampgdk::Unload();
}


PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
    a = amx;
    return AMX_ERR_NONE;
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
    return AMX_ERR_NONE;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
    int one = 10;
    int two = 20;
    int three = 30;
    int amxIndex = 0;

    logprintf("amx_FindPublic...TestCB3");
    if (!amx_FindPublic(a, "TestCB3", &amxIndex))
    {
        logprintf("amx_Push...");
        amx_Push(a, one);
        amx_Push(a, two);
        amx_Push(a, three);

        logprintf("amx_Exec...");
        amx_Exec(a, NULL, amxIndex);
    }
    else
    {
        logprintf("amx_FindPublic failed to find :(...");
    }
    return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPublicCall(AMX *amx, const char *name, cell *params, cell *retval) {
    if (!strcmp(name, "TestCB1")) {
        logprintf(">TestCB1(%d) %d", (params[0] / sizeof(cell)), params[1]);
    }
    if (!strcmp(name, "TestCB2")) {
        logprintf(">TestCB2(%d) %d %d", (params[0] / sizeof(cell)), params[1], params[2]);
    }
    if (!strcmp(name, "TestCB3")) {
        logprintf(">TestCB3(%d) %d %d %d", (params[0] / sizeof(cell)), params[1], params[2], params[3]);
    }
    if (!strcmp(name, "OnPlayerConnect")) {
        logprintf(">OnPlayerConnect(%d) %d", (params[0] / sizeof(cell)), params[1]);
    }
    return true;
}

