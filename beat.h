#ifndef BEAT_H
#define BEAT_H

#include <allegro5/allegro.h>
#include "globals.h"
#include "entity.h"

class Beat : public Entity {

  public:
	  Beat(KEY type);
	  ~Beat();
		virtual void update();
		bool wasMissed() { return missed; }
		bool correctKey(ALLEGRO_EVENT e);
  private:
	  KEY type; 
		bool missed;
};

#endif
