all: game

game:  globals.o main.o entity.o bitmap.o sprite.o player.o track.o beatmanager.o beat.o
	g++ globals.o main.o beat.o entity.o bitmap.o sprite.o player.o track.o  beatmanager.o -g -o game `pkg-config --libs allegro-5.0 allegro_primitives-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0`

globals.o: globals.cpp
	g++ -c globals.cpp

main.o: main.cpp
	g++ -c main.cpp

bitmap.o: bitmap.cpp
	g++ -c bitmap.cpp

beatmanager.o: player.o entity.o sprite.o beatmanager.cpp
	g++ -c beatmanager.cpp

beat.o: entity.o beat.cpp
	g++ -c beat.cpp -lentity.o

entity.o: entity.cpp
	g++ -c entity.cpp

track.o: sprite.o track.cpp
	g++ -c track.cpp
	
sprite.o: sprite.cpp
	g++ -c sprite.cpp

player.o: player.cpp
	g++ -c player.cpp

clean:
	rm -rf *o game
