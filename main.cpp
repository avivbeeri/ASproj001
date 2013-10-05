//Standard libs
#include <stdio.h>
#include <iostream>
#include <string>

//Allegro libs
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>

//local files
#include "entity.h"
#include "bitmap.h"
#include "sprite.h"
#include "track.h"
#include "player.h"
#include "beatmanager.h"

//prototypes
void drawTrack(int x);

//declarations
using std::string;
enum key { UP, DOWN, LEFT, RIGHT , ESCAPE, KEY_A, KEY_S, KEY_D, KEY_F};

//Globals
const float FPS = 60;
const int HEIGHT = 540;
const int WIDTH = 1010;

int main(int argc, char **argv)
{
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_MONITOR_INFO info;
  ALLEGRO_TIMER *timer = NULL;
  
  bool pressed[9] = {false, false, false, false, 
		     false, false, false, false, false};
  bool done = false;
  bool redraw = false;

  Entity beat1(50, 0);
  Entity beat2(100, 0);
  
  if(!al_init()) {
     fprintf(stderr, "failed to initialize allegro!\n");
     return -1;
  }

  /*
  al_get_monitor_info(0, &info);
  int w = info.x2 - info.x1; // Assume this is 1366 
  int h = info.y2 - info.y1; // Assume this is 768 
  al_set_new_display_flags(ALLEGRO_FULLSCREEN);
  */
  
  int w = WIDTH;
  int h = HEIGHT;
  display = al_create_display(w, h);
  if(!display) {
     fprintf(stderr, "failed to create display!\n");
     return -1;
  }

  al_init_primitives_addon();
  al_init_image_addon();
  al_init_font_addon();

  //Resource initialisation

  RhythmPlayer player;
  BeatManager manager;

  string str = "assets/art/arrow_blue.png";
  Sprite arrow(str);
  Track track;
  /*
  ALLEGRO_BITMAP * image = al_create_bitmap(4, 4);
  al_set_target_bitmap(image);
  al_clear_to_color(al_map_rgb(0,0,0));
  al_draw_filled_circle(2, 2, 2, al_map_rgb(255,0,255));
  al_set_target_bitmap(al_get_backbuffer(display));
  
  Bitmap b(image);
  */
  beat1.setSprite(&arrow);
  beat2.setSprite(&arrow);

  //Initialise event handling
  
  al_install_keyboard();
  event_queue = al_create_event_queue();
  if (event_queue == NULL) {
    fprintf(stderr, "failed to initialize event queue!\n");
    al_destroy_display(display);
    return -1;  
  }  

  timer = al_create_timer(1.0 / FPS);
  if (timer == NULL) {
    fprintf(stderr, "failed to initialize game loop timer!\n");
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    return -1;  
  }  

  //Register event sources
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_display_event_source(display));
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  
  //begin game loop timer
  al_start_timer(timer);  
  ALLEGRO_EVENT ev;
  while (!done) {
    al_wait_for_event(event_queue, &ev);
    if (ev.type == ALLEGRO_EVENT_TIMER) {
      //Update entities
      manager.tick();
      if (beat1.isLive()) 
        beat1.setY(beat1.getY() + 5);
      if (beat2.isLive())
        beat2.setY(beat1.getY() + 5);

		  //Check the pass/fail conditions
			if (!player.isAlive()) {
				done = true;
		  }
			if (!manager.enemyAlive()) {
        done = true;
			}
			redraw = true;
    }
    
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
 		  switch(ev.keyboard.keycode) {
        case ALLEGRO_KEY_UP: 
          pressed[UP] = true;
          break; 
        case ALLEGRO_KEY_DOWN: 
          pressed[DOWN] = true;
          break; 
        case ALLEGRO_KEY_LEFT: 
          pressed[LEFT] = true;
          break; 
        case ALLEGRO_KEY_RIGHT: 
          pressed[RIGHT] = true;
          break; 
        case ALLEGRO_KEY_A: 
          pressed[KEY_A] = true;
          break; 
        case ALLEGRO_KEY_S: 
          pressed[KEY_S] = true;
          break; 
        case ALLEGRO_KEY_D: 
          pressed[KEY_D] = true;
          break; 
        case ALLEGRO_KEY_F: 
          pressed[KEY_F] = true;
          break; 
        case ALLEGRO_KEY_ESCAPE: 
          pressed[ESCAPE] = true;
          break; 
      }
      //Process given button presses here
      if (pressed[ESCAPE]) {
			  //quit the game or return to the menu, when there is a menu
        done = true; 
			}
			//Check if current beats are scored
			if (beat1.getY() >= HEIGHT - 100 && pressed[UP]) {
        beat1.setLive(false);
      }
      if (beat2.getY() >= HEIGHT - 100 && pressed[LEFT]) {
        beat2.setLive(false);
      }
    } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
      switch(ev.keyboard.keycode) {
        case ALLEGRO_KEY_UP: 
				  pressed[UP] = false;
          break; 
        case ALLEGRO_KEY_DOWN: 
				  pressed[DOWN] = false;
          break; 
        case ALLEGRO_KEY_LEFT: 
				  pressed[LEFT] = false;
          break; 
        case ALLEGRO_KEY_RIGHT: 
				  pressed[RIGHT] = false;
          break; 
        case ALLEGRO_KEY_A: 
          pressed[KEY_A] = false;
          break; 
        case ALLEGRO_KEY_S: 
          pressed[KEY_S] = false;
          break; 
        case ALLEGRO_KEY_D: 
          pressed[KEY_D] = false;
          break; 
        case ALLEGRO_KEY_F: 
          pressed[KEY_F] = false;
          break; 
        case ALLEGRO_KEY_ESCAPE: 
          pressed[ESCAPE] = false;
          break; 
      }
    } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      done = true;
    }
 	  if (redraw && al_is_event_queue_empty(event_queue)) {
      //time to redraw the screen
      redraw = false;
      //Draw background 
      track.draw(0, HEIGHT);
      track.draw(WIDTH - 350, HEIGHT); 
      //draw entities
      beat1.draw();
      beat2.draw();
      manager.draw();
      
      //Display and reset buffer
      al_flip_display();
      al_clear_to_color(al_map_rgb(0,0,0));
    }
  }
  al_destroy_timer(timer);
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);
  return 0;

}


