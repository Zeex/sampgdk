SA-MP Gamemode Development Kit
==============================

Introduction
------------

This is a C/C++ port of SA-MP Pawn API built on top of SA-MP plugin SDK. It allows you to make
gamemodes in both C and C++ in the form of server plugins and supports multiple plugins loaded
at once i.e. there is no "main" plugin (in fact, they act like filterscripts). 

Installation
------------

There is an installer for Windows and a self-extracting tarball for Linux here:

https://github.com/Zeex/sampgdk/downloads

*	Windows
	1.	Download and install `sampgdk-x.y.z-win32.exe`. 
	2.	Don't forget to check *Add sampgdk to the system PATH* option - otherwise you will have to 
		copy the .dll into your server's folder or change PATH variable manually.
	3.	Set proper include and library paths in your IDE.

*	Linux
	1.	Download `sampgdk-x.y.z-Linux.sh`.
	2.	Run it as follows: `sudo sh sampgdk-x.y.z-Linux.sh --prefix=/usr/local/`. This will install
		the library and headers to /usr/local/lib and /usr/local/include respectively.
	3.	Link against libsampgdk, e.g. `g++ -shared plugin.cpp -lsampgdk -o plugin.so`.

Bugs
----

Report bugs here: https://github.com/Zeex/sampgdk/issues.

