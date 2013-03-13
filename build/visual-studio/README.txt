These .vcxproj.user files add two things:

o A post-build event that copies your plugin or the GDK DLL (if you're building
  GDK) to $(SAMP_SERVER_ROOT)/plugins/ and $(SAMP_SERVER_ROOT)/ respectively.

o Set application command line and working directory in debugger options for you
  so you just hit F5 and get the SA-MP server started automatically.

Both files expect the SAMP_SERVER_ROOT environment variable to be set to the
root directory of the SA-MP server, e.g. C:\samp-server.

Note that the files should not be copied while Visual Studio is open because it
will overwrite them upon exit.

You'll need Visual Studio 2010 or later (Express edition is OK).
