Makefile:

default: all

all: main

main: main.cpp
	g++ -std=c++20 main.cpp -o main

run: all
	./main

clean:
	rm -f main