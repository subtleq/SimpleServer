# Makefile for the sim

OPTIONS = -Wall -ggdb -Iinc -I. -lpthread

LIBRARY = libsimpleserver.a

OBJECTS = simpleserver_web.o

all: web_test;

%.o: src/%.cpp
	g++ $(OPTIONS) -c $? -o $@

%_test: $(OBJECTS) ../test/simpleserver_%_test.cpp
	g++ $(OPTIONS) $? -o $@

clean:
	rm -rf *.o *_test
