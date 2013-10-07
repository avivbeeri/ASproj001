#ifndef BEAT_MANAGER_H
#define BEAT_MANAGER_H

#include <list>
#include <allegro5/allegro.h>
#include "sprite.h"
#include "beat.h"

using std::list;


class BeatManager {

  public:
    BeatManager();
    ~BeatManager();
    void tick();
    void draw();
    void update();
		bool isGameOver();
    void interpretEvent(ALLEGRO_EVENT e);
	private:
    list<Beat *> activeBeats;
    list<Beat *> missedBeats;
		unsigned int time;
    int HEIGHT;
    int WIDTH;
};

#endif
