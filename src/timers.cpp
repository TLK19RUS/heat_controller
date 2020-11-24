#include "main.h"
//#include <Arduino.h>
//#include <Ticker.h>
//#include "timers.h"
//#include "menu.h"

/* extern Ticker ticker1;
extern Ticker ticker2;
extern Ticker ticker3;
extern Ticker ticker4;
extern uint8_t f_readbuttons;
extern uint8_t f_update_display;
extern uint8_t f_update_rtc; */

void Init_timers(){
  ticker1.attach(1, timer1);
  ticker2.attach(0.5, timer05);
  ticker3.attach(0.2, timer01);
  ticker4.attach(0.001, timer001);
}

void timer1(){
  menu_check();
  //DEBUG_PRINTLN(get_status_name( WiFi.status()));
  //DEBUG_PRINT(main_set.ssid);
  //DEBUG_PRINT("");
  //DEBUG_PRINTLN(main_set.pass);
  //DEBUG_PRINTLN(main_set.ssid);
  //DEBUG_PRINTLN(main_set.pass);
  //DEBUG_PRINTLN(main_set.ROM[239]);
  //DEBUG_PRINTLN(main_set.bssid[0], HEX);
  //DEBUG_PRINTLN(main_set.bssid[1], HEX);
  //DEBUG_PRINTLN(main_set.bssid[2], HEX);
  //DEBUG_PRINTLN(main_set.bssid[3], HEX);
  //DEBUG_PRINTLN(main_set.bssid[4], HEX);
  //DEBUG_PRINTLN(main_set.bssid[5], HEX);

  //station_config cfg;
  //wifi_station_get_config(&cfg);
  //DEBUG_PRINTLN((char *)cfg.ssid);
  //DEBUG_PRINTLN((char *)cfg.password);
  //DEBUG_PRINTLN(cfg.bssid_set);
  //DEBUG_PRINTLN(cfg.bssid[0], HEX);
  //DEBUG_PRINTLN(cfg.bssid[1], HEX);
  //DEBUG_PRINTLN(cfg.bssid[2], HEX);
  //DEBUG_PRINTLN(cfg.bssid[3], HEX);
  //DEBUG_PRINTLN(cfg.bssid[4], HEX);
  //DEBUG_PRINTLN(cfg.bssid[5], HEX);

}

void timer05(){
  f_update_rtc = 1;
}

void timer01(){
  f_update_display = 1;
}

void timer001(){
  f_readbuttons = 1;
}