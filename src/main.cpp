#include <Arduino.h>
#include "func.h"
#include "LCD.h"
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(LCD_SCLK_PIN, LCD_DIN_PIN, LCD_DC_PIN, LCD_RST_PIN);

void setup() {
  Init_LCD();
}

void loop() {
  display.clearDisplay();
  display.setTextSize(1);
  drawstrc1(15, utf8rus("Привет, мир!"), 1);
  display.setCursor(2, 40);
  display.print(utf8rus("ДА"));
  display.setCursor(66, 40);
  display.print(utf8rus("НЕТ"));
  display.display();
  delay(1000);
}