CXX=clang++
CXXFLAGS=-g -std=c++11 -Wall -pedantic
BIN=prog

OBJS = main.o items.o

master: $(OBJS)
	g++ -o $@ $(OBJS)

%.o: %.c items.h
	g++ -c $*.c

clean:
	rm *.o master

run:
	./master
