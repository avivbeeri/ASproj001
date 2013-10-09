#include <string>
#include "track.h"
#include "sprite.h"

using std::string;

Track::Track() {
  track_sprite = new Sprite("assets/art/track.png");
  trackend_sprite = new Sprite("assets/art/track.png");
}

Track::~Track() {
  delete trackend_sprite;
  delete track_sprite;
}

void Track::draw(int x, int height) {
  
  track_sprite->draw(x,height - 100);
  trackend_sprite->draw(x,height- 2*100);
  for (int i = height - 3*100; i > 0; i--) {
    track_sprite->draw(x,height -  (i + 2)*100);
  }
}



