#ifndef TRACK_H
#define TRACK_H

#include "drawable.h"
#include "sprite.h"

class Track : public Drawable {
  public:
    Track();
    virtual ~Track();
    void draw(int x, int h);
  private:
    Sprite * track_sprite;
    Sprite * trackend_sprite;

};

#endif
