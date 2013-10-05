#ifndef BEAT_H
#define BEAT_H

#include "entity.h"

class Beat : public Entity {

  public:
	  Beat(KEY type);
	  ~Beat();
		virtual void update();
		bool keyPressEvent(ALLEGRO_EVENT e);
  private:
	  KEY type; 
	  
};

#endif
