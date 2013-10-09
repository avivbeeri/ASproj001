#include "inputmanager.h"

void InputManager::onEvent(ALLEGRO_EVENT ev) {
   al_get_keyboard_state(&state);
}

bool InputManager::isKeyDown (KEY key) {
  switch(KEY) {
    case UP: 
			return al_key_down(&state, ALLEGRO_KEY_UP);
    case DOWN: 
			return al_key_down(&state, ALLEGRO_KEY_DOWN);
    case LEFT:
			return al_key_down(&state, ALLEGRO_KEY_LEFT);
    case RIGHT: 
			return al_key_down(&state, ALLEGRO_KEY_RIGHT);
    case KEY_A: 
			return al_key_down(&state, ALLEGRO_KEY_A);
    case KEY_S: 
			return al_key_down(&state, ALLEGRO_KEY_S);
    case KEY_D: 
			return al_key_down(&state, ALLEGRO_KEY_D);
    case KEY_F: 
			return al_key_down(&state, ALLEGRO_KEY_F);
    case ESCAPE:
			return al_key_down(&state, ALLEGRO_KEY_ESCAPE);
    case SPACE:
			return al_key_down(&state, ALLEGRO_KEY_SPACE);
	  default:
		  return false;
  }
}
