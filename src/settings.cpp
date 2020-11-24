//#include <Arduino.h>
//#include "settings.h"
//#include <PCF8583.h>
#include "main.h"

/* extern uint8_t set_arr[];
extern PCF8583 rtc; */



void Init_settings(){
 //main_set = new TSettings();
 rtc.getROM(main_set.ROM);
 if (main_set.CRCCorrect()){
    main_set.ReadROM();
    if (main_set.def_settings){
      main_set.def_settings = false;
      SaveToRTC();
      show_message_dialog(utf8rus("Настройки были\nсброшены на\nзначения\nпо умолчанию"));
    }
    for (uint8_t i=1;i<240;i++){
      DEBUG_PRINT(main_set.ROM[i]);
      DEBUG_PRINT(" ");
    }
    DEBUG_PRINTLN("");
    DEBUG_PRINTLN(main_set.ssid);
    DEBUG_PRINTLN(main_set.pass);
 }else{
   states.push(ROM_CRC_ERROR);
   DEBUG_PRINTLN("ROM CRC ERROR !!!");
 }
 
}

void reset_settings(){
  struct station_config config;
  memset(config.ssid, 0, 32);
  memset(config.password, 0, 64);
  config.bssid_set = 1;
  config.bssid[0] = 0;
  config.bssid[1] = 0;
  config.bssid[2] = 0;
  config.bssid[3] = 0;
  config.bssid[4] = 0;
  config.bssid[5] = 0;
  wifi_station_set_config(&config);
  main_set.SetDefault();
  SaveToRTC();
  restart();
}

void SaveToRTC(){
  main_set.WriteROM();
  rtc.setROM(main_set.ROM);
}