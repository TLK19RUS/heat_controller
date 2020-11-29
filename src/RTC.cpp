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
  //t_sec = rtc.getSecond();
  //if (time_blink == 1) {
     sprintf(ctime1,"%2d:%02d", t_hour, t_minute);
  //} else {
  //   sprintf(ctime1,"%2d %02d", t_hour, t_minute);
  //}
  //time_blink = 1 - time_blink;
  if (t_pminute!=t_minute){
    t_pminute=t_minute;
    ud();
  }
}

void sync_time(){
  timeClient.begin();
  timeClient.setTimeOffset(main_set.GetTimeZoneOffset());
  if (timeClient.forceUpdate()){
    time_t rawtime = timeClient.getEpochTime();
    int wday = weekday(rawtime);
    if (wday>1){
      wday--;
    }else{
      wday=7;
    }
    /*DEBUG_PRINTLN(rawtime);
    DEBUG_PRINT(day(rawtime));
    DEBUG_PRINT(".");
    DEBUG_PRINT(month(rawtime));
    DEBUG_PRINT(".");
    DEBUG_PRINT(year(rawtime));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(hour(rawtime));
    DEBUG_PRINT(":");
    DEBUG_PRINT(minute(rawtime));
    DEBUG_PRINT(":");
    DEBUG_PRINT(second(rawtime));
    DEBUG_PRINT(" ");
    DEBUG_PRINT(wday);*/

    rtc.setDateTime(second(rawtime), minute(rawtime), hour(rawtime), day(rawtime), month(rawtime), year(rawtime), wday);
    //rtc.setEpoch(timeClient.getEpochTime());
  }
  timeClient.end();
  ud();
}