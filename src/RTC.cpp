//#include "RTC.h"
//#include <Arduino.h>
//#include <PCF8583.h>
#include "main.h"

/* extern PCF8583 rtc;
extern uint8_t time_blink;
extern uint8_t t_hour;
extern uint8_t t_minute;
extern uint8_t t_sec;
extern char ctime1[6]; */


void get_rtc_time(){
  t_hour = rtc.getHour();
  t_minute = rtc.getMinute();
  t_sec = rtc.getSecond();
  if (time_blink == 1) {
     sprintf(ctime1,"%2d:%02d", t_hour, t_minute);
  } else {
     sprintf(ctime1,"%2d %02d", t_hour, t_minute);
  }
  time_blink = 1 - time_blink;
}