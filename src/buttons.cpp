//#include "buttons.h"
//#include <PCF8574.h>
//#include "settings.h"
//#include <PCF8583.h>
//#include "menu.h"
#include "main.h"
//#include "WIFI.h"
//#include "LCD.h"

/* extern PCF8574 pcf8574_buttons;
extern PCF8574::DigitalInput cur_state;
extern app_states state;
extern app_states prev_state;
extern String list_str;
extern uint8_t list_cnt;
extern uint8_t list_shift;
extern uint8_t list_cursor_pos; */

////////////////// временные переменные
extern String last_bt;
//extern uint8_t set_arr[];
extern PCF8583 rtc;
extern int set_cnt;
//////////////////

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
  switch(states.peek()){
    case MAIN:
      menu_show();  
    break;
    case MENU:
      menu_up_level();  
      menu_touch();
    break;
    case CONFIRM:
      hide_confirm_dialog(true);
    break;
    case WIFI_SCAN:
      states.pop();
      stop_scan();
    break;
    case WIFI_SCAN_COMPLETED:
      states.pop();
      stop_scan();
    break;
    case INPUT_TEXT:
      hide_input();
    break;
  }

}

void bt_softr_down(){
  switch(states.peek()){
    case MAIN:
      
    break;
    case MENU:
      menu_hide();
    break;
    case CONFIRM:
      hide_confirm_dialog(false);
    break;
    case INPUT_TEXT:
      switch_input();
    break;
  }

}

void bt_left_down(){
  switch(states.peek()){
    case MAIN:
      
    break;
    case MENU:
 
    break;
    case WIFI_SCAN_COMPLETED:

    break;
    case INPUT_TEXT:
      input_left();
    break;
  }
}

void bt_right_down(){
    switch(states.peek()){
    case MAIN:
      
    break;
    case MENU:
 
    break;
    case WIFI_SCAN_COMPLETED:

    break;
    case INPUT_TEXT:
      input_right();
    break;
  }
}

void bt_up_down(){
  switch(states.peek()){
    case MAIN:
      
    break;
    case MENU:
      menu_prev_item();
      menu_touch();
    break;
    case WIFI_SCAN_COMPLETED:
      move_cursor_up();
    break;
    case INPUT_TEXT:
      input_up();
    break;
  }

}

void bt_down_down(){
  switch(states.peek()){
    case MAIN:
      
    break;
    case MENU:
      menu_next_item();
      menu_touch();
    break;
    case WIFI_SCAN_COMPLETED:
      move_cursor_down();
    break;
    case INPUT_TEXT:
      input_down();
    break;
  }
}

void bt_ok_down(){
  switch(states.peek()){
    case MAIN:
      
    break;
    case MENU:
      menu_action(true);  
      menu_touch();
    break;
    case WIFI_SCAN_COMPLETED:
      connect_to_selected_wifi();
    break;
    case INPUT_TEXT:
      input_ok();
    break;
  }
  //last_bt = "bt_ok_down";
  //set_arr[0] = 1;
  //set_arr[1] = 2;
  //set_arr[2] = 3;
  //set_arr[3] = 4;
  //set_arr[236] = 237;
  //set_arr[237] = 238;
  //set_arr[238] = 239;
  //set_arr[239] = 240;
  //set_cnt = rtc.setROM(set_arr);
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
  delay(1);
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

