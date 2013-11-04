# Makefile for the sim

all: socket_test;

%.0: %.cpp
	g++ -Wall -ggdb $? -o $@

socket_test: simpleserver_socket.o simpleserver_socket_test.cpp
	g++ -Wall -ggdb $? -o $@

clean:
	rm -rf *.o socket_test
