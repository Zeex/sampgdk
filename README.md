SA-MP Gamemode Development Kit 2
================================

Introduction
------------

The SA:MP GDK allows you to easily create SA-MP gamemodes in C++ loading them as server plugins. 
It is basically a wrapper around SA:MP native scripting functions and callbacks. 

Quick setup
------------

*	Windows
	*	Download and install `sampgdk-x.y.z-win32.exe`. 
	*	Don't forget to check *Add sampgdk to the system PATH* option - otherwise you will have to 
		copy the .dll into your server's folder or change PATH variable manually.
	*	Set proper include and library directories in your IDE.

*	Linux
	*	Download `sampgdk-x.y.z-Linux.sh`.
	*	Run it as follows: `sudo sh sampgdk-x.y.z-Linux.sh --prefix=/usr/local/`.
	*	Link against libsampgdk by passing `-lsampgdk` flag to linker when compiling a plugin.

If you are new to GDK have a look at the code of helloworld example first, it will teach you some basics.

Bugs
----

Report bugs here: https://github.com/Zeex/sampgdk/issues.

