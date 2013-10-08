#ifndef BEAT_MANAGER_H
#define BEAT_MANAGER_H

#include <list>
#include <allegro5/allegro.h>
#include "sprite.h"
#include "beat.h"
#include "player.h"

using std::list;


class BeatManager {

  public:
    BeatManager(RhythmPlayer &player, unsigned int offset);
    ~BeatManager();
    void tick();
    void draw();
    void update();
		bool isGameOver();
    void interpretEvent(ALLEGRO_EVENT e);
	private:
    list<Beat *> activeBeats;
    list<Beat *> missedBeats;
		unsigned int offset;
		unsigned int time;
    int HEIGHT;
    int WIDTH;
		RhythmPlayer &player;
};

#endif
