CXX = g++
CXXFLAGS = -Wall -g
ALLEGRO_LIBS = allegro-5.0 allegro_primitives-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_audio-5.0 allegro_acodec-5.0

.PHONY: clean

all: game

game: main.o
	$(CXX) $(CXXFLAGS) `pkg-config --libs $(ALLEGRO_LIBS)` -o game main.o globals.o beat.o entity.o bitmap.o sprite.o player.o track.o beatmanager.o inputmanager.o sound.o


main.o: main.cpp sound.o globals.o entity.o bitmap.o sprite.o player.o track.o beatmanager.o beat.o inputmanager.o

track.o: track.h sprite.h bitmap.h drawable.h

beatmanager.o: beatmanager.h beat.h player.h entity.h sprite.h

beat.o: beat.h entity.h inputmanager.h
	
globals.o: globals.h inputmanager.h sprite.h 

bitmap.o: bitmap.h drawable.h

sprite.o: sprite.h

player.o: player.h

entity.o: entity.h drawable.h

drawable.o: drawable.h

sound.o: sound.h

inputmanager.o: inputmanager.h globals.h

clean:
	rm -rf *o game
