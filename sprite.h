#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <allegro5/allegro.h>
#include "drawable.h"

using std::string;

class Sprite : public Drawable
{
  public:
    Sprite(string name);
    ~Sprite();
    virtual void draw(int x,  int y);
  private:
    ALLEGRO_BITMAP *image;
};

#endif
