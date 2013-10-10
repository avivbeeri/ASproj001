CXX = g++
CXXFLAGS = -Wall 
ALLEGRO_LIBS = allegro-5.0 allegro_primitives-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_audio-5.0 allegro_acodec-5.0

.PHONY: clean

all: game

game: main.o
	$(CXX) $(CXXFLAGS) `pkg-config --libs $(ALLEGRO_LIBS)` -o game main.o player.o sound.o inputmanager.o entity.o beat.o sprite.o bitmap.o globals.o beatmanager.o track.o

main.o: main.cpp player.o sound.o inputmanager.o drawable.o entity.o beat.o sprite.o bitmap.o globals.o beatmanager.o track.o

track.o: track.h sprite.h drawable.h

beatmanager.o: beatmanager.h beat.h entity.h sprite.h player.h

globals.o: globals.h inputmanager.h sprite.h 

bitmap.o: bitmap.h drawable.h

sprite.o: sprite.h drawable.h

beat.o: beat.h entity.h inputmanager.h

entity.o: entity.h drawable.h

drawable.o: drawable.h

inputmanager.o: inputmanager.h globals.h

sound.o: sound.h

player.o: player.h

clean:
	rm -rf *o game
