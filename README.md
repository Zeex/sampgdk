GDK - Gamemode SDK for C/C++ 
============================

[![Donate][donate_button]][donate]

GDK provides an API for developing SA-MP gamemodes in C or C++. Gamemodes
written with GDK are no different from ordinary server plugins except that
they make calls to an external library - the GDK runtime - that implements
the core functionality, like SA-MP native functions, and can call you back
if you want to handle certain SA-MP events (callbacks). 

Downloads
---------

To download binary packages for Windows and Linux please visit
[this page][download].

Source code
-----------

The source code is hosted at [GitHub][github].

Installation
------------

The packages provided on the download page are sort of all-in-one: they contain
both development files (like C++ headers) and dynamic library. So no matter
whether you are a developer or just a user, you generally install the same
package.

### Linux ###

  Download `sampgdk-x.y.z-Linux.sh where x.y.z` denotes the version number
  and run it as root like this:

  `sh sampgdk-x.y.z-Linux.sh --prefix=/usr/local`

  To avoid scrolling down through the whole license text (it's pretty
  long) press *Q*.

  You can change the prefix to whatever you want but typically it's
  something like `/usr` or `/usr/local` (though some Linux distributions
  don't recognize libraries stored in `/usr/local/lib` so you might need
  to edit `/etc/ld.so.conf`).

### Windows ###

  Download `sampgdk-x.y.z-win32.exe` (where x.y.z is the version number) and
  follow installation instructions.

  Don't forget to check *Add sampgdk to the system PATH for current
  user* if you want your plugins to automatically find and use the DLL.

Basic Usage
-----------

The structure of a GDK-based plugin is somewhat similar to that of a typical
Pawn script:

```c++
PLUGIN_EXPORT bool PLUGIN_CALL OnGameModeInit() {
  SetGameModeText("Hello, World!");

  AddPlayerClass(0, 1958.3783f, 1343.1572f, 15.3746f, 269.1425f, 0, 0, 0, 0, 0, 0);

  ServerLog::Printf("------------------------------------------\n");
  ServerLog::Printf("      HelloWorld gamemode got loaded.     \n");
  ServerLog::Printf("------------------------------------------\n");

  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerConnect(int playerid) {
  SendClientMessage(playerid, 0xFFFFFFFF, "Welcome to the HelloWorld server!");
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerRequestClass(int playerid, int classid) {
  SetPlayerPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
  SetPlayerCameraPos(playerid, 1958.3783f, 1343.1572f, 15.3746f);
  SetPlayerCameraLookAt(playerid, 1958.3783f, 1343.1572f, 15.3746f, CAMERA_CUT);
  return true;
}

PLUGIN_EXPORT bool PLUGIN_CALL OnPlayerCommandText(int playerid, const char *cmdtext) {
  if (std::strcmp(cmdtext, "/hello") == 0) {
    char name[MAX_PLAYER_NAME];
    GetPlayerName(playerid, name, MAX_PLAYER_NAME);
    char message[128];
    std::sprintf(message, "Hello, %s!", name);
    SendClientMessage(playerid, 0x00FF00FF, message);
    return true;
  }
  return false;
}
```

Of course, since it's a plugin you'll need some additional boilerplate code
(see Kyosaur's [Plugin development guide][guide] for more details). Besides
that you also have to perform some additional initialization and cleanup steps:

```c++
static ThisPlugin helloworld;

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
  helloworld.Load(ppData);
  return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
  helloworld.Unload();
}
```

Now if you are not planning to use timers you can stop at this point.
Otherwise, there's one more thing left to do:

```c++
PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
  helloworld.ProcessTimers();
}
```

That's it!

Example plugins
---------------

There are a few demo plugins in the [plugins][plugins] directory of the
source tree, namely:

* [HelloWorld][helloworld]

  Demonstrates how to initialize GDK and do basic stuff like how to add
  commands and set timers.


* [LVDM][lvdm]

  A C++ port of the LVDM gamemode that shipped with the SA-MP server download
  until 0.3x.


* [UnlimitedFS][unlimitedfs]

  This plugin, as the name suggests, allows you to load an unlimited amount of
  filterscripts. Pretty useful if you want to split you gamemode into multiple
  (independent) scripts.

Using CMake
-----------

[CMake][cmake] is a meta build system that generates build files for lower-level
platform- and compiler-specific build systems and IDEs, for example, GNU make
on Linux and Visual Studio on Windows (but there are far more systems
supported). You just create a single build definition file (usually called
`CMakeLists.txt`) and run CMake against it on the target system.

Below is an example of such a file:

```cmake
cmake_minimum_required(VERSION 2.8)
project(gamemode)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)
include(SampPlugin)

add_samp_plugin(gamemode
  gamemode.cpp
  gamemode.def
)
```

[SampPlugin][SampPlugin.cmake] is a special module that provides the
`add_samp_plugin()` function. This module is obviously not bundled with
CMake. To install the module crate a new directory called `cmake` inside
your project's root (where `CMakeLists.txt` resides) and yet another
directory called `Modules` inside of it, and put the module in there.

Now if your plugin uses GDK (which is probably why you are reading this
topic) you have to add the GDK library and include directories to the
corresponding search paths to be able to use it from your plugin (well,
this isn't strictly necessary on Linux but I'm assuming you want to be
cross-platform). This could be accomplished with something like this:

```cmake
include_directories(${THE_INCLUDE_DIRECTORY})
link_directories(${THE_LIB_DIRECTORY})

# The library names slightly differ on Windows and Linux.
if(WIN32)
  target_link_libraries(gamemode sampgdk3)
else()
  target_link_libraries(gamemode sampgdk)
endif()
```

For your convenience, there's a module called [FindSampGdk3][FindSampGdk3.cmake]
that can be used together with the [`find_package()`][find_package] command that
searches for the library and header paths for you. Just copy the module to 
`cmake/Modules` and `find_package()` will automatically use it when you will be
searching for a package named SampGdk3:

```cmake
find_package(SampGdk3 REQUIRED)
include_directories(${SampGdk3_INCLUDE_DIRS})
link_libraries(${SampGdk3_LIBRARIES})
```

You can also specify a minimum or exact version of the package when calling
`find_package` so incompatibles version will be rejected:

```cmake
find_package(SampGdk3 3.3 REQUIRED)
```

For the above code to work you have to do one more thing - add the GDK
installation's `lib` and `include` directories to one of the search paths
supported by CMake (see the documentation of `find_package()`). For example,
you can add the `include` directory to the `INCLUDE` environment variable and
the `lib` directory to the `LIB` variable.

[donate]: http://pledgie.com/campaigns/19068
[donate_button]: http://pledgie.com/campaigns/19068.png
[download]: http://zeex.github.com/sampgdk
[github]: https://github.com/Zeex/sampgdk
[guide]: http://forum.sa-mp.com/showthread.php?t=295798
[plugins]: https://github.com/Zeex/sampgdk/tree/master/plugins
[helloworld]: https://github.com/Zeex/sampgdk/tree/master/plugins/helloworld
[lvdm]: https://github.com/Zeex/sampgdk/tree/master/plugins/lvdm
[unlimitedfs]: https://github.com/Zeex/sampgdk/tree/master/plugins/unlimitedfs
[cmake]: http://www.cmake.org/
[SampPlugin.cmake]: https://github.com/Zeex/sampgdk/blob/master/cmake/Modules/SampPlugin.cmake
[FindSampGdk3.cmake]: https://github.com/Zeex/sampgdk/blob/master/cmake/Modules/FindSampGdk3.cmake
[find_package]: http://www.cmake.org/cmake/help/v2.8.10/cmake.html#command:find_package
