#include "tuple.h"
#include <iostream>

Tuple::Tuple(KEY k0, KEY k1, KEY k2, KEY k3) {
  element[0] = k0;
  element[1] = k1;
  element[2] = k2;
  element[3] = k3;
}

Tuple::Tuple(string lineData) {
  if (!lineData.at(0) == '0') {
    element[0] = LEFT;
	} else {
    element[0] = EMPTY;
	}
  if (!lineData.at(1) == '0') {
    element[1] = UP;
	} else {
    element[1] = EMPTY;
	}
  if (!lineData.at(2) == '0') {
    element[2] = DOWN;
	} else {
    element[2] = EMPTY;
	}
  if (!lineData.at(3) == '0') {
    element[3] = RIGHT;
	} else {
    element[3] = EMPTY;
	}
}

KEY Tuple::getElement(int i) {
	if (i < 4) {
    return element[i];
  } else {
    return EMPTY;
  }
}

void Tuple::output() {
  for (int i = 0; i < 4; i++) {
    switch(element[i]) {
      case LEFT:
        std::cout << "LEFT ";
        break;
      case RIGHT:
        std::cout << "RIGHT ";
        break;
      case DOWN:
        std::cout << "DOWN ";
        break;
      case UP:
        std::cout << "UP ";
        break;
      default:
        std::cout << "EMPTY";
        break;
    }
  }
  std::cout << std::endl;
}
