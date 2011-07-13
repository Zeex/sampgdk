CC=gcc
CXX=g++

DEFINES=-DLINUX -DHAVE_STDINT_H
INCLUDES=-Isamp/plugin/amx

.PHONY: all debug release build clean

all: release

debug: CFLAGS=-c -g $(DEFINES) $(INCLUDES)
debug: build

release: CFLAGS=-c -w -O2 $(DEFINES) $(INCLUDES)
release: build

CXXFLAGS=$(CFLAGS) -std=c++0x
LDFLAGS=-fPIC -shared

VPATH=samp:samp/internal:samp/plugin:samp/plugin/amx

OBJECTS=callbacks.o eventhandler.o logprintf.o objects.o players.o\
        samp.o vehicles.o wrapper.o fakeamx.o jump.o amxplugin.o\
        helloworld.o
OUTFILE=helloworld.so

build: $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -vf $(OBJECTS) $(OUTFILE)

