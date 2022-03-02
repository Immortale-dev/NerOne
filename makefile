.PHONY: all generate_o generate_t

CC=g++
OPT=-g
CFLAGS=-c -Wall -std=c++14 
LDFLAGS=
SRCPATH:=src/
SRCS:=$(wildcard $(SRCPATH)*.cpp)
OBJS:=$(SRCS:%.cpp=%.o)

INCL=-Isrc -Itest

all: generate_o generate_t

generate_o: ${OBJS}

generate_t:
	$(CC) $(CFLAGS) $(INCL) test/test.cpp ${OPT} -o test/test.o
	${CC} ${INCL} -o test.exe test/test.o ${OBJS}

custom: generate_o
	$(CC) $(CFLAGS) $(INCL) test/mtest.cpp -o test/mtest.o
	${CC} ${INCL} -o mtest.exe test/mtest.o ${OBJS}

%.o: %.cpp
	${CC} ${CFLAGS} ${INCL} ${OPT} $< -o $@
