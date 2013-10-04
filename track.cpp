#include <string>
#include "track.h"
#include "sprite.h"

using std::string;

Track::Track() {
  string s = "assets/art/track.png";
  track_sprite = new Sprite(s);
  s = "assets/art/track_end.png";
  trackend_sprite = new Sprite(s);
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



