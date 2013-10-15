#include "beat.h"
#include "globals.h"
#include <iostream>

Beat::Beat(KEY type):
  Entity()
{
  this->type = type;  
  switch(type) {
    case UP: 
		  setSprite(upArrowSprite);
		  break;
    case DOWN: 
		  setSprite(downArrowSprite);
		  break;
    case RIGHT: 
		  this->setSprite(rightArrowSprite);
		  break;
    case LEFT: 
		  this->setSprite(leftArrowSprite);
		  break;
	  default:
		  setSprite(NULL);
			break;
	}

}

void Beat::update() {
	std::cout << "BEAT.updating" << std::endl;
  y += 4;
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
