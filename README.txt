========================================
SA:MP C++ gamemode SDK (or maybe GDK :D)
========================================

This is yet another C++ "wrapper" for Pawn which makes it possible to write gamemodes using the great power of the C++ language and a huge amount of third-party libraries.

The main feature of this wrapper is that it doesn't require the end users to run an additional filterscript/gamemode with all the callbacks, natives, etc in it. Also, since the wrapper's code doesn't make use of "hardcore" memory address hacks, it is portable across different versions of the SA:MP server. 


SA:MP native functions
--------------------------
All the functions from SA:MP 0.3c are available here as well. To be able to use them, you must include the "samp.h" header which is in the "samp/" directory 

[code]
#include "samp/samp.h"
[/code]

This will include all the other GDK's headers you will ever need. Note that since everything is in the samp namespace, you typically want to do the following:

[code]
using namespace samp;
[/code]

VERY IMPORTANT THING: before you can use any of the SA:MP native functions, you must _initialize_ the wrapper. This should be done in the Load() function of your plugin (you know, every plugin must have it).

[code]
PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData) {
    samp::Wrapper::GetInstance()->Initialize(ppPluginData);
    return true;
}
[/code]


SA:MP callbacks
--------------------------
The wrapper provides a single class with all the callbacks in it called EventHandler. If you wish to put some code in a callback, you must firt create a class inheriting from EventHandler and overload the necessary callback in it, like this:

[code]
// See helloworld.h and helloworld.cpp for the full code.

class HelloWorld : public samp::EventHandler {
public:
    virtual void OnGameModeInit();
    virtual bool OnPlayerConnect(int playerid);
    virtual bool OnPlayerRequestClass(int playerid);
    virtual bool OnPlayerCommandText(int playerid, const std::string &cmdtext);
};

void HelloWorld::OnGameModeInit() {
    logprintf("------------------------------------------\n");
    logprintf(" HelloWorld gamemode got loaded. \n");
    logprintf("------------------------------------------\n");
}

bool HelloWorld::OnPlayerCommandText(int playerid, const std::string &cmdtext) {
    if (cmdtext == "/hello") {
        SendClientMessage(playerid, 0x00FF00FF, "Hello, " + GetPlayerName(playerid) + "!");
        return true;
    }
    return false;
}

...
[/code]

So now you have a custom EventHandler. Good. But this is not enough! 

The second step you do is creating an instance of your gamemode somehwere and setting it as the current event handler using the SetEventHandler method of the EventHandler class. Again, you should do that in Load():

[code]
static HelloWorld theGameMode;

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppPluginData) {
    samp::Wrapper::GetInstance()->Initialize(ppPluginData);
    samp::EventHandler::SetEventHandler(&theGameMode);
    return true;
}
[/code]

Congratulations! You've finished your first C++ gamemode! 
