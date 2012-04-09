# unlimitedfs makefile

CXX = g++

ifeq ($(os),windows)
CPPFLAGS += -D_WIN32 -I"$(SAMPGDK_HOME)\include"
endif

ifeq ($(os),linux)
CPPFLAGS += -DLINUX 
endif

ifndef config
config = release
endif

ifeq ($(config),debug)
CXXFLAGS += -g -Wall
endif

ifeq ($(config),release)
CXXFLAGS += -O3
endif

CXXFLAGS += -m32
CXXFLAGS += -Wno-attributes

ifeq ($(os),windows)
LDFLAGS += -Wl,--kill-at --def unlimitedfs.def
LDFLAGS += "$(SAMPGDK_HOME)\bin\sampgdk2.dll"
LDFLAGS += -static-libgcc 
LDFLAGS += -static-libstdc++
endif

ifeq ($(os),linux)
LDFLAGS += -lsampgdk
endif

LDFLAGS += -m32
LDFLAGS += -shared
LDFLAGS += -Wl,--no-undefined

ifeq ($(os),windows)
unlimitedfs = unlimitedfs.dll
else
unlimitedfs = unlimitedfs.so
endif

all: $(unlimitedfs)

objects += filterscript.o
objects += plugin.o
objects += unlimitedfs.o

ifeq ($(os),windows)
objects += dlfcn.o
endif

$(unlimitedfs): $(objects)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -vf unlimitedfs.o $(unlimitedfs)
