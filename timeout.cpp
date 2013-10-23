#include "timeout.h"

Timeout::Timeout(double seconds):
  state(IDLE)
{
  setTimeout(seconds);  
}

void Timeout::start() {
  timeStart = al_get_time();
  state = RUNNING;
}

void Timeout::setTimeout(double seconds) {

  length = seconds;  
}

void Timeout::onEvent(ALLEGRO_EVENT ev) {
  if (ev.type == ALLEGRO_EVENT_TIMER && state == RUNNING) {
    current = al_get_time();
    if ((current - timeStart) >= length) {
      state = FINISHED;
    }
  }
}

bool Timeout::done() {
  bool result = (state == FINISHED);
  if (result) {
    state = IDLE;
  }
  return result;
}
