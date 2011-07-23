#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <samp/wrapper/eventhandler.h>

class HelloWorld : public samp::EventHandler {
public:
    HelloWorld();
    virtual ~HelloWorld();
    virtual void OnGameModeInit();
    virtual bool OnPlayerConnect(int playerid);
    virtual bool OnPlayerRequestClass(int playerid, int classid);
    virtual bool OnPlayerCommandText(int playerid, const std::string &cmdtext);
};

#endif