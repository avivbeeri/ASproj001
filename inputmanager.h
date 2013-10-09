#include <allegro5/allegro.h>

class InputManager {

  public:
    bool isKeyDown(KEY key);
    void onEvent(ALLEGRO_EVENT ev);
  private:
    ALLEGRO_KEYBOARD_STATE  state; 
}
