#ifndef GLOBALS_H
#define GLOBALS_H

enum KEY { UP, DOWN, LEFT, RIGHT, KEY_A, KEY_S, KEY_D, KEY_F, SPACE, ESCAPE, EMPTY};


#include "sprite.h"


extern const float FPS;
extern const int HEIGHT;
extern const int WIDTH;
extern const int SLOT_TOP;
extern const int SLOT_BOTTOM;

extern const int arrowOffset;
extern const int edgeWidth;

extern Sprite * leftArrowSprite;
extern Sprite * rightArrowSprite;
extern Sprite * downArrowSprite;
extern Sprite * upArrowSprite;
extern int uToInt(unsigned int x);

class InputManager;
extern InputManager * inputManager;

#endif
