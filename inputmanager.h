#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "globals.h"

class InputManager {

  public:
    InputManager();
    bool isPressed(KEY key);
    void onEvent(ALLEGRO_EVENT ev);
  private:
    ALLEGRO_KEYBOARD_STATE key_state; 
};

#endif
