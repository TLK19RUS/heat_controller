#include <Arduino.h>
#include "LCD.h"
#include <Adafruit_GFX.h>
#include <PCF8574_PCD8544.h>
#include <ESP8266WiFi.h>
#include "main.h"
#include "menu.h"

extern PCF8574_PCD8544 display;
extern char ctime1[6];
extern uint8_t set_arr[];
extern uint8_t state;
extern menu_item current_menu;
extern uint8_t menu_cursor_pos;

////////////////// временные переменные
extern String last_bt;
extern int set_cnt;
station_config cfg;
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
  
  if (state == STATE_MENU){
   draw_menu_new();
  }

  /*wifi_station_get_config(&cfg);
  display.setCursor(0, 12);
  display.print((char *)cfg.ssid);
  display.setCursor(0, 20);
  display.print((char *)cfg.password);
  display.setCursor(0, 28);
  display.print(cfg.bssid[0], HEX);
  display.print(":");
  display.print(cfg.bssid[1], HEX);
  display.print(":");
  display.print(cfg.bssid[2], HEX);
  display.print(":");
  display.print(cfg.bssid[3], HEX);
  display.print(":");
  display.print(cfg.bssid[4], HEX);
  display.print(":");
  display.print(cfg.bssid[5], HEX);*/

  //////////////////////
  /*display.setTextSize(1);
  display.setCursor(0, 12);
  display.print(last_bt);
  display.setCursor(0, 20);
  display.print(set_arr[0]);
  display.print(".");
  display.print(set_arr[1]);
  display.print(".");
  display.print(set_arr[2]);
  display.print(".");
  display.print(set_arr[3]);
  display.setCursor(0, 30);
  display.print(set_arr[236]);
  display.print(".");
  display.print(set_arr[237]);
  display.print(".");
  display.print(set_arr[238]);
  display.print(".");
  display.print(set_arr[239]);
  display.setCursor(0, 38);
  display.print(set_cnt);*/
  ///////////////////
  draw_soft_bt();
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

void draw_soft_bt(){
  display.setTextSize(1);
  if (state==STATE_MAIN){
   display.setCursor(0, 40);
   display.print(utf8rus("МЕНЮ"));  
  }
  if (state==STATE_MENU){
   display.setCursor(0, 40);
   display.print(utf8rus("НАЗАД"));
   display.setCursor(54, 40);
   display.print(utf8rus("ВЫХОД"));
  }
}

void draw_menu_new(){
  display.setTextSize(1);
   
  //if (menu_cursor_pos==1){

  //}
  
  byte mi_cnt = menu_get_items_count();

  menu_item menu_list[mi_cnt];
  menu_get_all_items(menu_list);

  for (byte i=0; i<mi_cnt;i++){
    display.setCursor(6, 8 + 8*i);  
    if (menu_list[i].id==current_menu.id){
      display.setCursor(0, 8 + 8*i);
      display.print(">");
    }
    display.print(utf8rus(menu_list[i].name));
  }
  display.setTextColor(BLACK);
  //display.setCursor(6, 12);
  //display.print(utf8rus(menu_get_prev().name));
  //display.setCursor(6, 20);
  //display.print(utf8rus(current_menu.name));
  //display.setCursor(6, 28);
  //display.print(utf8rus(menu_get_next().name));
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

