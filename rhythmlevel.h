#ifndef RHYTHMLEVEL_H
#define RHYTHMLEVEL_H

#include <allegro5/allegro.h>
#include "beat.h"
#include "sound.h"
#include "globals.h"

class RhythmLevel {
  public:
    RhythmLevel();
    void reset();
    void onEvent(ALLEGRO_EVENT ev);
    void begin();
    void end();
    Beat * getNextBeat();
    bool levelComplete();
    unsigned int getTimeRemaining() { return songLength - songPosition; }
	private: 
    void tick();
    
    Sound * song;
    unsigned int ticks;
    unsigned int songLength;
    unsigned int songPosition;
    unsigned short enemyHP;
    //some song data storage of some sort
};

#endif
