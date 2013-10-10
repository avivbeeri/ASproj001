#include "sound.h"

Sound::Sound(const string filename) {

  if (!al_is_audio_installed()) {
    exit(-1);
	}
  sample = al_load_sample(filename.c_str());

}

Sound::~Sound() {
  al_destroy_sample(sample);
}

void Sound::play(ALLEGRO_PLAYMODE mode) {
  al_play_sample(sample, 1.0, 0.0, 1.0, mode, NULL);
}
