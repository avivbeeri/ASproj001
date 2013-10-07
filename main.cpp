//Standard libs
#include <stdio.h>
#include <iostream>

//Allegro libs
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

//local files
#include "entity.h"
#include "bitmap.h"
#include "sprite.h"
#include "track.h"
#include "player.h"
#include "beatmanager.h"
#include "globals.h"

//prototypes
void drawTrack(int x);

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
	al_init_ttf_addon();
	 

  //Resource initialisation

  ALLEGRO_FONT *font13 = al_load_ttf_font("assets/fonts/copyviol.ttf",13,0 );
  if (!font13) {
    fprintf(stderr, "Could not load 'copyviol.ttf'.\n");
	  return -1;
	}

  leftArrowSprite = new Sprite("assets/art/arrow_blue.png");
  rightArrowSprite = new Sprite("assets/art/arrow_red.png");
  upArrowSprite = new Sprite("assets/art/arrow_yellow.png");
  downArrowSprite = new Sprite("assets/art/arrow_green.png");
  RhythmPlayer player;
  BeatManager manager(player);

  Track track;
  /*
  ALLEGRO_BITMAP * image = al_create_bitmap(4, 4);
  al_set_target_bitmap(image);
  al_clear_to_color(al_map_rgb(0,0,0));
  al_draw_filled_circle(2, 2, 2, al_map_rgb(255,0,255));
  al_set_target_bitmap(al_get_backbuffer(display));
  
  Bitmap b(image);
  */
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
    manager.interpretEvent(ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {
      //Update entities
      manager.tick();
		  //Check the pass/fail conditions
			if (!player.isAlive()) {
				done = true;
		  } else {
			}
			if (manager.isGameOver()) {
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
      //draw UI
      if (player.isAlive()) {
			  al_draw_textf(font13, al_map_rgb(255,255,255), 400, 0,0, "HP: %u", player.getHP()); 
			 }
			//draw entities

      manager.draw();
      al_draw_line(0, SLOT_TOP, WIDTH, SLOT_TOP, al_map_rgb(255,0,255), 4);      
      al_draw_line(0, SLOT_BOTTOM, WIDTH, SLOT_BOTTOM, al_map_rgb(255,0,255), 4);      
      //Display and reset buffer
      al_flip_display();
      al_clear_to_color(al_map_rgb(0,0,0));
    }
  }
	delete leftArrowSprite;
  delete rightArrowSprite;
  delete upArrowSprite;
  delete downArrowSprite;
  al_destroy_timer(timer);
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);
  return 0;

}


