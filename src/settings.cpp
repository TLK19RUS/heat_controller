#include <Arduino.h>
#include "settings.h"
#include <PCF8583.h>

extern uint8_t set_arr[];
extern PCF8583 rtc;

////////////////////
extern int set_cnt;
//////////////////

void Init_settings(){
 set_cnt = rtc.getROM(set_arr);
}