[SA-MP Gamemode Development Kit][github]
========================================

[![Donate][donate_button]][donate]
[![Build Status][build_status]][build]

Introduction
-------------

The GDK (Gamemode Development Kit) is a library that allows you to write
SA-MP gamemodes in C/C++. It is built on top of the SA-MP plugin SDK, so
gamemodes written with it are basically just ordinary plugins.

The library provides most the functions you would find in Pawn, except thos
that overlap with the C standard library, like file I/O or string utiluties,
or could be easily implemented on top of it. It also lets you handle various
SA-MP events (known as "callbacks" in Pawn).

Visit the [official SA-MP forums topic][topic] for more information and
support.

Getting Started
---------------

You can begin with downloading the source code and playing a bit with the
HelloWorld plugin in `plugins/helloworld`.

If you know Git the simplest way to get started is probably to clone this repo
and create a new branch for your personal project like `my-project`, and then
just start developing your own plugin right in the GDK's source tree. Later if
you decide to update the library you would simply switch to  `master`, pull in
the changes and merge them into `my-project`.

There are also some useful files provied for developing plugins in Visual Studio
using the above method. They are located in `build/visual-studio`. Running the
`configure.bat` script is the first thing you would do after downloading the
source code and installing the necessary development tools (like CMake and the
Visual Studio itself). Next you have to set the `SAMP_SERVER_ROOT` environment
variable to the full path of the server folder - this makes the post-build
events work and allows you to run the server easily from within Visual Studio.
The post-build events defined in the .user files copy both the library and
helloworld.dll to `%SAMP_SERVER_ROOT%` and `%SAMP_SERVER_ROOT%/plugins`
respectively (but only in Debug builds).

Downloads
---------

Pre-compiled binaries for Windows and Linux along with the documentation and
other development files can be downloaded [here][download].

[donate]: http://pledgie.com/campaigns/19068
[donate_button]: http://pledgie.com/campaigns/19068.png
[build]: https://travis-ci.org/Zeex/sampgdk
[build_status]: https://travis-ci.org/Zeex/sampgdk.png?branch=master
[topic]: http://forum.sa-mp.com/showthread.php?t=421090
[github]: https://github.com/Zeex/sampgdk
[download]: https://github.com/Zeex/sampgdk/releases
[helloworld]: https://github.com/Zeex/sampgdk/tree/master/plugins/helloworld
