#ifndef TIMEOUT_H
#define TIMEOUT_H

#include <allegro5/allegro.h>

class Timeout {
  enum timer_state {IDLE, RUNNING, FINISHED};
  
  public:
    Timeout(double seconds);
    void start();
    void onEvent(ALLEGRO_EVENT ev);
    bool done();
  private:
    double timeStart;
    double current;
    double length;
    timer_state state;; 
};

#endif
