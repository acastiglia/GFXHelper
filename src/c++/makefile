# author: Anthony Castiglia

LDLIBS = -lglfw -lGLEW -lGL

CC = g++
CFLAGS = -c -Wall $(DEBUG) 
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = $(LDLIBS)
LFLAGS = $(LIBFLAGS) -Wall $(DEBUG)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)

BUILDDIR = ../../
OBJS = GraphicsWindow.o util.o 
# LIBS = libGLHelper.a libGLHelper.so

all: main

util.o: util.h util.cpp
	$(CC) $(CFLAGS) util.cpp

GraphicsWindow.o: GraphicsWindow.h util.h GraphicsWindow.cpp
	$(CC) $(CFLAGS) GraphicsWindow.cpp

main: $(OBJS)
	$(CC) -o main $(OBJS) $(LFLAGS) 

# libGLHelper.a: $(OBJS)
# 	ar rcs libGLHelper.a $(OBJS)
# 
# libGLHelper.so: $(OBJS)
# 	g++ -shared -Wl -o libGLHelper.so $(OBJS)

debug:
	$(MAKE) $(MAKEFILE) DEBUG="-g"

# deploy: $(LIBS)
# 	mv -t ../../lib/ $(LIBS)
# 	cp -t ../../include GLHelper.h

clean:
	rm -f *.o
