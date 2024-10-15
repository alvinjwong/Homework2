CXX = g++
CXXFLAGS = -std=c++20 -Wall

all: event_management

event_management: main.o
	$(CXX) $(CXXFLAGS) main.o -o event_management

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

run: all
	./event_management

clean:
	rm -f *.o event_management