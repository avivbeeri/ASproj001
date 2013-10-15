#include "beatmanager.h"
#include "globals.h"
#include "entity.h"
#include <iostream>

const int offsetTest = WIDTH - 355;

BeatManager::BeatManager(RhythmPlayer &p, unsigned int oset):
  player(p),	
	offset(oset)
{

  level = NULL;
}


BeatManager::~BeatManager() {
  while (!activeBeats.empty()) {
    Beat * ptr = activeBeats.front();
		activeBeats.pop_front();
		delete ptr;
  }
  while (!missedBeats.empty()) {
    std::cout << "clearing the missedBeats" << std::endl;
		Beat * ptr = missedBeats.front();
		missedBeats.pop_front();
		delete ptr;
  }
	
}

void BeatManager::playLevel(RhythmLevel * l) {
  level = l;
	level->registerManager(this);
  level->begin();
}

void BeatManager::tick() {
  time++;
	if (time >= FPS) {
		update();
  }
	
	//cleanup all beats
	list<Beat*>::iterator beatIterator;

	for (beatIterator = activeBeats.begin();
		   beatIterator != activeBeats.end();
			 beatIterator++)
	{
	
		if (!(*beatIterator)->isLive()) {

      Beat * oldBeat = *beatIterator;
	    beatIterator = activeBeats.erase(beatIterator);
	    missedBeats.push_front(oldBeat);
      
		}
	}
  while (!missedBeats.empty()) {
    Beat * ptr = missedBeats.front();
		if (ptr->wasMissed()) {
			player.takeDamage(1);
		} else {
			player.heal(1);
		}
		missedBeats.pop_front();
		delete ptr;
  }
}

void BeatManager::draw() {
  //run through the list of beats, display them. they should know where they are.
  
  /* Drawing co-ordinate tests
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
  */
  
  //iterate through all beats to draw them
	list<Beat*>::iterator beatIterator;

	for (beatIterator = activeBeats.begin();
		   beatIterator != activeBeats.end();
			 beatIterator++)
	{
   	(*beatIterator)->draw();
	}
}

void BeatManager::publishTuple(Tuple t) {
	for (int i = 0; i < 4; i++) {
		if (t.getElement(i) != EMPTY) {
		  activeBeats.push_back(new Beat(t.getElement(i)));
		}
  }
}

void BeatManager::update() {
  time = 0; 
	
  /* 
	newBeat = new Beat(static_cast<KEY>(this->directionTest));
	newBeat->setX(offset + 70*(this->directionTest++));
	this->directionTest %= 4;
	activeBeats.push_back(newBeat);
  newBeat = new Beat(static_cast<KEY>(this->directionTest));
	newBeat->setX(offset + 70*(this->directionTest)++);
	this->directionTest %= 4;
	activeBeats.push_back(newBeat);
	*/
}

bool BeatManager::isGameOver() {
  return !player.isAlive() || (level != NULL && level->levelComplete());
}

void BeatManager::onEvent(ALLEGRO_EVENT e) {
  //update the level - might not need to be in here, but in the main loop
	if (level != NULL) {
    level->onEvent(e);
  }

  //pass event data to all active beats
	if (activeBeats.empty()) {
		return;
  }
  list<Beat*>::iterator beatIterator = activeBeats.begin();
  bool eventConsumed = false;


  while (beatIterator != activeBeats.end() && 
          eventConsumed == false) {
 
    if ((*beatIterator)->isLive()) {
      eventConsumed = (*beatIterator)->onEvent(e);
    } else {
      Beat * oldBeat = *beatIterator;
	    beatIterator = activeBeats.erase(beatIterator);
	    missedBeats.push_front(oldBeat);
    }
    beatIterator++;
  }
    
}
