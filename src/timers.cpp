#include <Arduino.h>
#include <Ticker.h>
#include "timers.h"
#include "menu.h"

extern Ticker ticker1;
extern Ticker ticker2;
extern Ticker ticker3;
extern uint8_t f_readbuttons;
extern uint8_t f_update_display;
extern uint8_t f_update_rtc;



void Init_timers(){
  ticker1.attach(1, timer1);
  ticker2.attach(0.5, timer05);
  ticker3.attach(0.1, timer01);
}

void timer1(){
  menu_check();
}

void timer05(){
  f_update_rtc = 1;
}

void timer01(){
  f_readbuttons = 1;
  f_update_display = 1;
}