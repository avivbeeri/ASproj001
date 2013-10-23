#include "globals.h"


const int SLOT_HEIGHT = 35;

const float FPS = 60;
const int HEIGHT = 600;
const int WIDTH = 1024;
const int SLOT_TOP = HEIGHT - 160;
const int SLOT_BOTTOM = SLOT_TOP + SLOT_HEIGHT;

const int edgeWidth = 10;
const int arrowOffset = 40 + edgeWidth + 10;
//40 for the image (dynamic later)
//10 for the the edges of the image, 5 pixels each side

Sprite * leftArrowSprite;
Sprite * rightArrowSprite;
Sprite * upArrowSprite;
Sprite * downArrowSprite;

InputManager * inputManager;
