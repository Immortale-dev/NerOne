.PHONY: all custom lib clear

CC=g++
OPT=-g
CFLAGS=-c -Wall -std=c++14
SRCPATH:=src/
SRCS:=$(wildcard $(SRCPATH)*.cpp)
OBJS:=$(SRCS:%.cpp=%.o)

# include LIBS flags
-include makefile.flags

LDFLAGS:=$(LIBS_LD)
INCL=-Isrc -Itest ${LIBS_INC}

all: test.exe

custom: mtest.exe

lib: liboutput.a

clear: ; $(RM) src/*.o test/*.o *.exe liboutput.a

liboutput.a: $(OBJS)
	$(RM) liboutput.a
	ar -qcT liboutput.a $(OBJS)

test.exe: liboutput.a test/test.o
	$(CC) -o test.exe test/test.o liboutput.a $(LDFLAGS) $(OPT)
	
mtest.exe: liboutput.a test/mtest.o
	$(CC) -o mtest.exe test/mtest.o liboutput.a $(LDFLAGS) $(OPT)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(INCL) $(OPT)