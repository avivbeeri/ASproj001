//Standard libs
#include <stdio.h>
#include <iostream>

//Allegro libs
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

//local files
#include "globals.h"
#include "inputmanager.h"
#include "player.h"

#include "sound.h"
#include "bitmap.h"
#include "sprite.h"
#include "track.h"
#include "entity.h"

#include "rhythmlevel.h"
#include "beatmanager.h"

using std::min;

//prototypes
void drawTrack(int x);
enum STATE {RUNNING, GAMEOVER};

int main(int argc, char **argv)
{
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_MONITOR_INFO info;
  ALLEGRO_TIMER *timer = NULL;
  
  bool done = false;
  bool redraw = false;
  STATE state = RUNNING;
  

	//begin allegro

  if(!al_init()) {
     fprintf(stderr, "failed to initialize allegro!\n");
     return -1;
  }

  
  al_get_monitor_info(0, &info);
  int w = info.x2 - info.x1; // Assume this is 1366 
  int h = info.y2 - info.y1; // Assume this is 768 
  al_set_new_display_flags(ALLEGRO_FULLSCREEN);
  
  
  //int w = WIDTH;
  //int h = HEIGHT;
  display = al_create_display(w, h);
  if(!display) {
     fprintf(stderr, "failed to create display!\n");
     return -1;
  }

  float scaleWidth = w / (float)WIDTH;
  float scaleHeight = h / (float)HEIGHT;
  float scale = min(scaleWidth, scaleHeight);

  float newX = (w - (WIDTH * scale));
  float newY = (h - (HEIGHT * scale));


  al_init_primitives_addon();
  al_init_image_addon();
  al_init_font_addon();
	al_init_ttf_addon();
	
	al_install_audio(); 

  al_init_acodec_addon(); 
	//Resource initialisation
  al_reserve_samples(1); 
	


  ALLEGRO_FONT *font16 = al_load_ttf_font("assets/fonts/copyviol.ttf",16,0 );
  if (!font16) {
    fprintf(stderr, "Could not load 'copyviol.ttf'.\n");
	  return -1;
	}

  leftArrowSprite = new Sprite("assets/art/arrow_left.png");
  rightArrowSprite = new Sprite("assets/art/arrow_right.png");
  upArrowSprite = new Sprite("assets/art/arrow_up.png");
  downArrowSprite = new Sprite("assets/art/arrow_down.png");
  RhythmPlayer player;
  BeatManager songManager(player, 750);
	string fileName = "test.bms";
	if (argc > 1) {
    fileName = string(argv[1]);
	}
	RhythmLevel level(fileName, songManager);

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
  inputManager = new InputManager();
  
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
  

  //timing variables
  double old_time = al_get_time();
	int frames_done = 0;
  double currentFPS = 0;
  level.begin();

	while (!done) {
    al_wait_for_event(event_queue, &ev);
    
    if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      done = true;
    }
    //distribute events to event listeners?
    inputManager->onEvent(ev);

    if (state == RUNNING) {
      songManager.onEvent(ev);
      level.onEvent(ev);
    }
    //handle specific game event actions

		if (ev.type == ALLEGRO_EVENT_TIMER) {
      //Update entities
      if (state == RUNNING) {

				//Check the pass/fail conditions
				if (!player.isAlive() || level.levelComplete()) {
					state = GAMEOVER;
				  level.end();
        }
			} else if (state == GAMEOVER) {
			  
			}

      //-------NOTHING NEW BELOW HERE-----
			redraw = true;

      double game_time = al_get_time();
		  if(game_time - old_time >= 1.0) {
		    currentFPS = frames_done / (game_time - old_time);
		 
			  frames_done = 0;
			  old_time = game_time;
		  }
			frames_done++;
      //-------NOTHING NEW ABOVE HERE-----
    } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
      //Process given button presses here
      if (state == RUNNING) {
				if (inputManager->isPressed(ESCAPE)) {
					//quit the game or return to the menu, when there is a menu
					state = GAMEOVER;
          level.end();
				} else if (inputManager->isPressed(SPACE)) {
          player.heal(100);
				}
			} else if (state == GAMEOVER) {
        if (inputManager->isPressed(SPACE)) {
				  player.reset();
          level.reset();
					level.begin();
					state = RUNNING;	
				}
				if (inputManager->isPressed(ESCAPE)) {
					//quit the game or return to the menu, when there is a menu
					done = true; 
				}
			}
    } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
      //stuff?
    }
 	  if (redraw && al_is_event_queue_empty(event_queue)) {
      //time to redraw the screen
      redraw = false;
      //Draw background 
      ALLEGRO_TRANSFORM transform;
      al_identity_transform(&transform);
      al_scale_transform(&transform, scale, scale); // scale x and y by 2
      al_translate_transform(&transform, newX, newY);
      al_use_transform(&transform);
      
      
      if (state == RUNNING) {
				track.draw(0, HEIGHT);
				track.draw(WIDTH - 350, HEIGHT); 
				//draw UI
				if (player.isAlive()) {
					al_draw_textf(font16, al_map_rgb(255,255,255), 400, 0,0, "HP: %u", player.getHP()); 
					al_draw_textf(font16, al_map_rgb(255,255,255), 400, 80,0, "Time remaining: %u", level.getTimeRemaining()); 

				 }
				//draw entities

				songManager.draw();
				
        al_draw_line(0, SLOT_TOP, WIDTH, SLOT_TOP, al_map_rgb(255,0,255), 4);      
				al_draw_line(0, SLOT_BOTTOM, WIDTH, SLOT_BOTTOM, al_map_rgb(255,0,255), 4);      
      
      } else if (state == GAMEOVER) {
					al_draw_text(font16, al_map_rgb(255,255,255), WIDTH/2, HEIGHT/2,
                        ALLEGRO_ALIGN_CENTER, "GAME OVER!"); 
			}
			al_draw_textf(font16, al_map_rgb(255,0,255), 0, 0, ALLEGRO_ALIGN_LEFT, "FPS: %f", currentFPS); 
			//Display and reset buffer
      al_flip_display();
      al_clear_to_color(al_map_rgb(0,0,0));
		}
  }
  
  delete inputManager;
	delete leftArrowSprite;
  delete rightArrowSprite;
  delete upArrowSprite;
  delete downArrowSprite;
  
  
  al_destroy_font(font16);
	al_destroy_timer(timer);
  al_destroy_event_queue(event_queue);
  al_destroy_display(display);
  return 0;

}


