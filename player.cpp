#include "player.h"

RhythmPlayer::RhythmPlayer() {
  maxHP = 100;
  HP = maxHP;
	mana = 0;
  level = 1;
}

RhythmPlayer::~RhythmPlayer() {
  //Empty destructor
}

void RhythmPlayer::takeDamage(int dmg) {
  HP -= dmg;
	if (HP < 0) HP = 0;
}

void RhythmPlayer::heal(int value) {
  HP += value;
	if (HP > maxHP) HP = maxHP;
}


void RhythmPlayer::reset() {
  HP = maxHP;
  mana = 0;
  level = 1;
}
