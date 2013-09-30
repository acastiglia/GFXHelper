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
OBJS = ../GFXUtil.o ../GFX.o

all: main

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

main: $(OBJS) main.o
	$(CC) -o main $(OBJS) main.o $(LFLAGS) 

test.o: test.cpp
	$(CC) $(CFLAGS) test.cpp

test: test.o
	$(CC) $(CFLAGS) $(OBJS) test.o 

debug:
	$(MAKE) $(MAKEFILE) DEBUG="-g"
clean:
	rm -f *.o main
