# Makefile for the sim

OPTIONS = -Wall -ggdb -Iinc -I. -lpthread

OBJECTS = simpleserver_socket.o simpleserver_log.o

all: socket_test log_test;

%.o: src/%.cpp
	g++ $(OPTIONS) -c $? -o $@

%_test: $(OBJECTS) ../test/simpleserver_%_test.cpp
	g++ $(OPTIONS) $? -o $@

clean:
	rm -rf *.o *_test
