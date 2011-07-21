CXX=g++

.PHONY: all debug release build clean

all: release

CPPFLAGS = -DLINUX -DHAVE_STDINT_H -Isamp/plugin/amx

debug: CXXFLAGS = -c -g -Wall 
debug: build

release: CXXFLAGS = -c -O2 
release: build

CXXFLAGS = $(CFLAGS) 
LDFLAGS = -fPIC -shared

VPATH = samp:samp/plugin:samp/plugin/amx

OBJECTS = callbacks.o eventhandler.o logprintf.o objects.o players.o\
          samp.o vehicles.o wrapper.o fakeamx.o jump.o amxplugin.o\
          helloworld.o
OUTFILE = helloworld.so

build: $(OUTFILE)

$(OUTFILE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -vf $(OBJECTS) $(OUTFILE)

