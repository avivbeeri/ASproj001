#ifndef ENTITY_H
#define ENTITY_H

#include <allegro5/allegro.h>
#include "drawable.h"

class Entity
{
  public:
    Entity();
    Entity(int x, int y);
    virtual ~Entity(); 
    void kill();
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    bool isLive();
    void setSprite(Drawable * sprite);
    virtual void onEvent(ALLEGRO_EVENT ev);
    virtual void update();
    virtual void draw();
  protected:
    int x;
    int y;
    bool live;
	private:
    Drawable * sprite;
};

#endif
