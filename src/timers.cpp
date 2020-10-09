#include <Arduino.h>
#include <Ticker.h>
#include "timers.h"

extern Ticker ticker3;
extern uint8_t f_readbuttons;
extern uint8_t f_update_display;

void Init_timers(){
  ticker3.attach(0.1, timer01);
}

void timer01(){
  f_readbuttons = 1;
  f_update_display = 1;
}