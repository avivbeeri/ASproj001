all: game

game:  main.o entity.o bitmap.o
	g++ main.o entity.o bitmap.o -o game `pkg-config --libs allegro-5.0 allegro_primitives-5.0`

main.o: main.cpp
	g++ -c main.cpp

bitmap.o: bitmap.cpp
	g++ -c bitmap.cpp

entity.o: entity.cpp
	g++ -c entity.cpp

clean:
	rm -rf *o game
