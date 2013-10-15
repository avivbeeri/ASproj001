#include "beatmanager.h"
#include "globals.h"
#include "entity.h"
#include <iostream>

BeatManager::BeatManager(RhythmPlayer &p, unsigned int oset):
  player(p),	
	offset(oset)
{}

BeatManager::~BeatManager() {
  while (!activeBeats.empty()) {
    Beat * ptr = activeBeats.front();
		activeBeats.pop_front();
		delete ptr;
  }
}

void BeatManager::emitTuple(Tuple t) {
  for (int i = 0; i < 4; i++) {
		if (t.getElement(i) != EMPTY) {
	    t.output();
		  activeBeats.push_back(new Beat(t.getElement(i)));
		}
  }
}

void BeatManager::onEvent(ALLEGRO_EVENT e) {
  //update the level - might not need to be in here, but in the main loop


  //pass event data to all active beats
  list<Beat*>::iterator beatIterator = activeBeats.begin();
  bool eventConsumed = false;

  while (beatIterator != activeBeats.end() && 
          eventConsumed == false) {
  
    if ((*beatIterator)->isLive()) {
      eventConsumed = (*beatIterator)->onEvent(e);
    } else {
      
     std::cout  << "BEATMANAGER.culling missed beats" << std::endl;
      Beat * oldBeat = *beatIterator;
      beatIterator = activeBeats.erase(beatIterator);
      if (oldBeat->wasMissed()) {
        player.takeDamage(1);
      } else {
        player.heal(1);
      }
      delete oldBeat;
    }
    beatIterator++;
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

  std::cout  << "BEATMANAGER.begin drawing beats" << std::endl;
	for (beatIterator = activeBeats.begin();
		   beatIterator != activeBeats.end();
			 beatIterator++)
	{
      (*beatIterator)->draw();
	}
  std::cout  << "BEATMANAGER.end drawing beats" << std::endl;
}
