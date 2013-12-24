#ifndef RHYTHMLEVEL_H
#define RHYTHMLEVEL_H

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <allegro5/allegro.h>

#include "timeout.h"
#include "beat.h"
#include "sound.h"
#include "globals.h"
#include "tuple.h"
#include "beatmanager.h"

using std::string;
using std::vector;
using std::ifstream;
using std::ios;
using std::getline;

class RhythmLevel {

	public:
    RhythmLevel(const string levelFile, BeatManager &m);
    ~RhythmLevel();
    void onEvent(ALLEGRO_EVENT ev);
    void reset();
    void begin();
    void end();
    bool levelComplete();
    double getTimeRemaining() { return song->getLength() - song->getPosition(); }
	double getTimePoint() { return floor(100*(song->getPosition()))/100; }
	double getArrowPoint() { return floor(100*(delay + (timePerArrow * currentArrow))) / 100; }
  private: 
    void loadFile(const string levelFile);
    
    BeatManager &manager;
    Sound * song;
    Timeout timeout;

	int currentArrow;
    bool playing;
    double barTime;
	double delay;
	unsigned int playthroughNo;
    double songLength;
    unsigned short enemyHP;
    //some song data storage of some sort
    
    //header data
    string songName;
    string artistName;
    unsigned int bpm;
    string wavFile;
    int beatsPerBar;
    double signature;
    int resolution;
    double timePerBeat;
    double timePerArrow;

    //game data
    vector<Tuple> data;
    std::vector<Tuple>::iterator tupleIterator;    
};

#endif
