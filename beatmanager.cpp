#include "beatmanager.h"
#include "globals.h"
#include "entity.h"


const int offsetTest = WIDTH - 355;
int directionTest = 0;

BeatManager::BeatManager(RhythmPlayer &p, unsigned int oset):
  player(p),	
	offset(oset),
  directionTest(0)
{
}


BeatManager::~BeatManager() {
  while (!activeBeats.empty()) {
    Beat * ptr = activeBeats.front();
		activeBeats.pop_front();
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
      //Cleanup

      Beat * beats = activeBeats.front();
	    beatIterator = activeBeats.erase(beatIterator);
	    missedBeats.push_front(beats);
      
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

void BeatManager::update() {
  time = 0; 
	
  Beat * newBeat = new Beat(static_cast<KEY>(this->directionTest));
	newBeat->setX(offset + 70*(this->directionTest)++);
	this->directionTest %= 4;
	activeBeats.push_back(newBeat);
}

bool BeatManager::isGameOver() {
  return false;
}

void BeatManager::onEvent(ALLEGRO_EVENT e) {
  //pass event data to all active beats
	if (activeBeats.empty()) {
		return;
  }
	   
  list<Beat*>::iterator beatIterator;

  for (beatIterator = activeBeats.begin();
       beatIterator != activeBeats.end();
       beatIterator++)
  {
  
    if ((*beatIterator)->isLive()) {
      (*beatIterator)->onEvent(e);
    } else {
      missedBeats.push_back(activeBeats.front());
      activeBeats.pop_front();
    }
  }
    
}
