#include "bitmap.h"

void Bitmap::draw(int x, int y) {
  al_draw_bitmap(image, x, y, 0);
}
