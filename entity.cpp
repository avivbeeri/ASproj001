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


void Entity::setLive(bool live) {
  this->live = live;
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

void Entity::update() {
  sprite->draw(x,y);
}

