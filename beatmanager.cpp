#include <string>
#include "beatmanager.h"
#include "entity.h"

const int FPS = 60;
const int offsetTest = 1024 - 350;

BeatManager::BeatManager() {
  string s;
  s = "assets/art/arrow_blue.png";
  leftArrowSprite = new Sprite(s);
  s = "assets/art/arrow_red.png";
  rightArrowSprite = new Sprite(s);
  s = "assets/art/arrow_yellow.png";
  upArrowSprite = new Sprite(s);
  s = "assets/art/arrow_green.png";
  downArrowSprite = new Sprite(s);
}


BeatManager::~BeatManager() {
  delete leftArrowSprite;
  delete rightArrowSprite;
  delete upArrowSprite;
  delete downArrowSprite;
}

void BeatManager::tick() {
  time++;
}

void BeatManager::draw() {
  //run through the list of beats, display them. they should know where they are.
  
  Entity arrow1(13 +offsetTest,0);
  arrow1.setSprite(leftArrowSprite);
  arrow1.draw();
  Entity arrow2(107 + offsetTest,0);
  arrow2.setSprite(upArrowSprite);
  arrow2.draw();

  Entity arrow3(193 + offsetTest,0);
  arrow3.setSprite(downArrowSprite);
  arrow3.draw();
  Entity arrow4(267 + offsetTest,0);
  arrow4.setSprite(rightArrowSprite);
  arrow4.draw();
}

void BeatManager::update() {
  if (time == FPS) {
    time = 0; 
  }
}

bool BeatManager::enemyAlive() {
  return true;
}
