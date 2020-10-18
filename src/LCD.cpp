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
extern String confirm_dialog_text;
extern String list_str;
extern uint8_t list_cnt;
extern uint8_t list_shift;
extern uint8_t list_cursor_pos;

////////////////// временные переменные
extern String last_bt;
extern int set_cnt;
station_config cfg;
extern uint8_t debug_cnt;
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

  display.setCursor(35, 0);
  display.print(debug_cnt);

  //draw_heater();
  drawRSSI();
  
  if (state == STATE_MENU){
    draw_menu_new();
  }
  if (state == STATE_CONFIRM){
    draw_confirm_dialog();
  }
  if (state==STATE_WIFI_SCAN){
    draw_wifi_scan();
  }
  if (state==STATE_WIFI_SCAN_COMPLETED){
    draw_wifi_scan_completed();
  }

  /*wifi_station_get_config(&cfg);*/
  
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
   display.print(utf8rus("меню"));  
  }
  if (state==STATE_MENU){
   display.setCursor(0, 40);
   display.print(utf8rus("назад"));
   display.setCursor(54, 40);
   display.print(utf8rus("выход"));
  }
  if ((state==STATE_WIFI_SCAN) || (state==STATE_WIFI_SCAN_COMPLETED)){
   display.setCursor(0, 40);
   display.print(utf8rus("назад"));
  }
}

void draw_confirm_dialog(){
  display.setTextSize(1);
  drawstrc1(15, utf8rus(confirm_dialog_text), 1);
  display.setCursor(0, 40);
  display.print(utf8rus("ДА"));
  display.setCursor(66, 40);
  display.print(utf8rus("НЕТ"));
}

void draw_wifi_scan(){
  display.setCursor(2, 12);
  display.print(utf8rus("поиск сетей"));
}

void draw_wifi_scan_completed(){
  int8_t sc = WiFi.scanComplete();
  if (sc>0){
    draw_list(list_shift);
  }
  else{
    display.setCursor(2, 12);
    display.print(utf8rus("Wi-Fi сети"));
    display.setCursor(2, 20);
    display.print(utf8rus("не найдены"));
  }
}

void draw_list(uint8_t start){
  int ci = list_str.indexOf('|');
  int fi = 0;
  uint8_t i=0;
  //debug_cnt = 1;
  while (ci != -1){
    if (i>=start){
      display.setCursor(6, 8+8*(i-start));
      display.print(list_str.substring(fi, ci));
    }
    fi = ci + 1;
    ci = list_str.indexOf('|', ci+1);
    i++;
    if (i>=start+LIST_LINES_CNT){
      break;
    }
    //debug_cnt++;
  }
  if ((i>=start) && (i<start+LIST_LINES_CNT)){
    display.setCursor(6, 8+8*(i-start));
    display.print(list_str.substring(fi));
  }
  display.setCursor(0, 8 + 8*(list_cursor_pos-1));
  display.print((char)187);

  /*char* line = strtok((char*)list_str.c_str(), "\n");
  uint8_t i=0;
  while (line != 0)
  {
      display.setCursor(6, 8+8*i);
      display.print(line);
      // Find the next command in input string
      line = strtok(0, "\n");
      i++;
      //debug_cnt = i;
      if (i>3){
        break;
      }
  }*/
}

void draw_menu_new(){
  display.setTextSize(1);
   
  byte mi_cnt = menu_get_items_count();

  menu_item menu_list[mi_cnt];
  menu_get_all_items(menu_list);
  for (byte i=0; i<mi_cnt;i++){
    display.setCursor(6, 8 + 8*i);  
    if (menu_list[i].id==current_menu.id){
      display.setCursor(0, 8 + 8*i);
      display.print((char)187);
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


void move_cursor_down(){
  if (list_cursor_pos<LIST_LINES_CNT){
    list_cursor_pos++;      
  }else{
    if (list_shift<list_cnt-LIST_LINES_CNT){
      list_shift++;
    }
  }
}

void move_cursor_up(){
  if (list_cursor_pos>1){
    list_cursor_pos--;      
  }else{
    if (list_shift>0){
      list_shift--;
    }
  }
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

