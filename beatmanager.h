#ifndef BEAT_MANAGER_H
#define BEAT_MANAGER_H

#include <allegro5/allegro.h>
#include "sprite.h"
#include "beat.h"


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
    unsigned int time;
    int HEIGHT;
    int WIDTH;
    Sprite * leftArrowSprite;
    Sprite * rightArrowSprite;
    Sprite * upArrowSprite;
    Sprite * downArrowSprite;
    Beat * test;
};

#endif
