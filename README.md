[GDK - Gamemode SDK for C/C++][github]
========================================

[![Version][version_badge]][version]
[![Build Status][build_status]][build]
[![Build Status - Windows][build_status_win]][build_win]
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

In order to build the GDK you first you need to download and install the
following:

* [SA-MP plugin SDK][sdk]
* [CMake][cmake] 2.8.12+
* [Python][python] 2.7+
* [PLY][ply] (Python-Lex-Yacc) and [cidl][cidl] (the IDL parser);
  both can be installed via [pip][pip]
* C compiler
* C++ compiler (optional, for building example plugins)

Once all dependencies are installed you can use the following commands to
build the library:

```sh
cd path/to/sampgdk
mkdir build && cd build
cmake ../ -DSAMP_SDK_ROOT=path/to/sdk
cmake --build . --config Release
cmake --build . --config Release --target install # optional
```

You can also pass additional arguments to the `cmake` command and change the
following build options:

* `SAMPGDK_STATIC`             - Build as static library (default is OFF)
* `SAMPGDK_BUILD_PLUGINS`      - Build example plugins (default is OFF)
* `SAMPGDK_BUILD_AMALGAMATION` - Build amalgamation (default is OFF)
* `SAMPGDK_BUILD_DOCS`         - Build Doxygen documentation (default is ON)

Getting Started
---------------

You can start with downloading the source code and playing a little bit with
the [helloworld][helloworld] plugin. In case you need documentation it's
available online [here][online_docs], in a browsable form, as well as in
the GDK header files.

If you feel like making a new project there's a
[step-by-step guide][cmake-guide] on setting up a GDK project with CMake.
No prior knowledge of CMake is required to follow it.

### Using Git

If you know Git and you've already managed to build the library successfully
the easiest way to get started is probably to clone this repo (if you haven't
done so) and create a new local branch for your personal project:

```
git clone git://github.com/Zeex/sampgdk.git
git checkout -b my-project
```

and begin working on it right inside the GDK source tree. You could either
edit the helloworld project or create a new project in a separate folder under
the `plugins/` directory. The latter is recommended as it would avoid possible
merge conflicts if helloworld suddenly gets updated in upstream.

Later if you decide that it's time to update the library, say to version
v1.2.3, you would simply fetch master from upstream and merge the changes
into your project's branch:

```
git fetch origin master
git merge v1.2.3
```

License
-------

Licensed under the Apache Licese version 2.0. See the LICENSE.txt file.

[github]: https://github.com/Zeex/sampgdk
[version]: http://badge.fury.io/gh/Zeex%2Fsampgdk
[version_badge]: https://badge.fury.io/gh/Zeex%2Fsampgdk.svg
[build]: https://travis-ci.org/Zeex/sampgdk
[build_status]: https://travis-ci.org/Zeex/sampgdk.svg?branch=master
[build_win]: https://ci.appveyor.com/project/Zeex/sampgdk/branch/master
[build_status_win]: https://ci.appveyor.com/api/projects/status/ybbvixqpppjhhyg7/branch/master?svg=true
[gitter]: https://gitter.im/Zeex/sampgdk?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge
[gitter_badge]: https://badges.gitter.im/Join%20Chat.svg
[helloworld]: plugins/helloworld
[sdk]: https://github.com/Zeex/samp-plugin-sdk
[cmake]: http://cmake.org
[python]: http://python.org
[ply]: http://www.dabeaz.com/ply/
[cidl]: https://github.com/Zeex/cidl
[pip]: https://pip.pypa.io/en/latest/
[online_docs]: http://zeex.github.io/sampgdk/doc/html/index.html
[cmake-guide]: https://github.com/Zeex/sampgdk/wiki/Setting-up-GDK-with-CMake
