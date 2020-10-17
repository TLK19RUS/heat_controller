#include "main.h"
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

PCF8574_PCD8544 display = PCF8574_PCD8544(LCD_ADDR, LCD_SCLK_PIN, LCD_DIN_PIN, LCD_DC_PIN, LCD_CE_PIN, LCD_RST_PIN);
uint8_t f_update_display = 0;

PCF8574 pcf8574_buttons(BUTTONS_ADDR, BUTTONS_SDA, BUTTONS_SCL);
PCF8574::DigitalInput cur_state;
uint8_t f_readbuttons = 0;

PCF8583 rtc(0xA0);
uint8_t f_update_rtc = 0;
uint8_t time_blink = 1;
uint8_t t_hour=0;
uint8_t t_minute=0;
uint8_t t_sec=0;
char ctime1[6]="--:--";

uint8_t set_arr[240];

Ticker ticker1;
Ticker ticker2;
Ticker ticker3;

uint8_t state = STATE_MAIN;

menu_item current_menu;
uint8_t menu_cursor_pos=1;
uint8_t menu_showed=0;

////////////////// временные переменные
String last_bt = "";
int set_cnt = 0;
//////////////////

void setup() {
  Init_settings();
  Init_buttons();
  Init_LCD();
  Init_wifi();
  Init_timers();
  
}

void loop() {
  if (f_readbuttons==1){
    f_readbuttons = 0;
    readbuttons();
  }
  if (f_update_rtc==1){
    f_update_rtc = 0;
    get_rtc_time();
  }
  if (f_update_display==1){
    f_update_display = 0;
    update_display();
  }
}