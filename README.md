SA-MP Gamemode Development Kit
==============================

GDK allows you to easily create SA-MP gamemodes in C or C++ and load them as server plugins. 

Installation
------------

*	Windows
	1.	Download and install `libsampgdk-x.y.z-win32.exe`. 
	2.	Don't forget to check *Add sampgdk to the system PATH* option - otherwise you will have to 
		copy the .dll into your server's folder or change PATH variable manually.
	3.	Set proper include and library paths in your IDE.

*	Linux
	1.	Download `libsampgdk-x.y.z-Linux.sh`.
	2.	Run it as follows: `sudo sh sampgdk-x.y.z-Linux.sh --prefix=/usr/local/`. This will install
		the library and headers to /usr/local/lib and /usr/local/include respectively.
	3.	Link against libsampgdk.

Bugs
----

Report bugs here: https://github.com/Zeex/sampgdk/issues.

