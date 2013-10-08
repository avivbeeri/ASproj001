#ifndef GLOBALS_H
#define GLOBALS_H

#include "sprite.h"
enum KEY { UP, DOWN, LEFT, RIGHT , ESCAPE, KEY_A, KEY_S, KEY_D, KEY_F, SPACE};

extern const float FPS;
extern const int HEIGHT;
extern const int WIDTH;
extern const int SLOT_TOP;
extern const int SLOT_BOTTOM;

extern Sprite * leftArrowSprite;
extern Sprite * rightArrowSprite;
extern Sprite * downArrowSprite;
extern Sprite * upArrowSprite;

#endif
