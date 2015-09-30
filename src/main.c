#include <pebble.h>
#include "UniverseTimeLine.h"
  
static Window *s_my_window;

static TextLayer *s_time_layer;
static TextLayer *s_event_layer;



static void update_time(){
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  static char buffer[] = "00:00";
  
  if(clock_is_24h_style() == true){
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  }else{
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }
  
  text_layer_set_text(s_time_layer, buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  update_time();
}

static void main_window_load(Window *window){
  //create time text layer
  //s_time_layer = text_layer_create(GRect(0, 55, 144, 50));
  s_time_layer = text_layer_create(GRect(0, 0, 144, 50));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  //text_layer_set_text(s_time_layer, "00:00");
  
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);
  //text_layer_set_text_alignment(s_time_layer, GTextAlignmentLeft);
  //add layer to as child to root
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
}
static void main_window_unload(Window *window){
  
}

void handle_init(void) {
  //Create window and assign it to 
  s_my_window = window_create();

  //Set handlers
  window_set_window_handlers(s_my_window, (WindowHandlers){
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_my_window, true);
  update_time();
  
  //text_layer = text_layer_create(GRect(0, 0, 144, 20));
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  //create all events
  init_all_events();
}

void handle_deinit(void) {
  text_layer_destroy(s_time_layer);
  window_destroy(s_my_window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
