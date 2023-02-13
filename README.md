[GDK - Gamemode SDK for C/C++][github]
======================================

[![Version][version_badge]][version]
[![Build Status][build_status]][build]

Introduction
-------------

GDK (Gamemode Development Kit) is a C/C++ library that allows you to write
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
following dependencies:

* [SA-MP plugin SDK][sdk]
* [CMake][cmake] 2.8.12+
* [Python][python] 2.7+
* [PLY][ply] (Python Lex-Yacc) can be installed via [pip][pip]
* C compiler
* C++ compiler (optional, for building example plugins)

Once all dependencies are installed you can use the following commands to
build and install the library:

```sh
cd path/to/sampgdk
mkdir build && cd build
cmake .. -DSAMP_SDK_ROOT=path/to/sdk
cmake --build . --config Release
cmake --build . --config Release --target install
```

You can pass additional arguments to CMake and change one or more of the
following options:

* `SAMPGDK_STATIC`             - Build as static library (default is OFF)
* `SAMPGDK_BUILD_PLUGINS`      - Build example plugins (default is OFF)
* `SAMPGDK_BUILD_AMALGAMATION` - Build amalgamation (default is OFF)
* `SAMPGDK_BUILD_DOCS`         - Build Doxygen documentation (default is ON)

For example, to build GDK as a static library together with example
plugins:

```sh
cmake .. -DSAMPGDK_STATIC=ON -DSAMPGDK_BUILD_PLUGINS=ON
```

The following built-in variables may also be useful:

* `CMAKE_BUILD_TYPE`     - Bulid type: Debug, Release, RelWIthDebInfo,
                           MinSizeRel
* `CMAKE_INSTALL_PREFIX` - Where to install files

For more information or questions about CMake please read the
[CMake FAQ][cmake_faq].

Getting Started
---------------

You can start with downloading the source code and playing a little bit with
the [helloworld][helloworld] plugin. In case you need documentation it's
available online [here][online_docs], in a browsable form, as well as in
the GDK header files.

If you feel like making a new project there's a
[step-by-step guide][cmake_guide] on setting up a GDK project with CMake.
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

Licensed under the Apache License version 2.0. See the LICENSE.txt file.

[github]: https://github.com/Zeex/sampgdk
[version]: https://github.com/Zeex/sampgdk/releases
[version_badge]: https://badge.fury.io/gh/Zeex%2Fsampgdk.svg
[build]: https://ci.appveyor.com/project/Zeex/sampgdk/branch/master
[build_status]: https://ci.appveyor.com/api/projects/status/ybbvixqpppjhhyg7/branch/master?svg=true
[helloworld]: plugins/helloworld
[online_docs]: http://zeex.github.io/sampgdk/doc/html/index.html
[cmake_faq]: http://www.cmake.org/Wiki/CMake_FAQ
[cmake_guide]: https://github.com/Zeex/sampgdk/wiki/Setting-up-GDK-with-CMake

