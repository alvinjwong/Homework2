CXX = g++
CXXFLAGS = -std=c++20 -Wall

all: event_management

event_management: event.o
	$(CXX) $(CXXFLAGS) event.o -o event_management

event.o: event.cpp
	$(CXX) $(CXXFLAGS) -c event.cpp

run: all
	./event_management

clean:
	rm -f *.o event_management