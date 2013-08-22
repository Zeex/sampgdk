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

[donate]: http://pledgie.com/campaigns/19068
[donate_button]: http://pledgie.com/campaigns/19068.png
[download]: http://zeex.github.com/sampgdk
[github]: https://github.com/Zeex/sampgdk
