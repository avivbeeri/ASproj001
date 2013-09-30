#include <allegro5/allegro.h>
#include "sprite.h"
	
Sprite::Sprite(char * str) {
	//file existence error checking
	image = al_load_bitmap(str);
}

Sprite::~Sprite() {
	al_destroy_bitmap(image);
}

void Sprite::draw(int x, int y) {
  al_draw_bitmap(image, x, y, 0);
}

