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
	  double getLength();
	  double getPosition();
    bool isPlaying() { return playing; }
  private:
	  bool playing;
    double timeStarted;
    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_ID id;
};

#endif
