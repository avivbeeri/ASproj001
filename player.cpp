#include "player.h"

RhythmPlayer::RhythmPlayer() {
  HP = 100;
  mana = 0;
  level = 1;
}

RhythmPlayer::~RhythmPlayer() {
  //Empty destructor
}


void RhythmPlayer::reset() {
  HP = 100;
  mana = 0;
  level = 1;
}
