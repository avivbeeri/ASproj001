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
		bool play(ALLEGRO_PLAYMODE mode = ALLEGRO_PLAYMODE_ONCE);
	  void stop();
	  unsigned int getLength();
    bool isPlaying() { return playing; }
  private:
	  bool playing;
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_ID id;
};

#endif
