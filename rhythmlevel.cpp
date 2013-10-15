#include "rhythmlevel.h"


RhythmLevel::RhythmLevel():
  ticks(0),
	barTicks(0), 
  enemyHP(15)
{
  manager = NULL;
	song = new Sound("assets/music/loz.wav");
  songLength = song->getLength() * 2;
  songPosition = 0;
	tupleIterator = data.begin();
}

RhythmLevel::RhythmLevel(const string levelName):
  song(NULL),
  ticks(0),
	barTicks(0),  
  enemyHP(15)
{
  manager = NULL;
	songPosition = 0;
  loadFile(levelName);
  tupleIterator = data.begin();
}

void RhythmLevel::registerManager(BeatManager * m) {
  manager = m;
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
	  song->play(ALLEGRO_PLAYMODE_LOOP);
  }
}

void RhythmLevel::loadFile(const string levelFileName) {
  ifstream levelFile (levelFileName.c_str(), ios::in);
  if (!levelFile.is_open()) {
     //error
  }
  unsigned int barCount = 0; 
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
		  timePerBeat = 1 / (double) bpm;
		} else if (parameter == "RESOLUTION") {
		  resolution = atoi(value.c_str());	
		} else if (parameter == "BARS") {
		  barCount = atoi(value.c_str());	
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
  
  data.resize(barCount * resolution, Tuple(EMPTY, EMPTY, EMPTY, EMPTY));
  
	//Data output test
	std::cout << "TITLE" << " - " << songName << std::endl;
  std::cout << "ARTIST" << " - " << artistName << std::endl;
  std::cout << "BPM" << " - " << bpm << std::endl;
  std::cout << "RESOLUTION" << " - " << resolution << std::endl;
  std::cout << "BARS" << " - " << barCount << std::endl;
  std::cout << "SIGNATURE" << " - " << signature << std::endl;
  //derived 
	std::cout << "Total points:" << " - " << data.size() << std::endl;
  std::cout << "Time per beat:" << " - " << timePerBeat << std::endl;
}

void RhythmLevel::end() {
  if (song != NULL) {
	  song->stop();
	}
  reset();
}

void RhythmLevel::tick() {
  ticks++;
	barTicks++;
  if (ticks >= FPS) {
    songPosition++;
    ticks = 0;
  }
	if (tupleIterator == data.end()) {
    tupleIterator = data.begin();
	} else if (barTicks >= timePerBeat) {
    barTicks = 0;
		tupleIterator++;
		manager->publishTuple(*tupleIterator);
	}
}

void RhythmLevel::onEvent(ALLEGRO_EVENT ev) {
  if (ev.type == ALLEGRO_EVENT_TIMER) {
    tick();
    
    if (songPosition >= songLength) {
      song->stop();
    }
    
  }
}

Tuple RhythmLevel::getNextTuple() {
	/*
	switch (songPosition % 4) {
    case 0: return new Beat(LEFT);
		case 1: return new Beat(UP);
		case 2: return new Beat(DOWN);
		case 3: return new Beat(RIGHT);
	  default: return NULL;
	} */
	if (songPosition % 2) {
    return Tuple(UP,  EMPTY, EMPTY, EMPTY);
	} else {
	  return (*tupleIterator);
	}
	
}

bool RhythmLevel::levelComplete() {
  return (enemyHP == 0) || (songPosition == songLength);
}
