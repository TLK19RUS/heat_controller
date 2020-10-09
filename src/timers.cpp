#include <Arduino.h>
#include <Ticker.h>
#include "timers.h"

extern Ticker ticker3;
extern uint8_t f_readbuttons;

void Init_timers(){
  ticker3.attach(0.1, timer01);
}

void timer01(){
  f_readbuttons = 1;
}