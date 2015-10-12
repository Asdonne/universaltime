#include <pebble.h>

typedef struct {
  int event_minutes;
  char* event_message;
  char* historic_time;
}event;  
  
static Window *s_my_window;
static TextLayer *s_time_layer;
static TextLayer *s_event_layer;
static TextLayer *s_age_layer;

#define NUM_EVENTS 16

event all_events[NUM_EVENTS];


void init_all_events(){
  
  all_events[0].event_minutes = 0;
  all_events[0].event_message =  "Solar System Starts to Form";
  all_events[0].historic_time =  "4600 MYA";
  
  all_events[1].event_minutes =  18;
  all_events[1].event_message =  "Sun Ignites into an Main Sequence Star";
  all_events[1].historic_time =  "4550 MYA";
  
  all_events[2].event_minutes =  21; //501;
  all_events[2].event_message =  "Left over dust blown away by the Sun";
  all_events[2].historic_time =  "4540 MYA";
  
  all_events[3].event_minutes =  34;
  all_events[3].event_message =  "Moons forms very closer to Earth.";
  all_events[3].historic_time =  "4500 MYA";
  
  all_events[4].event_minutes =  128;
  all_events[4].event_message =  "Fist Oceans appear";
  all_events[4].historic_time =  "4200 MYA"; 
    
  all_events[5].event_minutes =  143;
  all_events[5].event_message =  "Late Heavy Bombardment Starts";
  all_events[5].historic_time =  "4100 MYA";

  all_events[6].event_minutes =  158;
  all_events[6].event_message =  "First Singe Cell life appears";
  all_events[6].historic_time =  "3900 MYA";

  all_events[7].event_minutes =  252;
  all_events[7].event_message =  "End of Late Heavy Bombardment";
  all_events[7].historic_time =  "3800 MYA";

  all_events[8].event_minutes =  346;
  all_events[8].event_message =  "Life starts basic process of photosynthesis";
  all_events[8].historic_time =  "3500 MYA";

  all_events[9].event_minutes =  502;
  all_events[9].event_message =  "Cynobacteria start producing Oxygen";
  all_events[9].historic_time =  "3000 MYA";

  all_events[10].event_minutes =  596;
  all_events[10].event_message =  "Oldest Cyanobacteria Fossils";
  all_events[10].historic_time =  "2700 MYA";
  
  all_events[11].event_minutes =  659;
  all_events[11].event_message =  "Iron Ore Deposits Form from Oxygen in the Ocean";
  all_events[11].historic_time =  "2500 MYA";

  all_events[12].event_minutes =  690;
  all_events[12].event_message =  "Great Oxygenation Event";
  all_events[12].historic_time =  "2400 MYA";

  all_events[13].event_minutes =  784;
  all_events[13].event_message =  "First eukaryotes";
  all_events[13].historic_time =  "2100 MYA";
  
  all_events[14].event_minutes =  815;
  all_events[14].event_message =  "Life starts producing oxygen";
  all_events[14].historic_time =  "2000 MYA"; 
  
  all_events[15].event_minutes =  877;
  all_events[15].event_message =  "Start of the Boring Billion Years";
  all_events[15].historic_time =  "1800 MYA"; 

  /**
  all_events[1].event_minutes = ;
  all_events[1].event_message =     "";
  all_events[1].historic_time = "";
  */

}
//IF elapsed_minutes is greater then the time needed for the next event, incremet the next event
static bool update_counter(int elapsed_minutes, int index){
  APP_LOG(APP_LOG_LEVEL_DEBUG, "if (%d >= %d)", elapsed_minutes, all_events[index+1].event_minutes);
  if( elapsed_minutes >= all_events[index+1].event_minutes && index < NUM_EVENTS-1){
    return true;
  }
  else{
    return false;    
    }
}

static void update_events()
{
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  
  int elapsed_minutes = 0;
  //int current_event_minutes = 0; 
  static int s_current_event = 0;
  event* current_event = NULL;
  event* next_event = NULL;
  
  char *event_buffer = NULL; //buffer for elapsed minutes
  char *age_buffer = NULL;
  
  elapsed_minutes = tick_time->tm_hour * 60 + tick_time->tm_min;
  
  current_event = &all_events[s_current_event];
  next_event = &all_events[s_current_event+1];
  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "current_event->event_minutes = %d)", current_event->event_minutes);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "next_event->event_minutes = %d)", next_event->event_minutes);
  
  while(update_counter(elapsed_minutes, s_current_event)){
    APP_LOG(APP_LOG_LEVEL_DEBUG, "\tupdated s_current_event");
    s_current_event++;
  }
  
  event_buffer = all_events[s_current_event].event_message;
  age_buffer = all_events[s_current_event].historic_time;
  
  text_layer_set_text(s_event_layer, event_buffer);
  text_layer_set_text(s_age_layer, age_buffer);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "\n");
}

static void update_time(){
  time_t temp = time(NULL);
  struct tm *tick_time = localtime(&temp);
  static char buffer[] = "00:00"; //buffer for current time
  
 
  
  if(clock_is_24h_style() == true){
    strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  }else{
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  }
  
  text_layer_set_text(s_time_layer, buffer);
  
  update_events();
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed){
  update_time();
}

static void init_layer(TextLayer *layer, Window *window){
  text_layer_set_background_color(layer, GColorBlack);
  text_layer_set_text_color(layer, GColorClear);
  text_layer_set_text_alignment(layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(layer));
}

static void main_window_load(Window *window){
  //create time text layer
  s_time_layer = text_layer_create(GRect(0, 0, 144, 50));
  s_event_layer = text_layer_create(GRect(0, 50, 144, 50));
  s_age_layer = text_layer_create(GRect(0, 100, 144, 68));
  
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  text_layer_set_font(s_event_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD));
  text_layer_set_font(s_age_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  
  init_layer(s_time_layer, window);
  init_layer(s_event_layer, window);
  init_layer(s_age_layer, window); 
}



static void main_window_unload(Window *window){
  
}

void handle_init(void) {
  //create all events
  init_all_events();
  
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
