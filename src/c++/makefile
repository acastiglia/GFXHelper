# author: Anthony Castiglia

LDLIBS = -lglfw -lGLEW -lGL

CC = clang++ -std=c++0x
CFLAGS = -c -Wall $(DEBUG) 
CCFLAGS =  $(CFLAGS)
CXXFLAGS = $(CFLAGS)

LIBFLAGS = $(LDLIBS)
LFLAGS = $(LIBFLAGS) -Wall $(DEBUG)
CLIBFLAGS = $(LIBFLAGS)
CCLIBFLAGS = $(LIBFLAGS)

BUILDDIR = ../../
OBJS = GFXUtil.o 

all: GFXUtil.o GFX.o

GFXUtil.o: GFXUtil.h GFXUtil.cpp
	$(CC) $(CFLAGS) GFXUtil.cpp

GFX.o: GFX.h GFXUtil.h GFX.cpp
	$(CC) $(CFLAGS) GFX.cpp

debug:
	$(MAKE) $(MAKEFILE) DEBUG="-g"

# deploy: $(LIBS)
# 	mv -t ../../lib/ $(LIBS)
# 	cp -t ../../include GLHelper.h

clean:
	rm -f *.o 
