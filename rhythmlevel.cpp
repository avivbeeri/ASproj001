#include "rhythmlevel.h"

RhythmLevel::RhythmLevel():
  songPosition(0),
  enemyHP(15)
  
{
  song = new Sound("assets/music/loz.wav");
  songLength = song->getLength() * 2;
}

void RhythmLevel::reset() {
  songPosition = 0;
  enemyHP = 15;
}

void RhythmLevel::begin() {
  song->play();
}

void RhythmLevel::onEvent(ALLEGRO_EVENT ev) {
  if (ev.type == ALLEGRO_EVENT_TIMER) {
    songPosition++;
    if (songPosition == (songLength / 2)) {
      song->play();
    }
  }
}

Beat * RhythmLevel::getNextBeat() {
  return new Beat(LEFT);
}

bool RhythmLevel::levelComplete() {
  return (enemyHP == 0) || (songPosition == songLength);
}
