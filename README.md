SA:MP Gamemode Development Kit for C++
======================================

What's this?
------------

The SA:MP GDK allows one to easily create SA:MP gamemodes in C++ and load them as server plugins.
GDK is basically a wrapper around SA:MP's native scripting functions and callbacks. It does not
perform hardcore memory hacks and does not require the end user to run an extra .amx on their server
to make things work, thus it is highly portable across different server versions.


Quick Setup
-----------

### Download the source ###

Download the source code via GitHub Download interface and unpack it to a separate directory project.

Alternatively, you can use Git and clone the GDK repository:

`git clone git://github.com/Zeex/sampgdk.git`

### Connect to your project ###

There are ready-to-use projects for various IDE's which can be found in `projects` folder. 
It is generally recommended that you use these to compile the GDK. 
	
For instance, if you're using Microsoft Visual Studio 2010, just add `projects/vs2010/sampgdk.vcxproj` 
to your solution (the .sln) and setup include/library paths in your project's settings. 

To compile GDK on Linux you can use a Makefile from `projects/gmake`. I think you can even `include` it 
in your project's Makefile directly though I didn't try.

### Write some code ###

If you are new to GDK you may have a look at the helloworld example, it will teach you some basics.

Bugs
----

If you found a bug please create a new issue at https://github.com/Zeex/sampgdk/issues.

