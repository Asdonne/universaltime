#include <pebble.h>
#include "UniverseTimeLine.h"

//typedef struct event event;  
  
static int elapsed_minutes = 0;

event all_events[3];

void init_all_events(){
  
  all_events[0].minutes_elapsed = 501;
  all_events[0].event_message =  "Andromeda Galaxy formed from a collision";
  all_events[0].historic_time =  "9000 MYA";
  
  all_events[1].minutes_elapsed = 939;
  all_events[1].event_message =   "Formation of the solar system";
  all_events[1].historic_time =   "4600 MYA";
   
    
  all_events[2].minutes_elapsed =   0;
  all_events[2].event_message =     "";
  all_events[2].historic_time =     "";
  
}

char* itoa(int num){
  
  static char buff[20] = {};
  int i = 0;
  int temp_num = num;
  int length = 0;
  
  //count how many times you can divide by 10 to get the lenght
  if (num >= 0){
    while(temp_num){
      temp_num /= 10;
      length++;
    }
  }
  for(i = 0; i < length; i++){
    buff[(length-1)-i] = '0'+(num % 10);
    num /= 10;
  }
  buff[i]='\0';
  
  return buff;
}