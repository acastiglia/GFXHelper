
CC = g++
CFLAGS = -c -Wall $(DEBUG) 

LDLIBS = -lglfw -lGLEW
LIBFLAGS = $(LDLIBS)
LFLAGS = $(LIBFLAGS) -Wall $(DEBUG)
OBJS = GLHelper.o test.o

all: build 

build: 
	cd src/c++; make

test.o: test.cpp 
	$(CC) $(CFLAGS) test.cpp

test: $(OBJS)
	$(CC) -o test $(OBJS) $(LFLAGS)
clean: 
	rm -f *.o *.h
