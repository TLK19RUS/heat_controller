#include "WIFI.h"
#include <ESP8266WiFi.h>

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