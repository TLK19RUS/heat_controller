#include "menu.h"
#include "main.h"
#include "WIFI.h"

extern app_states state;
extern menu_item current_menu;
extern uint8_t menu_cursor_pos;
extern uint8_t menu_showed;
extern app_states prev_state;
extern bool confirm_dialog_visible;
extern String confirm_dialog_text;

void menu_show(){
  current_menu = main_menu[0];
  //menu_cursor_pos=1;
  state=MENU;
  menu_touch();
}

void menu_hide(){
  state=MAIN;
}

void menu_touch(){
  menu_showed = 0;
}

void menu_check(){
  if ((state==MENU) || (state==CONFIRM)){
    menu_showed++;
    if (menu_showed>menu_show_time){
      if (state==MENU){
        menu_hide();
      } else if (state==CONFIRM){
        hide_confirm_dialog(false);
      }
    }
  }else{
    menu_touch();  
  }
}


void menu_next_item(){
  //if (menu_cursor_pos<3){
  //    menu_cursor_pos ++;
  //}

  uint8_t j=0;
  for (uint8_t i=0;i<menu_items_count;i++){
    if (main_menu[i].id == current_menu.id){
      j=i;
    }
  }
  for (uint8_t i=j+1;i<menu_items_count;i++){
    if (main_menu[i].parent_id == current_menu.parent_id){
      current_menu = main_menu[i];
      return;
    }
  }
}

void menu_prev_item(){
  //if (menu_cursor_pos>1){
  //    menu_cursor_pos --;
  //}
  int8_t j=0;
  for (int8_t i=0;i<menu_items_count;i++){
    if (main_menu[i].id == current_menu.id){
      j=i;
    }
  }
  for (int8_t i=j-1;i>=0;i--){
    if (main_menu[i].parent_id == current_menu.parent_id){
      current_menu = main_menu[i];
      return;
    }
  }
}

menu_item menu_get_next(){
  menu_item ret;
  uint8_t j=0;
  for (uint8_t i=0;i<menu_items_count;i++){
    if (main_menu[i].id == current_menu.id){
      j=i;
    }
  }
  for (uint8_t i=j+1;i<menu_items_count;i++){
    if (main_menu[i].parent_id == current_menu.parent_id){
      return main_menu[i];
    }
  }
  return ret;
}

menu_item menu_get_prev(){
  menu_item ret;
  int8_t j=0;
  for (int8_t i=0;i<menu_items_count;i++){
    if (main_menu[i].id == current_menu.id){
      j=i;
    }
  }
  for (int8_t i=j-1;i>=0;i--){
    if (main_menu[i].parent_id == current_menu.parent_id){
      return main_menu[i];
    }
  }
  return ret;
}

void menu_get_all_items(menu_item *menu_list){
  byte j=0;
  for (uint8_t i=0;i<menu_items_count;i++){
    if (main_menu[i].parent_id == current_menu.parent_id){
      menu_list[j] = main_menu[i];
      j++;
    }
  }
}

byte menu_get_items_count(){
  byte ret = 0;
  for (uint8_t i=0;i<menu_items_count;i++){
    if (main_menu[i].parent_id == current_menu.parent_id){
      ret ++;
    }
  }
  return ret;
}

byte menu_get_current_pos(){
  byte ret = 0;
  for (uint8_t i=0;i<menu_items_count;i++){
      if (main_menu[i].parent_id == current_menu.parent_id){
        if (main_menu[i].id == current_menu.id){
            return ret;
        }
        ret++;  
      }
  }
  return 0;
}

void menu_up_level(){
  if (current_menu.parent_id==0) {
    menu_hide();
    return;
  }
  for (int8_t i=0;i<menu_items_count;i++){
    if (main_menu[i].id == current_menu.parent_id){
      current_menu = main_menu[i];
      return;
    }
  }
}

void menu_action(bool confirm){
  if (current_menu.action==MENU_NONE) {
    for (int8_t i=0;i<menu_items_count;i++){
      if (main_menu[i].parent_id == current_menu.id){
        current_menu = main_menu[i];
        //menu_cursor_pos = 1;
        return;
      }
    }
  }
  if (current_menu.action==MENU_DSPLAY_BL) {
    //if (settings[T_BL]==1){
    //  set_t_bl(0);
    //}else{
    //  set_t_bl(1);
    //}
    //return;
  }
  if (current_menu.action==MENU_REBOOT) {
    if (confirm){
      show_confirm_dialog("Перезагрузка?");
    }else{
      //settings[T_MODE] = MODE_OFF;
      ESP.restart();
      return;
    }
  }
  if (current_menu.action==MENU_WIFI_SCAN) {
    prev_state = state;
    state = WIFI_SCAN;
    start_scan();
    return;
  }
}

void show_confirm_dialog(String text){
  confirm_dialog_text = text;
  confirm_dialog_visible = true;
  prev_state = state;
  state = CONFIRM;
  menu_touch();
}

void hide_confirm_dialog(bool action){
  confirm_dialog_visible = false;
  state = prev_state;
  menu_touch();
  if (action){
    menu_action(false);
  }
}
