#include "buttons.h"
#include <Adafruit_PCD8544.h>
#include <PCF8574.h>

extern PCF8574 pcf8574_buttons;
extern PCF8574::DigitalInput cur_state;
extern Adafruit_PCD8544 display;

void Init_buttons(){
  pcf8574_buttons.pinMode(P0, INPUT_PULLUP);
  pcf8574_buttons.pinMode(P1, INPUT_PULLUP);
  pcf8574_buttons.pinMode(P2, INPUT_PULLUP);
  pcf8574_buttons.pinMode(P3, INPUT_PULLUP);
  pcf8574_buttons.pinMode(P4, INPUT_PULLUP);
  pcf8574_buttons.pinMode(P5, INPUT_PULLUP);
  pcf8574_buttons.pinMode(P6, INPUT_PULLUP);
  pcf8574_buttons.pinMode(P7, INPUT_PULLUP);
  pcf8574_buttons.begin();
  cur_state.p0 = 1;
  cur_state.p1 = 1;
  cur_state.p2 = 1;
  cur_state.p3 = 1;
  cur_state.p4 = 1;
  cur_state.p5 = 1;
  cur_state.p6 = 1;
  cur_state.p7 = 1;
}

void bt_softl_down(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("bt_softl_down");
  display.display();
}
//0
void bt_softr_down(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("bt_softr_down");
  display.display();
}
//5
void bt_left_down(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("bt_left_down");
  display.display(); 
}
//1
void bt_right_down(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("bt_right_down");
  display.display();  
}
//2
void bt_up_down(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("bt_up_down");
  display.display();
}
//6
void bt_down_down(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("bt_down_down");
  display.display();
}
//3
void bt_ok_down(){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("bt_ok_down");
  display.display();
}


void bt_softl_up(){}
void bt_softr_up(){}
void bt_left_up(){}
void bt_right_up(){}
void bt_up_up(){}
void bt_down_up(){}
void bt_ok_up(){}


void readbuttons(){
  PCF8574::DigitalInput pins = pcf8574_buttons.digitalReadAll();
  delay(10);
  PCF8574::DigitalInput pins2 = pcf8574_buttons.digitalReadAll();
  if (pins.p0 == pins2.p0){
    if (pins2.p0 != cur_state.p0){
      if (pins2.p0==0){
        bt_softr_down();
      }else{
        bt_softr_up();
      }
      cur_state.p0 = pins2.p0;
    }
  }

  if (pins.p1 == pins2.p1){
    if (pins2.p1 != cur_state.p1){
      if (pins2.p1==0){
        bt_right_down();
      }else{
        bt_right_up();
      }
      cur_state.p1 = pins2.p1;
    }
  }
  
  if (pins.p4 == pins2.p4){
    if (pins2.p4 != cur_state.p4){
      if (pins2.p4==0){
        bt_softl_down();
      }else{
        bt_softl_up();
      }
      cur_state.p4 = pins2.p4;
    }
  }  

  if (pins.p2 == pins2.p2){
    if (pins2.p2 != cur_state.p2){
      if (pins2.p2==0){
        bt_up_down();
      }else{
        bt_up_up();
      }
      cur_state.p2 = pins2.p2;
    }
  }  
  
  if (pins.p3 == pins2.p3){
    if (pins2.p3 != cur_state.p3){
      if (pins2.p3==0){
        bt_ok_down();
      }else{
        bt_ok_up();
      }
      cur_state.p3 = pins2.p3;
    }
  }    

  if (pins.p5 == pins2.p5){
    if (pins2.p5 != cur_state.p5){
      if (pins2.p5==0){
        bt_left_down();
      }else{
        bt_left_up();
      }
      cur_state.p5 = pins2.p5;
    }
  }    

  if (pins.p6 == pins2.p6){
    if (pins2.p6 != cur_state.p6){
      if (pins2.p6==0){
        bt_down_down();
      }else{
        bt_down_up();
      }
      cur_state.p6 = pins2.p6;
    }
  } 
}

