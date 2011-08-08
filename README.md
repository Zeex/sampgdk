SA:MP Gamemode Development Kit for C++
======================================

Introduction
------------

This is a C++ wrapper for SA:MP Pawn scripting API. It allows you to call SA:MP built-in functions
and handle server events (i.e. callbacks) from within a plugin. 

Installing binaries
-------------------

On Windows:

*    If you are using MinGW, download and install sampgdk-x.x-gcc-install.exe
*    For Microsoft Visual C++, install sampgdk-x.x-install.exe

On Unix variants:

There's no packages yet, you have to compile it and install yourself.

Compiling yourself
--------------------

To compile from source you use CMake: http://cmake.org

CMake is a tool which generates input files for platform specific build tools, e.g. make's Makefiles on *nix or Visual Stuido projects on Windows.

The basic usage is:

    cmake -G <generator> path/to/source

For example:

    cmake -G "Visual Studio 9 2008" C:\sampgdk

After compilation is done, either run 'make install' or build the 'INSTALL' project depending on your tool choice.

License
-------

The code is licensed under the Apache License version 2.0, see LICENSE for details.

Authors
-------

Zeex

Contributors
------------

jte<br>
l1am9111<br>

