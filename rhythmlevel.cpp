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

void RhythmLevel::end() {
  song->stop();
  reset();
}

void RhythmLevel::tick() {
  ticks++;
  if (ticks >= FPS) {
    songPosition++;
    ticks = 0;
  }
}

void RhythmLevel::onEvent(ALLEGRO_EVENT ev) {
  if (ev.type == ALLEGRO_EVENT_TIMER) {
    tick();

    if (songPosition == (songLength / 2)) {
      song->play();
    }
  }
}

Beat * RhythmLevel::getNextBeat() {
  switch (songPosition % 4) {
    case 0: return new Beat(LEFT);
		case 1: return new Beat(UP);
		case 2: return new Beat(DOWN);
		case 3: return new Beat(RIGHT);
	  default: return NULL;
	}

	
	
}

bool RhythmLevel::levelComplete() {
  return (enemyHP == 0) || (songPosition == songLength);
}
