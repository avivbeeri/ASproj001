#include "rhythmlevel.h"

RhythmLevel::RhythmLevel():
  songPosition(0),
  enemyHP(15)
  
{
  song = new Sound("assets/music/loz.wav");
  songLength = song->getLength() * 2;
}

RhythmLevel::RhythmLevel(const string levelName):
  song(NULL),
  songPosition(0),
  enemyHP(15)
{
  loadFile(levelName);
}

RhythmLevel::~RhythmLevel() {
  if (song != NULL) {
	  song->stop();
    delete song;
	}
}

void RhythmLevel::reset() {
  songPosition = 0;
  enemyHP = 15;
}

void RhythmLevel::begin() {
  if (song != NULL) {
	  song->play();
  }
}

void RhythmLevel::loadFile(const string levelFileName) {
  ifstream levelFile (levelFileName.c_str(), ios::in);
  if (!levelFile.is_open()) {
     //error
  }
  
  string currentLine;
  while ( getline(levelFile, currentLine) ) {
    //parse strings
    //std::cout << currentLine << std::endl;
    if (currentLine.size() <= 0) {
      continue;
		}
		if (currentLine.at(0) != '#') {
      continue;
    }
    //a potential command, process
    unsigned int pivot = currentLine.find(' ', 2);
    if (pivot == string::npos) {
      continue;
		}
    string parameter = currentLine.substr(1, pivot-1);
    
		string value = currentLine.substr(pivot+1, currentLine.size());
    std::transform(parameter.begin(), parameter.end(),parameter.begin(), ::toupper);
    if (parameter == "TITLE") {
      songName = value;  
		} else if (parameter == "ARTIST") {
      artistName = value;
		} else if (parameter == "BPM") {
		  bpm = atoi(value.c_str());	
		} else if (parameter == "RESOLUTION") {
		  resolution = atoi(value.c_str());	
		} else if (parameter == "SIGNATURE") {
      pivot = value.find('/', 1);
			float dividend = atof(value.substr(0, pivot).c_str());
			int  divisor = atoi(value.substr(pivot+1, value.size()).c_str());
      signature = dividend / divisor;
		} else if (parameter == "WAVFILE") {
      wavFile = value;
      song = new Sound(wavFile);
      songLength = song->getLength() * 2;
		}
    		
	} 
  levelFile.close();
  
  std::cout << "TITLE" << " - " << songName << std::endl;
  std::cout << "ARTIST" << " - " << artistName << std::endl;
  std::cout << "BPM" << " - " << bpm << std::endl;
  std::cout << "RESOLUTION" << " - " << resolution << std::endl;
  std::cout << "SIGNATURE" << " - " << signature << std::endl;
}

void RhythmLevel::end() {
  if (song != NULL) {
	  song->stop();
	}
  reset();
}

void RhythmLevel::tick() {
  ticks++;
  if (ticks >= FPS) {
    songPosition++;
    ticks = 0;
  }
}

void RhythmLevel::onEvent(ALLEGRO_EVENT ev) {
  if (ev.type == ALLEGRO_EVENT_TIMER) {
    tick();

    if (songPosition == (songLength / 2)) {
      song->play();
    }
  }
}

Beat * RhythmLevel::getNextBeat() {
  switch (songPosition % 4) {
    case 0: return new Beat(LEFT);
		case 1: return new Beat(UP);
		case 2: return new Beat(DOWN);
		case 3: return new Beat(RIGHT);
	  default: return NULL;
	}

	
	
}

bool RhythmLevel::levelComplete() {
  return (enemyHP == 0) || (songPosition == songLength);
}
