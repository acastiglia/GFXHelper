# author: Anthony Castiglia

LDLIBS = -lglfw -lGLEW -lGL

CC = clang++ -std=c++0x
CFLAGS = -c -Wall -I../ $(DEBUG) 
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = $(LDLIBS)
LFLAGS = -I../ $(LIBFLAGS) -Wall $(DEBUG)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)

BUILDDIR = ../../
OBJS = ../util.o ../GFX.o main.o
# LIBS = libGLHelper.a libGLHelper.so

all: main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

main: $(OBJS)
	$(CC) -o main $(OBJS) $(LFLAGS) 

debug:
	$(MAKE) $(MAKEFILE) DEBUG="-g"
clean:
	rm -f *.o main
