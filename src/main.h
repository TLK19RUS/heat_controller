#ifndef __MAIN_H__
#define __MAIN_H__

#include <Arduino.h>
#include <Ticker.h>
#include "func.h"
#include "LCD.h"
#include "RTC.h"
#include "buttons.h"
#include "timers.h"
#include "settings.h"
#include "menu.h"
#include "WIFI.h"
#include <Adafruit_GFX.h>
#include <PCF8574_PCD8544.h>
#include <PCF8574.h>
#include <PCF8583.h>
#include <ESP8266WiFi.h>
#include "StackList.h"
#include <TSettings.h>

#define DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }
#define DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }

enum app_states {MAIN, MENU, CONFIRM, INPUT_TEXT, WIFI_SCAN, WIFI_SCAN_COMPLETED, WIFI_CONNECT};
enum input_modes {ALPHA_LOWER, ALPHA_UPPER, SYMBOLS};

extern PCF8574_PCD8544 display;
extern uint8_t f_update_display;

extern PCF8574 pcf8574_buttons;
extern PCF8574::DigitalInput cur_state;
extern uint8_t f_readbuttons;

extern PCF8583 rtc;
extern uint8_t f_update_rtc;
extern uint8_t time_blink;
extern uint8_t t_hour;
extern uint8_t t_minute;
extern uint8_t t_sec;
extern char ctime1[6];

//extern uint8_t set_arr[240];

extern Ticker ticker1;
extern Ticker ticker2;
extern Ticker ticker3;
extern Ticker ticker4;

//extern app_states state;
//extern app_states prev_state;
extern StackList<app_states> states;

extern bool confirm_dialog_visible;
extern String confirm_dialog_text;

extern String str_alpha_lower;
extern String str_alpha_upper;
extern String str_symbols;

extern uint8_t alpha_lower_count;
extern uint8_t alpha_upper_count;
extern uint8_t symbols_count;

extern input_modes input_mode;
extern uint8_t input_x;
extern uint8_t input_y;
extern String input_str;

extern menu_item current_menu;
extern uint8_t menu_showed;

extern String list_str;
extern uint8_t list_cnt;
extern uint8_t list_shift;
extern uint8_t list_cursor_pos;

extern TSettings main_set;

#endif