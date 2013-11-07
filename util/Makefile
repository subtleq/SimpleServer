# Makefile for the sim

all: socket_test log_test;

%.0: %.cpp
	g++ -Wall -ggdb $? -o $@

%_test: simpleserver_%.o ../test/simpleserver_%_test.cpp
	g++ -Wall -I. -ggdb $? -o $@

clean:
	rm -rf *.o socket_test
