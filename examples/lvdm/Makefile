# LVDM makefile

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
LDFLAGS += -Wl,--kill-at --def lvdm.def
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
lvdm = lvdm.dll
else
lvdm = lvdm.so
endif

all: $(lvdm)

$(lvdm): lvdm.o
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -vf lvdm.o $(lvdm)
