#include "beatmanager.h"
#include "globals.h"
#include "entity.h"

const int offsetTest = 1024 - 365;

BeatManager::BeatManager() {
  leftArrowSprite = new Sprite("assets/art/arrow_blue.png");
  rightArrowSprite = new Sprite("assets/art/arrow_red.png");
  upArrowSprite = new Sprite("assets/art/arrow_yellow.png");
  downArrowSprite = new Sprite("assets/art/arrow_green.png");
  test = new Beat(LEFT);
	test->setSprite(leftArrowSprite);
}


BeatManager::~BeatManager() {
  delete test;
	delete leftArrowSprite;
  delete rightArrowSprite;
  delete upArrowSprite;
  delete downArrowSprite;
}

void BeatManager::tick() {
  time++;
	if (time == FPS) {
		update();
  }
  //Add new beat to list
	if (test->isLive()) {
	  test->update();
	} else {
		test->setLive(true); 
  }
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

	if (test->isLive()) {
    test->draw();
  }
}

void BeatManager::update() {
  time = 0; 
}

bool BeatManager::isGameOver() {
  return false;
}

void BeatManager::interpretEvent(ALLEGRO_EVENT e) {
  //pass event data to all active beats
	if (!test->correctKey(e)) {
	  	//player takes damage
	} else {

	}
}
