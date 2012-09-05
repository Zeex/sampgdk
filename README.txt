SA-MP Gamemode Development Kit
==============================

http://github.com/Zeex/sampgdk

This is a C/C++ port of the SA-MP Pawn API built on top of SA-MP plugin SDK.
It allows you to make gamemodes in C++ or pure C in the form of server plugins
and supports multiple plugins loaded at once i.e. there is no "main" plugin.


Installation
------------

For Microsoft Windows:

  1. Download sampgdk-x.y.z-win32.exe at https://github.com/Zeex/sampgdk/downloads.

  2. Run the installer and complete the setup.

     NOTE: Don't forget to turn on the *Add sampgdk to the system PATH* option,
     otherwise you will have to copy the .dll into your server's folder or
     change the system PATH manually.

  3. If you're planning to make a plugin you will have to add installation's
     include directory to the compiler's include path and lib to its library
     search path.

     For Visual Studio 2005+ this can be done through the Project Properties
     dialog (right-click on your project in Solution Explorer or press Alt-F7):
     
     * headers: "Project Properties" -> "C/C++" -> "General" -> "Additional
       Include Directories"

     * library: "Project Properties" -> "Linker" -> "Input" -> "Additional
       Dependencies"

For GNU/Linux:

  1. Download `sampgdk-x.y.z-Linux.sh` at https://github.com/Zeex/sampgdk/downloads.

  2. Run it as follows
  
     sudo sh sampgdk-x.y.z-Linux.sh --prefix=/usr/local
     
     This will install the shared library to /usr/local/lib and the headers to
     /usr/local/include. Of course you can change the prefix to whatever you want
     if you know what you're doing...

  3. If you're planning to make a plugin you will have to link against
     libsampgdk e.g. for GCC this can be done by adding "-lsampgdk" to link
     flags.


Bugs and other issues:
----------------------

http://github.com/Zeex/sampgdk/issues
