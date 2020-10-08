#include <Arduino.h>
#define LCD_RST_PIN 4
#define LCD_DC_PIN  12
#define LCD_DIN_PIN 13
#define LCD_SCLK_PIN  14
#define LCD_BL_PIN  15

void Init_LCD();
void drawstrc1(uint8_t _y, String source, uint8_t _ts);
String utf8rus(String source);