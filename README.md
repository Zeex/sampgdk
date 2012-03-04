SA-MP Gamemode Development Kit 2
================================

The SA-MP GDK allows you to easily create SA-MP gamemodes in C++ and load them as server plugins. 

Installation
------------

*	Windows
	1.	Download and install `libsampgdk-x.y.z-win32.exe`. 
	2.	Don't forget to check *Add sampgdk to the system PATH* option - otherwise you will have to 
		copy the .dll into your server's folder or change PATH variable manually.
	3.	Set proper include and library paths in your IDE.

*	Linux
	1.	Download and install either of `libsampgdk-x.y.z-Linux.deb` and `libsampgdk-x.y.z-Linux.rpm`.
	2.	Now you can both runtime library and development headers.
	3.	If you are making a plugin with GDK, don't forget to link against `libsampgdk`, e.g. pass`-lsampgdk` flag to GCC.

Bugs
----

Report bugs here: https://github.com/Zeex/sampgdk/issues.

