//#include "WIFI.h"
//#include <ESP8266WiFi.h>
#include "main.h"
//#include "LCD.h"
//#include "StackList.h"

/* extern app_states state;
extern app_states prev_state;
extern String list_str;
extern uint8_t list_cursor_pos;
extern uint8_t list_shift;
extern uint8_t list_cnt; */

//////////////
extern uint8_t debug_cnt;
//////////////


void Init_wifi(){
  if (WiFi.getPersistent() == true){
    WiFi.persistent(false);
  }
  if (WiFi.getAutoConnect() == true)  
  {
    WiFi.setAutoConnect(false);
  }
  if (WiFi.getAutoReconnect() != true){
    WiFi.setAutoReconnect(true);
  }
  if ((main_set.ssid != "") && (main_set.CRCCorrect())){
    WiFi.begin(main_set.ssid, main_set.pass, 0, main_set.bssid, true);
  }
  //WiFi.reconnect();
}

void scan_completed(int scan_result){
  if (scan_result>0){
    //debug_cnt = scan_result;
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
      ssid +=  "\t" + String(net_rssi[i]);
      if (i==0){
        list_str = ssid;
      }else{
        list_str = list_str + "|" + ssid;
      }
    }
    list_cnt = scan_result;
  }
  if (states.peek() == WIFI_SCAN){
    list_cursor_pos=1;
    list_shift=0;
    states.pop();
    states.push(WIFI_SCAN_COMPLETED);
  }
}

void start_scan(){
  WiFi.scanNetworksAsync(scan_completed, false);
}

void stop_scan(){
  WiFi.scanDelete();
}

void connect_to_selected_wifi(){
  states.pop();
  states.push(WIFI_CONNECT);
  
  show_input();
  //debug_cnt = get_cursor_pos_in_list();
}


void wifi_begin(){
  uint8_t wid = get_value_from_selected_item();
  DEBUG_PRINTLN(WiFi.SSID(wid));
  DEBUG_PRINTLN(WiFi.BSSIDstr(wid));
  DEBUG_PRINTLN(input_str);
  main_set.ssid = WiFi.SSID(wid);
  main_set.pass = input_str;
  main_set.bssid[0] = WiFi.BSSID(wid)[0];
  main_set.bssid[1] = WiFi.BSSID(wid)[1];
  main_set.bssid[2] = WiFi.BSSID(wid)[2];
  main_set.bssid[3] = WiFi.BSSID(wid)[3];
  main_set.bssid[4] = WiFi.BSSID(wid)[4];
  main_set.bssid[5] = WiFi.BSSID(wid)[5];
  SaveToRTC();
  WiFi.begin(WiFi.SSID(wid), input_str, 0, WiFi.BSSID(wid), true);
  
  states.pop();
}