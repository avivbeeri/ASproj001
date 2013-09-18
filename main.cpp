#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

int main(int argc, char **argv)
{
   ALLEGRO_DISPLAY *display = NULL;
   ALLEGRO_EVENT_QUEUE *event_queue = NULL;

   bool done = false;

   int pos_x = 320;
   int pos_y = 240;

  
   if(!al_init()) {
      fprintf(stderr, "failed to initialize allegro!\n");
      return -1;
   }

   display = al_create_display(640, 480);
   if(!display) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }

   al_init_primitives_addon();
   al_install_keyboard();

   event_queue = al_create_event_queue();

   al_register_event_source(event_queue, al_get_keyboard_event_source());
   al_register_event_source(event_queue, al_get_display_event_source(display));
   
   while (!done) {
     ALLEGRO_EVENT ev;
     al_wait_for_event(event_queue, &ev);

     if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
       switch(ev.keyboard.keycode) {
         case ALLEGRO_KEY_UP: 
           pos_y -= 10;
           break; 
         case ALLEGRO_KEY_DOWN: 
           pos_y += 10;
           break; 
         case ALLEGRO_KEY_LEFT: 
           pos_x -= 10;
           break; 
         case ALLEGRO_KEY_RIGHT: 
           pos_x += 10;
           break; 
       }
     } else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
       if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
         done = true;
       }
     } else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
       done = true;
     }
     al_draw_filled_rectangle(pos_x, pos_y, 30 + pos_x, 30 + pos_y, al_map_rgb(255,0,255));
     al_flip_display();
     al_clear_to_color(al_map_rgb(0,0,0));
   }
   

   al_destroy_display(display);
   return 0;
}
