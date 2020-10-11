#include <Arduino.h>
#include <Ticker.h>
#include "func.h"
#include "LCD.h"
#include "RTC.h"
#include "buttons.h"
#include "timers.h"
#include "settings.h"
#include <Adafruit_GFX.h>
#include <PCF8574_PCD8544.h>
//#include <Adafruit_PCD8544.h>
#include <PCF8574.h>
#include <PCF8583.h>

PCF8574_PCD8544 display = PCF8574_PCD8544(LCD_ADDR, LCD_SCLK_PIN, LCD_DIN_PIN, LCD_DC_PIN, LCD_CE_PIN, LCD_RST_PIN);
uint8_t f_update_display = 0;
//Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_SCLK_PIN, LCD_DIN_PIN, LCD_DC_PIN, LCD_RST_PIN);

//PCF8574 pcf8574_LCD(LCD_ADDR, LCD_SDA, LCD_SCL);

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



////////////////// временные переменные
String last_bt = "";
int set_cnt = 0;
//////////////////

void setup() {
  Init_settings();
  Init_buttons();
  Init_LCD();
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