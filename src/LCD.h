#ifndef __LCD_H__
#define __LCD_H__

#include <Arduino.h>
#define LCD_ADDR 36 // 0x24
#define LCD_SDA 1
#define LCD_SCL 3
//// PCF8574 pins
#define LCD_RST_PIN 2
#define LCD_BL_PIN  3
#define LCD_CE_PIN  4
#define LCD_DC_PIN  5
#define LCD_DIN_PIN 6
#define LCD_SCLK_PIN 7 
////
#define BL_ON 1
#define BL_OFF 0

#define LIST_LINES_CNT 4

static const unsigned char PROGMEM wifi_off_bmp[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6D, 0xB6, 0x00, 0x00 };

static const unsigned char PROGMEM wifi_1_bmp[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x6D, 0xB6, 0x00, 0x00 };

static const unsigned char PROGMEM wifi_2_bmp[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x6C, 0x00, 0x6D, 0xB6, 0x00, 0x00 };

static const unsigned char PROGMEM wifi_3_bmp[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x0D, 0x80, 0x6D, 0x80, 0x6D, 0xB6, 0x00, 0x00 };

static const unsigned char PROGMEM wifi_4_bmp[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x01, 0xB0, 0x0D, 0xB0, 0x6D, 0xB0, 0x6D, 0xB6, 0x00, 0x00 };

static const unsigned char PROGMEM wifi_5_bmp[] =
{ 0x00, 0x00, 0x00, 0x06, 0x00, 0x36, 0x01, 0xB6, 0x0D, 0xB6, 0x6D, 0xB6, 0x6D, 0xB6, 0x00, 0x00 };

static const unsigned char PROGMEM antenna_bmp[] =
{ 0x99, 0xDB, 0x7E, 0x3C, 0x18, 0x18, 0x18, 0x00 };

void Init_LCD();
void set_bl(uint8_t bl);
void drawstrc1(uint8_t _y, String source, uint8_t _ts);
void drawstrc(uint8_t _y, String source, uint8_t _ts);
String utf8rus(String source);
void update_display();
void draw_time();
void drawRSSI();
void draw_crc_error();
void draw_soft_bt();
void draw_menu_new();
void draw_confirm_dialog();
void draw_wifi_scan();
void draw_wifi_scan_completed();
void draw_list(uint8_t start);
void move_cursor_down();
void move_cursor_up();
uint8_t get_cursor_pos_in_list();
uint8_t get_value_from_selected_item();
void draw_input();
void show_input();
void hide_input();
void switch_input();
void input_up();
void input_down();
void input_left();
void input_right();
void input_ok();
boolean cursor_pos_correct();
void draw_message_dialog();

#endif