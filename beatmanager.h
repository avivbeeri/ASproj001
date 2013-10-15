#ifndef BEAT_MANAGER_H
#define BEAT_MANAGER_H

#include <list>
#include <allegro5/allegro.h>

#include "sprite.h"
#include "beat.h"
#include "tuple.h"
#include "player.h"

using std::list;

class BeatManager {

  public:
    BeatManager(RhythmPlayer &player, unsigned int offset);
    ~BeatManager();
    void draw();
    void onEvent(ALLEGRO_EVENT e);
		void emitTuple(Tuple t);
	private:
    list<Beat *> activeBeats;
    list<Beat *> missedBeats;
		RhythmPlayer &player;
    unsigned int offset;
		unsigned int time;
    int HEIGHT;
    int WIDTH;
    int directionTest;
};

#endif
