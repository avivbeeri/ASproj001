all: game

game:  main.o entity.o bitmap.o sprite.o player.o
	g++ main.o entity.o bitmap.o sprite.o player.o -o game `pkg-config --libs allegro-5.0 allegro_primitives-5.0 allegro_image-5.0 allegro_font-5.0`

main.o: main.cpp
	g++ -c main.cpp

bitmap.o: bitmap.cpp
	g++ -c bitmap.cpp

entity.o: entity.cpp
	g++ -c entity.cpp
	
sprite.o: sprite.cpp
	g++ -c sprite.cpp

player.o: player.cpp
	g++ -c player.cpp

clean:
	rm -rf *o game
