#include "beat.h"
#include "globals.h"

Beat::Beat(KEY type):
  Entity()
{
  this->type = type;  
}

Beat::~Beat() {
  //Empty
}

void Beat::update() {
  y += 1;
}

bool Beat::correctKey(ALLEGRO_EVENT e) {
 //Returns true if the beat was hit correctly, 
 //otherwise return false. 
  return (y > SLOT_TOP && y < SLOT_BOTTOM);

}
