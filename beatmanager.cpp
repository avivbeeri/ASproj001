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

void BeatManager::emitTuple(Tuple t, double timePerBeat) {
  for (int i = 0; i < 4; i++) {
		if (t.getElement(i) != EMPTY) {
      Beat * newBeat = new Beat(t.getElement(i), timePerBeat);
		  activeBeats.push_back(newBeat);

		}
  }
}

void BeatManager::onEvent(ALLEGRO_EVENT e) {
  //update the level - might not need to be in here, but in the main loop


  //pass event data to all active beats
  if (activeBeats.empty()) {
      return;
  }
  list<Beat*>::iterator beatIterator = activeBeats.begin();
  bool eventConsumed = false;

  
  do { 
    if ((*beatIterator)->isLive()) {
      eventConsumed = (*beatIterator)->onEvent(e);
    } else {
       
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
  } while (beatIterator != activeBeats.end() && 
          eventConsumed == false); 
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
