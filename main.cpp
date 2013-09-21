#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

enum key { UP, DOWN, LEFT, RIGHT };
const float FPS = 60;

int main(int argc, char **argv)
{
  ALLEGRO_DISPLAY *display = NULL;
  ALLEGRO_EVENT_QUEUE *event_queue = NULL;
  ALLEGRO_MONITOR_INFO info;
  ALLEGRO_TIMER *timer = NULL;
  
  bool pressed[4] = {false, false, false, false};
  bool done = false;
  bool redraw = false;

  int pos_x = 320;
  int pos_y = 240;

 
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
  
  int w = 640;
  int h = 480;
  display = al_create_display(w, h);
  if(!display) {
     fprintf(stderr, "failed to create display!\n");
     return -1;
  }

  al_init_primitives_addon();
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
    
 	    pos_y += pressed[DOWN] * 10;
 	    pos_y -= pressed[UP] * 10;
 	    pos_x += pressed[RIGHT] * 10;
 	    pos_x -= pressed[LEFT] * 10;

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
        case ALLEGRO_KEY_ESCAPE:
          done = true;
          break;
      }
    } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
      done = true;
    }
 	  if (redraw && al_is_event_queue_empty(event_queue)) {
      //time to redraw the screen
 		  redraw = false;

 		  //draw things
      al_draw_filled_circle(pos_x, pos_y, 10, al_map_rgb(255,0,255));
      al_draw_line(0,h-1, w-1, h-1, al_map_rgb(255,255,255), 1);
      
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
