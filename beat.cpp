#include "beat.h"

Beat::Beat(KEY type):
  Entity();
{
  
}

Beat::~Beat() {
  //Empty
}

virtual void Beat::update() {
  y += 1;
}

bool Beat:correctKey(ALLEGRO_EVENT e) {
 //Returns true if the beat was hit correctly, 
 //otherwise return false. 
  return (y - (HEIGHT - 200) < 50);

}
