#include "beatmanager.h"
#include "globals.h"
#include "entity.h"
#include <iostream>


const int offsetTest = 1024 - 365;

BeatManager::BeatManager() {
}


BeatManager::~BeatManager() {
  while (!activeBeats.empty()) {
    Beat * ptr = activeBeats.front();
		activeBeats.pop_front();
		delete ptr;
  }
	
  while (!missedBeats.empty()) {
    Beat * ptr = missedBeats.front();
		missedBeats.pop_front();
		delete ptr;
  }
}

void BeatManager::tick() {
  time++;
	if (time >= FPS) {
		update();
  }
	
	//update all beats
	list<Beat*>::iterator beatIterator;

	for (beatIterator = activeBeats.begin();
		   beatIterator != activeBeats.end();
			 beatIterator++)
	{
	
		if ((*beatIterator)->isLive()) {
     	(*beatIterator)->update();
  	} else {
      Beat * beats = activeBeats.front();
			if (beatIterator != activeBeats.end()) {
			  beatIterator++;
			}
	    activeBeats.pop_front();
	    delete beats;
		}
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
  //iterate through all beats to draw them
	list<Beat*>::iterator beatIterator;

	for (beatIterator = activeBeats.begin();
		   beatIterator != activeBeats.end();
			 beatIterator++)
	{
   	(*beatIterator)->draw();
	}
}

void BeatManager::update() {
  time = 0; 
  Beat * newBeat = new Beat(LEFT);
	activeBeats.push_back(newBeat);

}

bool BeatManager::isGameOver() {
  return false;
}

void BeatManager::interpretEvent(ALLEGRO_EVENT e) {
  //pass event data to all active beats
	if (activeBeats.empty()) {
		return;
  }
	if (e.type == ALLEGRO_EVENT_KEY_DOWN) {
	   
		if (!((activeBeats.front())->correctKey(e))) {
	    	//player takes damage
      missedBeats.push_back(activeBeats.front());
			activeBeats.pop_front();
	  } else {

	  }
    
  }
}
