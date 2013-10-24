#include "sound.h"
#include "globals.h"

Sound::Sound(const string filename) {

  if (!al_is_audio_installed()) {
    exit(-1);
	}
  sample = al_load_sample(filename.c_str());

}

Sound::~Sound() {
  al_destroy_sample(sample);
}

bool Sound::play(ALLEGRO_PLAYMODE mode) {
  playing = al_play_sample(sample, 1.0, 0.0, 1.0, mode, &id);
	timeStarted = al_get_time();
  return playing;
}

void Sound::stop() {
  if (playing) {
    al_stop_sample(&id);
		playing = false;
	}
}

double Sound::getLength() {
  int length = uToInt(al_get_sample_length(sample));
  int frequency = uToInt(al_get_sample_frequency(sample));
  return length / (double) frequency;
//  return 1;
}

double Sound::getPosition() {
  if (al_get_time() > getLength()) {
    playing = false;
  }
  return al_get_time() - timeStarted;
}
