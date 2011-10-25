CXX      = g++
CPPFLAGS = -DLINUX 
CXXFLAGS = -m32 -fPIC -Wno-attributes 
LDFLAGS  = -m32 -shared -lsampgdk 

all: helloworld.so

helloworld.so: helloworld.o
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	rm -vf helloworld.o helloworld.so
