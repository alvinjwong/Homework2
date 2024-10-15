Makefile:
all: main.o

	g++ main.o -o event_management

main.o: main.cpp

	g++ -c main.cpp
	
run: all

	./event_management

clean:

	rm *.o event_management