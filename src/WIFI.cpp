#include "WIFI.h"
#include <ESP8266WiFi.h>
#include "main.h"

extern uint8_t state;
extern uint8_t prev_state;
extern String list_str;

//////////////
extern uint8_t debug_cnt;
//////////////


void Init_wifi(){
  if (WiFi.getPersistent() == true){
    WiFi.persistent(false);
  }
  if (WiFi.getAutoConnect() == true)    //configuration will be saved into SDK flash area
  {
    WiFi.setAutoConnect(false);   //on power-on automatically connects to last used hwAP
  }
  if (WiFi.getAutoReconnect() != true){
    WiFi.setAutoReconnect(true);    //automatically reconnects to hwAP in case it's disconnected
  }
  
  //WiFi.reconnect();
}

void scan_completed(int scan_result){
  if (scan_result>0){
    
    uint8_t net_rssi[scan_result];

    for(uint8_t i=0;i<scan_result;i++){
      net_rssi[i]=i;
    }
    uint8_t ti;
    for(uint8_t i=0;i<scan_result-1;i++){
      for(uint8_t j=i+1;j<scan_result;j++){
        if (WiFi.RSSI(net_rssi[j])>WiFi.RSSI(net_rssi[i])) {
          ti = net_rssi[j];
          net_rssi[j] = net_rssi[i];
          net_rssi[i] = ti;
        }
      }  
    }
    list_str = "";
    for(uint8_t i=0;i<scan_result;i++){
      String ssid = WiFi.SSID(net_rssi[i]);
      if (ssid.length()>13) {
        ssid = ssid.substring(0,13);
      }
      if (i==0){
        list_str = ssid;
      }else{
        list_str = list_str + "|" + ssid;
      }
    }
  }
  if (state == STATE_WIFI_SCAN){
    state = STATE_WIFI_SCAN_COMPLETED;
  }
}

void start_scan(){
  WiFi.scanNetworksAsync(scan_completed, false);
}

void stop_scan(){
  WiFi.scanDelete();
}