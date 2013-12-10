# Makefile for the sim

OPTIONS = -Wall -ggdb -Iinc -I.

all: socket_test log_test;

%.o: src/%.cpp
	g++ $(OPTIONS) -c $? -o $@

%_test: simpleserver_%.o ../test/simpleserver_%_test.cpp
	g++ $(OPTIONS) $? -o $@

clean:
	rm -rf *.o socket_test
