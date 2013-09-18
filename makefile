all: game

game:  main.o
	g++ main.o -o game -I/usr/include/allegro5 -L/usr/lib -lallegro

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *o game
