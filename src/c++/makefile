# author: Anthony Castiglia

LDLIBS = -lGLEW -lGL

CC = g++
CFLAGS = -c -Wall $(DEBUG) 
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = $(LDLIBS)
LFLAGS = $(LIBFLAGS) -Wall $(DEBUG)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)

OBJS = GLHelper.o

# all: $(MAIN)
all: GLHelper.o

# _.o: _.h _.cpp
# 	$(CC) $(CFLAGS) _.cpp

GLHelper.o: GLHelper.h GLHelper.cpp
	$(CC) $(CFLAGS) GLHelper.cpp


$(MAIN): $(OBJS)
	$(CC) $(OBJS) $(LFLAGS) -o $(MAIN)

debug:
	$(MAKE) $(MAKEFILE) DEBUG="-g"

clean:
	rm -rf *.o $(MAIN) $(SUBMISSION) 
