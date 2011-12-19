#ifndef HELLOWORLD_H
#define HELLOWORLD_H

#include <string>

#include <sampgdk/eventhandler.h>

class HelloWorld : public sampgdk::EventHandler {
public:
	HelloWorld();
	virtual ~HelloWorld();
	virtual bool OnGameModeInit();
	virtual bool OnPlayerConnect(int playerid);
	virtual bool OnPlayerRequestClass(int playerid, int classid);
	virtual bool OnPlayerCommandText(int playerid, const std::string &cmdtext);
};

#endif
