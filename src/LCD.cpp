//#include <Arduino.h>
//#include "LCD.h"
//#include <Adafruit_GFX.h>
//#include <PCF8574_PCD8544.h>
//#include <ESP8266WiFi.h>
#include "main.h"
//#include "menu.h"
//#include "StackList.h"

/* extern PCF8574_PCD8544 display;
extern char ctime1[6];
extern uint8_t set_arr[];
extern app_states state;
extern app_states prev_state;
extern menu_item current_menu;
extern String confirm_dialog_text;
extern String list_str;
extern uint8_t list_cnt;
extern uint8_t list_shift;
extern uint8_t list_cursor_pos;

extern String str_alpha_lower;
extern String str_alpha_upper;
extern String str_symbols;
extern uint8_t alpha_lower_count;
extern uint8_t alpha_upper_count;
extern uint8_t symbols_count;
extern input_modes input_mode;
extern uint8_t input_x;
extern uint8_t input_y;
extern String input_str; */


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

void ud(){
  f_update_display = 1;
}

void update_display()
{
  display.clearDisplay();
  draw_time();

  //draw_heater();
  drawRSSI();
  
  if (states.peek() == ROM_CRC_ERROR){
    draw_crc_error();
  }
  
  if (states.peek() == MAIN){
    draw_date();
  }

  if (states.peek() == MENU){
    draw_menu_new();
  }
  if (states.peek() == CONFIRM){
    draw_confirm_dialog();
  }
  if (states.peek() == MESSAGE){
    draw_message_dialog();
  }
  if (states.peek() == WIFI_SCAN){
    draw_wifi_scan();
  }
  if (states.peek() == WIFI_SCAN_COMPLETED){
    draw_wifi_scan_completed();
  }
  if (states.peek() == INPUT_TEXT){
    draw_input();
  }
  
  draw_soft_bt();
  display.display();
  //digitalWrite(LCD_BL_PIN, settings[T_BL]);
}

void draw_time(){
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(ctime1);
}

void draw_date(){
  //display.setTextSize(1);
  //display.setCursor(0, 12);
  //display.print(ms);
  //display.print(".");
  //display.print(rtc.getMonth());
  //display.print(".");
  //display.print(rtc.getYear());
  //display.print(" ");
  //display.print(rtc.getWeekday()+1);

  drawBitmapFont(44, 42, lpad(rtc.getDay(),2, '0')+"."+lpad(rtc.getMonth(),2, '0')+"."+String(rtc.getYear()-2000));
}

void drawBitmapFont(uint8_t x, uint8_t y, String value){
  uint8_t sx = x;
  for (uint8_t i=0;i<value.length();i++){
    switch(value[i]){
      case '0':
        display.drawBitmap(sx, y,  char_0, 4, 5, 1);
        sx += 5;
      break;
      case '1':
        display.drawBitmap(sx, y,  char_1, 4, 5, 1);
        sx += 5;
      break;
      case '2':
        display.drawBitmap(sx, y,  char_2, 4, 5, 1);
        sx += 5;
      break;
      case '3':
        display.drawBitmap(sx, y,  char_3, 4, 5, 1);
        sx += 5;
      break;
      case '4':
        display.drawBitmap(sx, y,  char_4, 4, 5, 1);
        sx += 5;
      break;
      case '5':
        display.drawBitmap(sx, y,  char_5, 4, 5, 1);
        sx += 5;
      break;
      case '6':
        display.drawBitmap(sx, y,  char_6, 4, 5, 1);
        sx += 5;
      break;
      case '7':
        display.drawBitmap(sx, y,  char_7, 4, 5, 1);
        sx += 5;
      break;
      case '8':
        display.drawBitmap(sx, y,  char_8, 4, 5, 1);
        sx += 5;
      break;
      case '9':
        display.drawBitmap(sx, y,  char_9, 4, 5, 1);
        sx += 5;
      break;
      case '.':
        display.drawBitmap(sx, y,  char_dot, 4, 5, 1);
        sx += 5;
      break;
      case '-':
        display.drawBitmap(sx, y,  char_dash, 4, 5, 1);
        sx += 5;
      break;
      case ':':
        display.drawBitmap(sx, y,  char_colon, 4, 5, 1);
        sx += 5;
      break;
      case 'A':
        display.drawBitmap(sx, y,  char_a, 4, 5, 1);
        sx += 5;
      break;
      case 'B':
        display.drawBitmap(sx, y,  char_b, 4, 5, 1);
        sx += 5;
      break;
      case 'C':
        display.drawBitmap(sx, y,  char_c, 4, 5, 1);
        sx += 5;
      break;
      case 'D':
        display.drawBitmap(sx, y,  char_d, 4, 5, 1);
        sx += 5;
      break;
      case 'E':
        display.drawBitmap(sx, y,  char_e, 4, 5, 1);
        sx += 5;
      break;
      case 'F':
        display.drawBitmap(sx, y,  char_f, 4, 5, 1);
        sx += 5;
      break;
    }
  }
}

