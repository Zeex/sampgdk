[GDK - Gamemode SDK for C/C++][github]
========================================

[![Build Status][build_status]][build]
[![Gitter][gitter_badge]][gitter]

Introduction
-------------

The GDK (Gamemode Development Kit) is a library that allows you to write
SA-MP gamemodes in C/C++. It mirrors the Pawn scripting API provied by
the SA-MP server and lets you handle various SA-MP events a.k.a callbacks
in a similar fashion.

For the impatient, [here](plugins/helloworld/helloworld.cpp) is what it
looks like in C++:

```c++
#include <stdio.h>
#include <string.h>

#include <sampgdk/a_players.h>
#include <sampgdk/a_samp.h>
#include <sampgdk/core.h>
#include <sampgdk/sdk.h>

void SAMPGDK_CALL PrintTickCountTimer(int timerid, void *params) {
  sampgdk::logprintf("Tick count: %d", GetTickCount());
}

PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
  SetGameModeText("Hello, World!");
  AddPlayerClass(0, 1958.3783f, 1343.1572f, 15.3746f, 269.1425f,
                 0, 0, 0, 0, 0, 0);
  SetTimer(1000, true, PrintTickCountTimer, 0);
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
  SendClientMessage(playerid, 0xFFFFFFFF, "Welcome to the HelloWorld server!");
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid,
                                                    int classid) {
  SetPlayerPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
  SetPlayerCameraPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
  SetPlayerCameraLookAt(playerid, 1958.3783f, 1343.1572f, 15.3746f, CAMERA_CUT);
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid,
                                                   const char *cmdtext) {
  if (strcmp(cmdtext, "/hello") == 0) {
    char name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, sizeof(name));
    char message[MAX_CLIENT_MESSAGE];
    sprintf(message, "Hello, %s!", name);
    SendClientMessage(playerid, 0x00FF00FF, message);
    return true;
  }
  return false;
}
```

Build Instructions
------------------

There's a number of build prerequisites:

* [SA-MP plugin SDK][sdk]
* [CMake][cmake] 2.8.12+
* [Python][python] 2.7+
* [PLY][ply] (Python-Lex-Yacc) and [cidl][cidl] (the IDL parser);
  both can be installed via [pip][pip]
* C compiler
* C++ compiler (optional, for building example plugins)

Once all dependencies are installed run the following commands to build
the library:

```sh
cd path/to/sampgdk
mkdir build && cd build
cmake ../ -DSDK_DIR=path/to/sdk
make
make install # optional
```

You can also pass additional options to the `cmake` command and change
some build variables (see below).

Supported variables:

* `SAMPGDK_STATIC`             - Build as static library (default is OFF)
* `SAMPGDK_BUILD_PLUGINS`      - Build example plugins (default is OFF)
* `SAMPGDK_BUILD_AMALGAMATION` - Build amalgamation (default is OFF)
* `SAMPGDK_BUILD_DOCS`         - Build Doxygen documentation (default is ON)

Getting Started
---------------

You can start with downloading the source code and playing a little bit
with the [HelloWorld][helloworld] plugin.

### Using Git

If you know Git the simplest way to get started is probably to clone this
repo and create a new local branch for your personal project:

```
git clone git://github.com/Zeex/sampgdk.git
git checkout -b my-project
```

and begin working on it right inside the GDK source tree.

Later if you decide that it's time to update the library, say to version
v1.2.3, you would simply switch to master, pull the changes in and merge
them into your local branch:

```
<commit your changes>
git checkout master
git pull origin master
git checkout my-project
git merge v1.2.3
```

Documentation
-------------

The API documentation is generated using [Doxygen][doxygen] and is located
in the doc/html directory of the build tree. For the current release it is
also available [online][online-docs].

[github]: https://github.com/Zeex/sampgdk
[build]: https://travis-ci.org/Zeex/sampgdk
[build_status]: https://travis-ci.org/Zeex/sampgdk.svg?branch=master
[gitter]: https://gitter.im/Zeex/sampgdk?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge
[gitter_badge]: https://badges.gitter.im/Join%20Chat.svg
[helloworld]: plugins/helloworld
[sdk]: https://github.com/Zeex/samp-plugin-sdk
[cmake]: http://cmake.org
[python]: http://python.org
[ply]: http://www.dabeaz.com/ply/
[cidl]: https://github.com/Zeex/cidl
[pip]: https://pip.pypa.io/en/latest/
[wiki-tutorial]: https://github.com/Zeex/sampgdk/wiki/Setting-up-GDK-with-CMake
[doxygen]: http://www.stack.nl/~dimitri/doxygen/
[online-docs]: http://zeex.github.io/sampgdk/doc/html/index.html
[forums]: http://forum.sa-mp.com/showthread.php?t=421090
