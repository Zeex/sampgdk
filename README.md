[GDK - Gamemode SDK for C/C++][github]
========================================

[![Donate][donate_button]][donate]
[![Build Status][build_status]][build]

Introduction
-------------

The GDK (Gamemode Development Kit) is a library that allows you to write
SA-MP gamemodes in C/C++. It is built on top of the SA-MP plugin SDK, so
gamemodes written with it are basically just ordinary plugins.

The library provides most of the functions you would find in Pawn, except
thoset that either overlap with the C standard library, like file I/O or
string utiluties, or could be easily implemented on top of it. It also lets
you handle standard SA-MP scripting events (a.k.a. "callbacks").

Visit the [official SA-MP forums topic][topic] for more information and
support.

Building GDK
------------

Prerequisites:

* [SA-MP plugin SDK](https://github.com/Zeex/samp-plugin-sdk)
* [CMake](http://cmake.org) 2.8.12+
* [Python](http://python.org) 2.7+
* C89 compiler
* C++ compiler (for plugins)

Building the source code is as simple as running the following commands:

```sh
cd path/to/sampgdk
mkdir build && cd build
cmake ../ -DSDK_DIR=path/to/sdk
make
make install # optional
```

Supported options:

* SAMPGDK_STATIC             - Build as static library (default is OFF)
* SAMPGDK_BUILD_PLUGINS      - Build example plugins (default is OFF)
* SAMPGDK_BUILD_AMALGAMATION - Build amalgamation (default is OFF)

Getting Started
---------------

You can start with downloading the source code and playing a bit with the
[HelloWorld][helloworld] plugin.

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

Doxygen documentation is available online [here][doc].

[github]: https://github.com/Zeex/sampgdk
[donate]: http://pledgie.com/campaigns/19068
[donate_button]: http://pledgie.com/campaigns/19068.png
[build]: https://travis-ci.org/Zeex/sampgdk
[build_status]: https://travis-ci.org/Zeex/sampgdk.png?branch=master
[topic]: http://forum.sa-mp.com/showthread.php?t=421090
[helloworld]: https://github.com/Zeex/sampgdk/tree/master/plugins/helloworld
[doc]: http://zeex.github.io/sampgdk/doc/html/index.html
