#ifndef SOUND_H
#define SOUND_H

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

using std::string;

class Sound {
  public:
    Sound(const string filename);
		~Sound();
		void play(ALLEGRO_PLAYMODE mode = ALLEGRO_PLAYMODE_ONCE);
	private:
    ALLEGRO_SAMPLE *sample;
};

#endif
