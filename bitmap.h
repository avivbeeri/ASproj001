#ifndef BITMAP_H
#define BITMAP_H

#include <allegro5/allegro.h>
#include "drawable.h"

class Bitmap : public Drawable
{
  public:
    Bitmap(ALLEGRO_BITMAP *ptr) { image = ptr; }
    virtual void draw(int x,  int y);
  private:
    ALLEGRO_BITMAP *image;
};

#endif
