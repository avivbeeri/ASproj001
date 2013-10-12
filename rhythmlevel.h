#ifndef RHYTHMLEVEL_H
#define RHYTHMLEVEL_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <allegro5/allegro.h>

#include "beat.h"
#include "sound.h"
#include "globals.h"
#include "tuple.h"

using std::string;
using std::vector;
using std::ifstream;
using std::ios;
using std::getline;

class RhythmLevel {
  public:
    RhythmLevel();
    RhythmLevel(const string levelFile);
    ~RhythmLevel();
    void reset();
    void onEvent(ALLEGRO_EVENT ev);
    void begin();
    void end();
    Beat * getNextBeat();
    bool levelComplete();
    unsigned int getTimeRemaining() { return songLength - songPosition; }
  private: 
    void tick();
    void loadFile(const string levelFile);

    Sound * song;
    unsigned int ticks;
    unsigned int songLength;
    unsigned int songPosition;
    unsigned short enemyHP;
    //some song data storage of some sort
    
    //header data
    string songName;
    string artistName;
    unsigned int bpm;
    string wavFile;

    //game data
    //vector<Tuple> data;
    
};

#endif
