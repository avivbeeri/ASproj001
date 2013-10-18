#ifndef TUPLE_H
#define TUPLE_H

#include <string>
#include "globals.h"


using std::string;
class Tuple {
  
	public:
    Tuple(KEY, KEY, KEY, KEY);
    Tuple(string data);
	  KEY getElement(int i);
    void output();
  private:
    KEY element[4];
};


#endif
