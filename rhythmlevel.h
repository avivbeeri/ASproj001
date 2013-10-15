#ifndef RHYTHMLEVEL_H
#define RHYTHMLEVEL_H

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>

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
    RhythmLevel();
    RhythmLevel(const string levelFile, BeatManager m);
    ~RhythmLevel();
    void onEvent(ALLEGRO_EVENT ev);
    void reset();
    void begin();
    void end();
    bool levelComplete();
    void registerManager(BeatManager * m);
    unsigned int getTimeRemaining() { return songLength - songPosition; }
  private: 
    void loadFile(const string levelFile);
    
    Sound * song;
    BeatManager * manager;

		bool playing;
    unsigned int ticks;
		unsigned int barTicks;
    unsigned int songLength;
    unsigned int songPosition;
    unsigned short enemyHP;
    //some song data storage of some sort
    
    //header data
    string songName;
    string artistName;
    unsigned int bpm;
    string wavFile;
    double signature;
    unsigned int resolution;
    double timePerBeat;

    //game data
    vector<Tuple> data;
    std::vector<Tuple>::iterator tupleIterator;    
};

#endif
