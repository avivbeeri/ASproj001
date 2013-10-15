#ifndef BEAT_MANAGER_H
#define BEAT_MANAGER_H

#include <list>
#include <allegro5/allegro.h>


class RhythmLevel;

#include "sprite.h"
#include "beat.h"
#include "tuple.h"
#include "player.h"




using std::list;


class BeatManager {

  public:
    BeatManager(RhythmPlayer &player, unsigned int offset);
    ~BeatManager();
    void tick();
    void draw();
    void update();
		void playLevel(RhythmLevel * level);
    bool isGameOver();
    void onEvent(ALLEGRO_EVENT e);
		void publishTuple(Tuple t);
	private:
    list<Beat *> activeBeats;
    list<Beat *> missedBeats;
		RhythmPlayer &player;
    unsigned int offset;
		unsigned int time;
    int HEIGHT;
    int WIDTH;
    int directionTest;
		RhythmLevel * level;
};

#endif
