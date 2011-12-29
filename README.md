SA-MP Gamemode Development Kit for C/C++
======================================

Introduction
------------

The SA:MP GDK allows you to easily create SA-MP gamemodes in C++ loading them as server plugins. 
It is basically a wrapper around SA:MP native scripting functions and callbacks. 

Quick setup
------------

*	Windows
	*	Download and install `sampgdk-x.x.x-win32.exe`. 
	*	Don't forget to check *Add sampgdk to the system PATH* option - otherwise you will have to 
		copy the .dll into server folder or change PATH manually.
	*	Set the right include and library directories in your IDE.

*	Linux, etc
	*	Download and install `sampgdk-x.x.x-Linux.sh`. 
	*	Pass -lsampgdk flag to the linker.
	*	Done!

If you are new to GDK have a look at the code of helloworld example first, it will teach you some basics.

Bugs 
----

Report bugs here: https://github.com/Zeex/sampgdk/issues.

