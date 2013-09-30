all: game

game:  main.o entity.o bitmap.o sprite.o
	g++ main.o entity.o bitmap.o sprite.o -o game `pkg-config --libs allegro-5.0 allegro_primitives-5.0`

main.o: main.cpp
	g++ -c main.cpp

bitmap.o: bitmap.cpp
	g++ -c bitmap.cpp

entity.o: entity.cpp
	g++ -c entity.cpp
	
sprite.o: sprite.cpp
	g++ -c sprite.cpp


clean:
	rm -rf *o game
