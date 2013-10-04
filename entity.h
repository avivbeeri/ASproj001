#ifndef ENTITY_H
#define ENTITY_H

#include "drawable.h"

class Entity
{
  public:
    Entity();
    Entity(int x, int y);
    ~Entity(); 
    void setLive(bool live);
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();
    bool isLive();
    void setSprite(Drawable * sprite);
    void update();
    void draw();
  private:
    int x;
    int y;
    bool live;
    Drawable * sprite;
};

#endif
