#include <Arduino.h>
#include "LCD.h"
#include <Adafruit_GFX.h>
//#include <Adafruit_PCD8544.h>
#include <PCF8574_PCD8544.h>
#include <ESP8266WiFi.h>

extern PCF8574_PCD8544 display;
extern char ctime1[6];

////////////////// временные переменные
extern String last_bt;
//////////////////

void Init_LCD(){
  display.begin(1000000L, LCD_SDA, LCD_SCL);
  display.cp437(true);
  display.clearDisplay();
  display.display();
  display.setContrast(60);
  display.setTextSize(1);
  display.setTextColor(BLACK);
  set_bl(BL_ON);
}

void set_bl(uint8_t bl){
 display.digitalWrite(LCD_BL_PIN, bl);
}

void update_display()
{
  display.clearDisplay();
  draw_time();
  //draw_heater();
  drawRSSI();

  //////////////////////
  display.setTextSize(1);
  display.setCursor(0, 12);
  display.print(last_bt);
  ///////////////////

  display.display();
  //digitalWrite(LCD_BL_PIN, settings[T_BL]);
}

void draw_time(){
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(ctime1);
}

void drawRSSI() {
  display.drawBitmap(58, 0,  antenna_bmp, 8, 8, 1);
  if (WiFi.status() == WL_CONNECTED) {
    if (WiFi.RSSI() > -50 && WiFi.RSSI() < 0)
    {
      display.drawBitmap(66, 0,  wifi_5_bmp, 16, 8, 1);
    }
    else if (WiFi.RSSI() > -60 && WiFi.RSSI() <= -50)
    {
      display.drawBitmap(66, 0,  wifi_4_bmp, 16, 8, 1);
    }
    else if (WiFi.RSSI() > -70 && WiFi.RSSI() <= -60)
    {
      display.drawBitmap(66, 0,  wifi_3_bmp, 16, 8, 1);
    }
    else if (WiFi.RSSI() > -80 && WiFi.RSSI() <= -70)
    {
      display.drawBitmap(66, 0,  wifi_2_bmp, 16, 8, 1);
    }
    else
    {
      display.drawBitmap(66, 0,  wifi_1_bmp, 16, 8, 1);
    }

    //  display.print(WiFi.RSSI());
  } else {
    display.drawBitmap(66, 0,  wifi_off_bmp, 16, 8, 1);
  }
}


void drawstrc1(uint8_t _y, String source, uint8_t _ts){
  uint8_t sl;
  uint8_t dx;
  sl = source.length();
  dx = (display.width() - sl*6*_ts)/2;
  display.setCursor(dx, _y);
  display.print(source);
}

String utf8rus(String source)
{
  int i, k;
  String target;
  unsigned char n;
  char m[2] = { '0', '\0' };

  k = source.length(); i = 0;

  while (i < k) {
    n = source[i]; i++;

    if (n >= 0xC0) {
      switch (n) {
        case 0xD0: {
            n = source[i]; i++;
            if (n == 0x81) {
              n = 0xA8;
              break;
            }
            if (n >= 0x90 && n <= 0xBF) n = n + 0x30;
            break;
          }
        case 0xD1: {
            n = source[i]; i++;
            if (n == 0x91) {
              n = 0xB8;
              break;
            }
            if (n >= 0x80 && n <= 0x8F) n = n + 0x70;
            break;
          }
      }
    }
    m[0] = n; target = target + String(m);
  }
  return target;
}

