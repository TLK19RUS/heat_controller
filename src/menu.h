#ifndef __MENU_H__
#define __MENU_H__

#include "Arduino.h"

#define menu_show_time 15

enum item_types {IT_MENU, IT_ITEM};
enum menu_actions {MENU_NONE, MENU_SETTINGS_TEMP, MENU_SETTINGS_TIME, MENU_DSPLAY_BL, MENU_REBOOT,MENU_DEFAULT,
                  MENU_WIFI_SCAN, MENU_WIFI_STATUS};

struct menu_item{
  int id;
  String name;
  int parent_id;
  item_types type;
  menu_actions action;
};

const uint8_t menu_items_count = 13;
const menu_item main_menu[] = {
  {1, "настройки", 0, IT_MENU, MENU_NONE},
  {10, "температура", 1, IT_ITEM, MENU_SETTINGS_TEMP},
  {11, "дата/время", 1, IT_ITEM, MENU_SETTINGS_TIME},
  {12, "дисплей", 1, IT_MENU, MENU_NONE},
  {121, "подсветка", 12, IT_ITEM, MENU_DSPLAY_BL},
  {13, "сеть", 1, IT_MENU, MENU_NONE},
  {131, "wi-fi", 13, IT_MENU, MENU_NONE},
  {1311, "поиск сети", 131, IT_ITEM, MENU_WIFI_SCAN},
  {1312, "статус", 131, IT_ITEM, MENU_WIFI_STATUS},
  {132, "telegram", 13, IT_MENU, MENU_NONE},
  {2, "сервис", 0, IT_MENU, MENU_NONE},
  {21, "перезагрузка", 2, IT_ITEM, MENU_REBOOT},
  {22, "сброс", 2, IT_ITEM, MENU_DEFAULT}
};

void menu_show();
void menu_hide();
void menu_touch();
void menu_check();
void menu_next_item();
void menu_prev_item();
void menu_up_level();
void menu_action(bool confirm);
menu_item menu_get_next();
menu_item menu_get_prev();
void menu_get_all_items(menu_item *menu_list);
byte menu_get_items_count();
void show_confirm_dialog(String text);
void hide_confirm_dialog(bool action);

#endif