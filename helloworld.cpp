#include "helloworld.h"

using namespace samp;

// Our gamemode is automatically registered as an event handler.
// You can undo this by calling Disconnect() or passing 'false' to constructor.
static HelloWorld theGameMode;

void HelloWorld::OnGameModeInit() {
    SetGameModeText("Hello, World!");

    AddPlayerClass(0, 1958.3783f, 1343.1572f, 15.3746f, 269.1425f, 0, 0, 0, 0, 0, 0);

    logprintf("------------------------------------------\n");
    logprintf("      HelloWorld gamemode got loaded.     \n"); 
    logprintf("------------------------------------------\n");
}

bool HelloWorld::OnPlayerConnect(int playerid) {
    SendClientMessage(playerid, 0xFFFFFFFF, "Welcome to the HelloWorld server!");
    return true;
}

bool HelloWorld::OnPlayerRequestClass(int playerid, int classid) {
    SetPlayerPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
    SetPlayerCameraPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
    SetPlayerCameraLookAt(playerid, 1958.3783f, 1343.1572f, 15.3746f);
    return true;
}

bool HelloWorld::OnPlayerCommandText(int playerid, const std::string &cmdtext) {
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
    // Initialize the wrapper - this always should  be done here.
    Wrapper::GetInstance()->Initialize(ppPluginData);
    // Register our gamemode in order to catch events - if you don't do this 
    // none of the HelloWorld callbacks will be ever called.
    theGameMode.Register();
    // Do not call any natives here - they are not yet prepared for use at this stage.
    return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    return;
}
