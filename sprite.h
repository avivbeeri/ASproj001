#ifndef SPRITE_H
#define SPRITE_H

#include <allegro5/allegro.h>
#include "drawable.h"

class Sprite : public Drawable
{
  public:
    Sprite(char * str);
    ~Sprite();
    virtual void draw(int x,  int y);
  private:
    ALLEGRO_BITMAP *image;
};

#endif
