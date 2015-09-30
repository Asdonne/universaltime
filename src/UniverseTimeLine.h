#pragma once
  
typedef struct {
  int minutes_elapsed;
  char* event_message;
  char* historic_time;
}event;  

void init_all_events();

char* itoa(int num);