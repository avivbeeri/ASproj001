#ifndef TUPLE_H
#define TUPLE_H

#include "globals.h"

class Tuple {
  public:
    Tuple(KEY, KEY, KEY, KEY);
	  KEY getElement(int i);
    void output();
  private:
    KEY element[4];
};


#endif
