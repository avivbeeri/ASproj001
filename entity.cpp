#include "entity.h"

//constructor


Entity::Entity() {
  x = 0;
  y = 0;
  live = true;
}

Entity::Entity(int x, int y) {
  this->x = x;
  this->y = y;
  live = true;
}


Entity::~Entity() {
  //Empty destructor
}


void Entity::kill() {
  this->live = false;
}

void Entity::setX(int x) {
  this->x = x;
}

void Entity::setY(int y) {
  this->y = y;
}

int Entity::getX() {
  return x;
}

int Entity::getY() {
  return y;
}

bool Entity::isLive() {
  return live;
}

void Entity::setSprite(Drawable * spritePtr) {
  sprite = spritePtr;
}


void Entity::update() {}

void Entity::draw() {
  if (live) {
	  sprite->draw(x,y);
	}
}

