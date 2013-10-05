#ifndef BEAT_MANAGER_H
#define BEAT_MANAGER_H

#include "sprite.h"

class BeatManager {

  public:
    BeatManager();
    ~BeatManager();
    void tick();
    void draw();
    void update();
		bool enemyAlive();
  private:
    unsigned int time;
    int HEIGHT;
    int WIDTH;
    Sprite * leftArrowSprite;
    Sprite * rightArrowSprite;
    Sprite * upArrowSprite;
    Sprite * downArrowSprite;
   
};

#endif
