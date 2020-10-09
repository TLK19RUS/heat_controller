#include <Arduino.h>
#include <Ticker.h>
#include "func.h"
#include "LCD.h"
#include "buttons.h"
#include "timers.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <PCF8574.h>


Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_SCLK_PIN, LCD_DIN_PIN, LCD_DC_PIN, LCD_RST_PIN);

PCF8574 pcf8574_buttons(0x38,1,3);
PCF8574::DigitalInput cur_state;
uint8_t f_readbuttons = 0;
uint8_t f_update_display = 0;

Ticker ticker3;

void setup() {
  Init_buttons();
  Init_LCD();
  Init_timers();
}

void loop() {
  if (f_readbuttons==1){
    f_readbuttons = 0;
    readbuttons();
  }
  if (f_update_display==1){
    f_update_display = 0;
    update_display();
  }
}