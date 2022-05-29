all: run

State.o: State.h State.cpp
	g++ -g -w -std=c++11 -c State.cpp

run: ttt.cpp State.o 
	g++ -g -w -std=c++11 -o ttt ttt.cpp State.o -lpthread -lrt

clean: 
	rm -rf *.o ttt