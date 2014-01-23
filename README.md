SA-MP Gamemode Development Kit
==============================

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

Visit the official SA-MP forums topic for more information and support:
http://forum.sa-mp.com/showthread.php?t=421090

Source code
-----------

The source code is hosted at [GitHub][github].

Downloads
---------

Binary packages for Windows and Linux can be downloaded [here][download].

Getting started
---------------

You can begin with downloading the source code and playing a bit with the
helloworld plugin in plugins/helloworld/.

If you know Git the simplest way to get started is probably to clone this repo
and create a new branch for your personal project like `my-project`, and then
just start developing your own plugin right inside the GDK's source tree. Later
if you decide to update the library you would simply switch to  `master`, pull
in the changes and merge them into `my-project`.

[donate]: http://pledgie.com/campaigns/19068
[donate_button]: http://pledgie.com/campaigns/19068.png
[build]: https://travis-ci.org/Zeex/sampgdk
[build_status]: https://travis-ci.org/Zeex/sampgdk.png?branch=master
[download]: http://zeex.github.com/sampgdk
[github]: https://github.com/Zeex/sampgdk
