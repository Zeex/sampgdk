TOP = ..

lib_LTLIBRARIES = libsampgdk.la
libsampgdk_la_SOURCES =\
	$(TOP)/src/amxhooks.cpp\
	$(TOP)/src/amxplugin.cpp\
	$(TOP)/src/callbacks.cpp\
	$(TOP)/src/core.cpp\
	$(TOP)/src/fakeamx.cpp\
	$(TOP)/src/gpci.cpp\
	$(TOP)/src/jump-x86.cpp\
	$(TOP)/src/natives.cpp\
	$(TOP)/src/objects.cpp\
	$(TOP)/src/players.cpp\
	$(TOP)/src/samp.cpp\
	$(TOP)/src/timers.cpp\
	$(TOP)/src/vehicles.cpp\
	$(TOP)/src/version.cpp
libsampgdk_la_CPPFLAGS = -DLINUX -I$(TOP)/include

# Example plugins
noinst_LTLIBRARIES = lvdm.la helloworld.la

PLUGIN_LDFLAGS = -module -avoid-version -rpath /wtf
PLUGIN_CPPFLAGS = -DLINUX -Iinclude

lvdm_la_SOURCES = $(TOP)/examples/lvdm/lvdm.cpp
lvdm_la_LIBADD = libsampgdk.la
lvdm_la_CPPFLAGS = $(PLUGIN_CPPFLAGS)
lvdm_la_LDFLAGS = $(PLUGIN_LDFLAGS)

helloworld_la_SOURCES = $(TOP)/examples/helloworld/helloworld.cpp
helloworld_la_LIBADD = libsampgdk.la
helloworld_la_CPPFLAGS = $(PLUGIN_CPPFLAGS)
helloworld_la_LDFLAGS = $(PLUGIN_LDFLAGS)
