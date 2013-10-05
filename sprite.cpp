#include <allegro5/allegro.h>
#include "sprite.h"
	
Sprite::Sprite(const string str) {
	//file existence error checking
	image = al_load_bitmap(str.c_str());
	if (image == NULL) {
		//Serious error, kill the game.
	}
}

Sprite::~Sprite() {
	al_destroy_bitmap(image);
}

void Sprite::draw(int x, int y) {
  al_draw_bitmap(image, x, y, 0);
}

