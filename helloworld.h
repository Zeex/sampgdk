#ifndef SAMPLE_GAMEMODE_H
#define SAMPLE_GAMEMODE_H

#include "samp/samp.h"

class HelloWorld : public samp::EventHandler {
public:
    virtual void OnGameModeInit();
    virtual bool OnPlayerConnect(int playerid);
    virtual bool OnPlayerRequestClass(int playerid, int classid);
    virtual bool OnPlayerCommandText(int playerid, const std::string &cmdtext);
};

#endif
