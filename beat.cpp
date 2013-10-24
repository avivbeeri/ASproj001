#include "beat.h"
#include "globals.h"
#include <iostream>

Beat::Beat(KEY type, double timePerBeat):
  Entity()
{
  this->type = type;  
  switch(type) {
    case UP: 
		  setX(15 + arrowOffset);
			setSprite(upArrowSprite);
		  break;
    case DOWN: 
		  setSprite(downArrowSprite);
		  setX(15 + 2 * arrowOffset);
		  break;
    case RIGHT: 
		  this->setSprite(rightArrowSprite);
		  setX(15 + 3 * arrowOffset);
		  break;
    case LEFT: 
		  setX(edgeWidth + 5);
		  this->setSprite(leftArrowSprite);
		  break;
	  default:
		  setSprite(NULL);
			break;
	}
  setY(-40);
  this->speed = ((1 / FPS) * (SLOT_TOP+40) / ((timePerBeat) * 4));
}

void Beat::update() {
  y += speed;
  if (y > HEIGHT) {
		kill();
		missed = true;
	}
  
}

bool Beat::onEvent(ALLEGRO_EVENT ev) {
	//this->missed is set to true if the press was incorrect 
  //due to earlyness, lateness or incorrect button.
	 
    if ((ev.type == ALLEGRO_EVENT_KEY_DOWN) &&
        (y > SLOT_TOP && y < SLOT_BOTTOM)) {
      
      /*on a key press, if the correct button was pressed
        while beat is in the right place, mark it for 
        destruction, and score points.*/

      if (inputManager->isPressed(type)) {
        kill();
        missed = false; 
        return true;
      }
    } else if (ev.type == ALLEGRO_EVENT_TIMER) {
			this->update();
    }
    return false;
}
