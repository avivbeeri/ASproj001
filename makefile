all: game

game:  main.o
	g++ main.o -o game `pkg-config --libs allegro-5.0 allegro_primitives-5.0`

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *o game
