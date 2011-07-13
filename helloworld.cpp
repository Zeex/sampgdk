// Very stupid gamemode that shows some basic stuff

#include "helloworld.h"

using namespace samp;

void HelloWorld::OnGameModeInit() {
    // This is HelloWorld, so...
    SetGameModeText("Hello, World!");

    // The trailing f's are needed to avoid compiler warnings (floating point literals
    // in C[++] are of type 'double', but we need 'float').
    AddPlayerClass(0, 1958.3783f, 1343.1572f, 15.3746f, 269.1425f, 0, 0, 0, 0, 0, 0);

    logprintf("-------------------------------------------\n");
    logprintf("      HelloWorld gamemode got loaded.      \n"); 
    logprintf("-------------------------------------------\n");
}

bool HelloWorld::OnPlayerConnect(int playerid) {
    SendClientMessage(playerid, 0xFFFFFFFF, "Welcome to our awesome server!");
    return true;
}

bool HelloWorld::OnPlayerRequestClass(int playerid, int classid) {
    SetPlayerPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
    SetPlayerCameraPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
    SetPlayerCameraLookAt(playerid, 1958.3783f, 1343.1572f, 15.3746f);
    return true;
}

bool HelloWorld::OnPlayerCommandText(int playerid, const std::string &cmdtext) {
    // Define a command in a "classic" way.
    // Most likely you will want to do this more efficiently, e.g. with a hash map.
    if (cmdtext == "/hello") {
        SendClientMessage(playerid, 0x00FF00FF, "Hello, " + GetPlayerName(playerid) + "!");
        return true;
    }
    return false;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()  {
    return SUPPORTS_VERSION;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData)  {
    // The wrapper needs to be initialized, this should done first.
    Wrapper::GetInstance()->Initialize(ppPluginData);
    // Set our gamemode as the main event handler. 
    EventHandler::SetEventHandler(std::shared_ptr<EventHandler>(new HelloWorld));
    // You can't call any of SA:MP native functions here -
    // they are not yet prepared for use at this stage.
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    return;
}
