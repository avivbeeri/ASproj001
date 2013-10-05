#include "beat.h"
#include "globals.h"
#include <iostream>

Beat::Beat(KEY type):
  Entity()
{
  this->type = type;  
}

Beat::~Beat() {
  //Empty
}

void Beat::update() {
	y += 4;
  if (y > HEIGHT) {
		setLive(false);
    y = 0;
	}
  
}

bool Beat::correctKey(ALLEGRO_EVENT ev) {
 //Returns true if the beat was hit correctly, 
 //otherwise return false. 
	if ((y > SLOT_TOP && y < SLOT_BOTTOM) &&
      (ev.type == ALLEGRO_EVENT_KEY_DOWN)) {
		
		setLive(false);
		y = 0;
		switch(ev.keyboard.keycode) {
      case ALLEGRO_KEY_UP: 
        return type == UP;
				break;
      case ALLEGRO_KEY_DOWN: 
        return type == DOWN;
				break;
      case ALLEGRO_KEY_LEFT:
			  x += 100; 
        return type == LEFT;
				break;
      case ALLEGRO_KEY_RIGHT: 
        return type == RIGHT;
				break;
      case ALLEGRO_KEY_A: 
        return type == KEY_A;
				break;
      case ALLEGRO_KEY_S: 
        return type == KEY_S;
				break;
      case ALLEGRO_KEY_D: 
        return type == KEY_D;
				break;
      case ALLEGRO_KEY_F: 
        return type == KEY_F;
				break;
		  default:
			  return false;	      
    }
  } else {
    //outside the box, you fail too!
	}
}