void drawBitmapFont(uint8_t x, uint8_t y, int value){

}

void draw_crc_error(){
  drawstrc(12, utf8rus("Ошибка E1\nROM CRC ERROR"), 1);
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
  if (states.peek() == ROM_CRC_ERROR){
   display.setCursor(0, 40);
   display.print(utf8rus("REBOOT"));
   display.setCursor(54, 40);
   display.print(utf8rus("RESET"));
  }

  if (states.peek() == MAIN){
   display.setCursor(0, 40);
   display.print(utf8rus("меню"));  
  }
  if (states.peek() == MENU){
   display.setCursor(0, 40);
   display.print(utf8rus("назад"));
   display.setCursor(54, 40);
   display.print(utf8rus("выход"));
  }
  if ((states.peek() == WIFI_SCAN) || (states.peek() == WIFI_SCAN_COMPLETED)){
   display.setCursor(0, 40);
   display.print(utf8rus("назад"));
  }
  if (states.peek() == INPUT_TEXT){
   display.setCursor(0, 40);
   if (input_str==""){
    display.print(utf8rus("назад"));
   }else{
     display.print("ok");
   }
   display.setCursor(66, 40);
   if (input_mode==ALPHA_UPPER){
     display.print(utf8rus("АБВ"));
   }
   if (input_mode==ALPHA_LOWER){
     display.print(utf8rus("абв"));
   }
   if (input_mode==SYMBOLS){
     display.print("!?#");
   }
  }
}

void draw_confirm_dialog(){
  display.setTextSize(1);
  drawstrc(8, utf8rus(confirm_dialog_text), 1);
  display.setCursor(0, 40);
  display.print(utf8rus("ДА"));
  display.setCursor(66, 40);
  display.print(utf8rus("НЕТ"));
}

void draw_message_dialog(){
  display.setTextSize(1);
  drawstrc(8, utf8rus(message_dialog_text), 1);
  display.setCursor(0, 40);
  display.print("OK");
}

void draw_wifi_scan(){
  drawstrc(12, utf8rus("поиск сетей"),1);
  //display.setCursor(2, 12);
  //display.print(utf8rus("поиск сетей"));
}

