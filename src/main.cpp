#include <Arduino.h>
#include <Ticker.h>
#include "func.h"
#include "LCD.h"
#include "buttons.h"
#include "timers.h"
#include <Adafruit_GFX.h>
#include <PCF8574_PCD8544.h>
//#include <Adafruit_PCD8544.h>
#include <PCF8574.h>

PCF8574_PCD8544 display = PCF8574_PCD8544(LCD_ADDR, LCD_SCLK_PIN, LCD_DIN_PIN, LCD_DC_PIN, LCD_CE_PIN, LCD_RST_PIN);
uint8_t f_update_display = 0;
//Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_SCLK_PIN, LCD_DIN_PIN, LCD_DC_PIN, LCD_RST_PIN);

//PCF8574 pcf8574_LCD(LCD_ADDR, LCD_SDA, LCD_SCL);

PCF8574 pcf8574_buttons(BUTTONS_ADDR, BUTTONS_SDA, BUTTONS_SCL);
PCF8574::DigitalInput cur_state;
uint8_t f_readbuttons = 0;

Ticker ticker1;
Ticker ticker3;



////////////////// временные переменные
String last_bt = "";
//////////////////

void setup() {
  Init_buttons();
  Init_LCD();
  
  //display.clearDisplay();
  //display.setTextSize(1);
  //display.setTextColor(BLACK);
  //display.setCursor(0, 0);
  //display.print("hello");
  //display.display();
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