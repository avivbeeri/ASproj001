#include "beat.h"
#include "globals.h"

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
		  break;
	}

}

Beat::~Beat() {
  //Empty
}

void Beat::update() {
	y += 4;
  if (y > HEIGHT) {
		setLive(false);
		missed = true;
    y = 0;
	}
  
}

bool Beat::correctKey(ALLEGRO_EVENT ev) {
  //Returns true if the keypress is valid
	//  this->missed is set to true if the press was incorrect, due to earlyness, lateness or incorrect button.
  //otherwise return false, value of missed is irrelevant.
	 
  bool validPress = false;
	if ((y > SLOT_TOP && y < SLOT_BOTTOM) &&
      (ev.type == ALLEGRO_EVENT_KEY_DOWN)) {
		bool result = false;
		switch(ev.keyboard.keycode) {
      case ALLEGRO_KEY_UP: 
        result = (type == UP);
				validPress = true;
				break;
      case ALLEGRO_KEY_DOWN: 
        result =  (type == DOWN);
				validPress = true;
				break;
      case ALLEGRO_KEY_LEFT:
        result = (type == LEFT);
				validPress = true;
				break;
      case ALLEGRO_KEY_RIGHT: 
        result = (type == RIGHT);
				validPress = true;
				break;
      case ALLEGRO_KEY_A: 
        result = (type == KEY_A);
				validPress = true;
				break;
      case ALLEGRO_KEY_S: 
        result = (type == KEY_S);
				validPress = true;
				break;
      case ALLEGRO_KEY_D: 
        result = (type == KEY_D);
				validPress = true;
				break;
      case ALLEGRO_KEY_F: 
        result = (type == KEY_F);
				validPress = true;
				break;
		  default:
			  //do nothing
				validPress = false;
				result = false;
				return false;    
    }

		missed = !result;
		setLive(!validPress);
		return validPress;
	} else if ((y < SLOT_TOP || y > SLOT_BOTTOM) &&
      (ev.type == ALLEGRO_EVENT_KEY_DOWN)) {
		switch(ev.keyboard.keycode) {
      case ALLEGRO_KEY_UP: 
				validPress = true;
				break;
      case ALLEGRO_KEY_DOWN: 
				validPress = true;
				break;
      case ALLEGRO_KEY_LEFT:
				validPress = true;
				break;
      case ALLEGRO_KEY_RIGHT: 
				validPress = true;
				break;
      case ALLEGRO_KEY_A: 
				validPress = true;
				break;
      case ALLEGRO_KEY_S: 
				validPress = true;
				break;
      case ALLEGRO_KEY_D: 
				validPress = true;
				break;
      case ALLEGRO_KEY_F: 
				validPress = true;
				break;
		  default:
			  //do nothing
				validPress = false;
    }

		missed = true;	  
    return validPress;
	} else if (ev.type != ALLEGRO_EVENT_KEY_DOWN) {  
	  //timer event, do nothing for now	
		validPress = false;
  } else {
    //outside the box, you fail too!
		validPress = false;
	}
	return false;
}