void draw_wifi_scan_completed(){
  int8_t sc = WiFi.scanComplete();
  if (sc>0){
    draw_list(list_shift);
  }
  else{
    drawstrc(12,"Wi-Fi сети\nне найдены",1);
    //display.setCursor(2, 12);
    //display.print(utf8rus("Wi-Fi сети"));
    //display.setCursor(2, 20);
    //display.print(utf8rus("не найдены"));
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
      String tt = list_str.substring(fi, ci);
      int ci2 = tt.indexOf('\t');
      if (ci2 != -1){
        tt = tt.substring(0,ci2);
      }
      display.print(tt);
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
    String tt = list_str.substring(fi);
    int ci2 = tt.indexOf('\t');
    if (ci2 != -1){
      tt = tt.substring(0,ci2);
    }
    display.print(tt);
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

uint8_t get_cursor_pos_in_list(){
  return list_shift + list_cursor_pos - 1;
}

uint8_t get_value_from_selected_item(){
  int8_t ret = -1;
  uint8_t i = 0;
  int fi = 0;
  uint8_t cp = get_cursor_pos_in_list();
  int ci = list_str.indexOf('|');
  while ((ci != -1) && (ret == -1)){
    if (i==cp){
      String tt = list_str.substring(fi, ci);
      int ci2 = tt.indexOf('\t');
      if (ci2 != -1){
        tt = tt.substring(ci2+1);
        ret = tt.toInt();
      }
    }
    fi = ci + 1;
    i++;
    ci = list_str.indexOf('|', ci+1);
  }
  if (ret==-1 && i==cp){
    String tt = list_str.substring(fi, ci);
    int ci2 = tt.indexOf('\t');
    if (ci2 != -1){
      tt = tt.substring(ci2+1);
      ret = tt.toInt();
    }
  }
  return ret;
}

void drawstrc1(uint8_t _y, String source, uint8_t _ts){
  uint8_t sl;
  uint8_t dx;
  sl = source.length();
  dx = (display.width() - sl*6*_ts)/2;
  display.setCursor(dx, _y);
  display.print(source);
}

void drawstrc(uint8_t _y, String source, uint8_t _ts){
  int8_t np = source.indexOf('\n');
  uint8_t fi = 0;
  uint8_t y = _y;
  uint8_t sl;
  uint8_t dx;
  String str = "";
  while (np != -1) {
    str = source.substring(fi, np);
    //DEBUG_PRINTLN(str);
    sl = str.length();
    dx = (display.width() - sl*6*_ts)/2;
    display.setCursor(dx, y);
    display.print(str);

    fi = np+1;
    np = source.indexOf('\n', np+1);
    y = y + 8;
  }
  str = source.substring(fi, np);
  sl = str.length();
  dx = (display.width() - sl*6*_ts)/2;
  display.setCursor(dx, y);
  display.print(str);
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

void draw_input (){
  display.setTextSize(1);
  //display.setTextColor(WHITE, BLACK);
  display.setCursor(0, 9);
  if (input_str.length()>12){
    display.print((char)187+input_str.substring(input_str.length()-12));
  }else{
    display.print((char)187+input_str);
  }
  display.setCursor(78, 9);
  display.print((char)171);

  for (uint8_t y=0;y<3;y++){
      for (uint8_t x=0;x<14;x++){
        if (x==input_x && y==input_y){
          display.setTextColor(WHITE, BLACK);
        }
        display.setCursor(0+x*6, 17+y*8);
        switch (input_mode) {
        case ALPHA_LOWER:
          if (x+y*14<alpha_lower_count){
            display.print(str_alpha_lower[x+y*14]);
          }
          break;
        case ALPHA_UPPER:
          if (x+y*14<alpha_upper_count){
            display.print(str_alpha_upper[x+y*14]);
          }
          break;
        case SYMBOLS:
          if (x+y*14<symbols_count){
            display.print(str_symbols[x+y*14]);
          }
          break;    
        }
        if (x==input_x && y==input_y){
          display.setTextColor(BLACK);
        }
      }
    }

}

boolean cursor_pos_correct(){
  boolean ret = true;
  switch (input_mode)
  {
    case ALPHA_LOWER:
      if (input_x + input_y*14 >= alpha_lower_count){
        ret = false;
      }
    break;
    case ALPHA_UPPER:
      if (input_x + input_y*14 >= alpha_upper_count){
        ret = false;
      }
    break;
    case SYMBOLS:
      if (input_x + input_y*14 >= symbols_count){
        ret = false;
      }
    break;
  }
  return ret;
}

void input_up(){
  if (input_y == 0){
    input_y = 2;
  }else{
    input_y--;
  }
  if (!cursor_pos_correct()){
    input_up();
  }
}

void input_down(){
  if (input_y == 2){
    input_y = 0;
  }else{
    input_y++;
  }
  if (!cursor_pos_correct()){
    input_down();
  }
}

void input_left(){
  if (input_x == 0){
    input_x = 13;
  }else{
    input_x--;
  }
  if (!cursor_pos_correct()){
    input_left();
  }
}
void input_right(){
 if (input_x == 13){
    input_x = 0;
  }else{
    input_x++;
  }
  if (!cursor_pos_correct()){
    input_right();
  }
}

void input_ok(){
  switch (input_mode)
  {
  case ALPHA_LOWER:
    input_str = input_str + str_alpha_lower[input_x+input_y*14];
    break;
  case ALPHA_UPPER:
    input_str = input_str + str_alpha_upper[input_x+input_y*14];
    break;
  case SYMBOLS:
    input_str = input_str + str_symbols[input_x+input_y*14];
    break;
  }
}


void show_input(){
  input_str = "";
  input_x = 0;
  input_y = 0;
  //prev_state = state;
  states.push(INPUT_TEXT);
}

void hide_input(){
  states.pop();
  if (states.peek()==WIFI_CONNECT){
    if (input_str!=""){
      wifi_begin();
    }
    states.pop();
  }

}

void switch_input(){
  switch(input_mode){
    case ALPHA_LOWER:
      input_mode = ALPHA_UPPER;
    break;
    case ALPHA_UPPER:
      input_mode = SYMBOLS;
    break;
    case SYMBOLS:
      input_mode = ALPHA_LOWER;
    break;
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

