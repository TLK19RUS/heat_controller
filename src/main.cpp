#include "main.h"

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

//uint8_t set_arr[240];

Ticker ticker1;
Ticker ticker2;
Ticker ticker3;
Ticker ticker4;

//app_states state = MAIN;
//app_states prev_state;
StackList<app_states> states;

bool confirm_dialog_visible = false;
String confirm_dialog_text = "";

String str_alpha_lower = "1234567890abcdefghijklmnopqrstuvwxyz";
String str_alpha_upper = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
String str_symbols     = ".,/;'\\`~-=!@#$%^&*()_+{}:|<>?\"";

uint8_t alpha_lower_count = str_alpha_lower.length();
uint8_t alpha_upper_count = str_alpha_upper.length();
uint8_t symbols_count = str_symbols.length();

input_modes input_mode = ALPHA_LOWER;
uint8_t input_x = 0;
uint8_t input_y = 0;
String input_str="";

menu_item current_menu;
uint8_t menu_showed=0;

String list_str;
uint8_t list_cnt;
uint8_t list_shift=0;
uint8_t list_cursor_pos=1;

TSettings main_set;

//struct {
// char ssid[33];
// char pass[64];
// uint8_t bssid[6];
//} main_set;

void setup() {
  ///////////////////
  Serial.begin(115200); //GPIO1 (TX) and GPIO3 (RX), 9600kbps, 8-bit data, no parity, 1-bit stop
  Serial.swap(); //GPIO15 (TX) and GPIO13 (RX)
  Serial.flush();
  //////////////////
  DEBUG_PRINTLN("Start");
  states.push(MAIN);
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