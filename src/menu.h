#include "Arduino.h"

#define menu_show_time 15

enum item_types {IT_MENU, IT_ITEM};
enum menu_actions {MENU_NONE, MENU_SETTINGS_TEMP, MENU_SETTINGS_TIME, MENU_DSPLAY_BL, MENU_REBOOT,MENU_DEFAULT};

struct menu_item{
  uint8_t id;
  String name;
  uint8_t parent_id;
  item_types type;
  menu_actions action;
};

const uint8_t menu_items_count = 11;
const menu_item main_menu[] = {
  {1, "Настройки", 0, IT_MENU, MENU_NONE},
  {10, "Температура", 1, IT_ITEM, MENU_SETTINGS_TEMP},
  {11, "Дата/время", 1, IT_ITEM, MENU_SETTINGS_TIME},
  {12, "Дисплей", 1, IT_MENU, MENU_NONE},
  {121, "Подсветка", 12, IT_ITEM, MENU_DSPLAY_BL},
  {13, "Сеть", 1, IT_MENU, MENU_NONE},
  {131, "Wi-Fi", 13, IT_MENU, MENU_NONE},
  {132, "Telegram", 13, IT_MENU, MENU_NONE},
  {2, "Сервис", 0, IT_MENU, MENU_NONE},
  {21, "Перезагрузка", 2, IT_ITEM, MENU_REBOOT},
  {22, "Сброс", 2, IT_ITEM, MENU_DEFAULT}
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