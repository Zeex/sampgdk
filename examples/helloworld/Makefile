# HelloWorld makefile

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
LDFLAGS += -Wl,--kill-at --def helloworld.def
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
helloworld = helloworld.dll
else
helloworld = helloworld.so
endif

all: $(helloworld)

$(helloworld): helloworld.o
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -vf helloworld.o $(helloworld)
