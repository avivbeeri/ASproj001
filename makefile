CXX = g++
CXXFLAGS = -Wall 
ALLEGRO_LIBS = allegro-5.0 allegro_primitives-5.0 allegro_image-5.0 allegro_font-5.0 allegro_ttf-5.0 allegro_audio-5.0 allegro_acodec-5.0

.PHONY: clean

all: game

game: main.o
	$(CXX) $(CXXFLAGS) `pkg-config --libs $(ALLEGRO_LIBS)` -o game main.o player.o sound.o timeout.o inputmanager.o entity.o beat.o rhythmlevel.o sprite.o bitmap.o globals.o beatmanager.o track.o tuple.o

main.o: main.cpp player.o sound.o timeout.o inputmanager.o drawable.o entity.o beat.o rhythmlevel.o sprite.o bitmap.o globals.o beatmanager.o track.o tuple.o

track.o: track.h sprite.h drawable.h

rhythmlevel.o: rhythmlevel.h globals.h beat.h sound.h beatmanager.h tuple.h timeout.h

beatmanager.o: beatmanager.h beat.h entity.h sprite.h player.h tuple.h

tuple.o: tuple.h

beat.o: beat.h entity.h inputmanager.h globals.h

sound.o: sound.h globals.h

globals.o: globals.h inputmanager.h sprite.h 

bitmap.o: bitmap.h drawable.h

sprite.o: sprite.h drawable.h

entity.o: entity.h drawable.h

drawable.o: drawable.h

inputmanager.o: inputmanager.h globals.h

player.o: player.h

timeout.o: timeout.h

clean:
	rm -rf *o game
