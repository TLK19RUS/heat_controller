#include "main.h"

String get_status_name(uint8_t status){
    String ret = "";
    switch (status) {
    case WL_CONNECTED:
        ret = "WL_CONNECTED";
        break;
    case WL_IDLE_STATUS:
        ret = "WL_IDLE_STATUS";
        break;
    case WL_NO_SSID_AVAIL:
        ret = "WL_NO_SSID_AVAIL";
        break;
    case WL_SCAN_COMPLETED:
        ret = "WL_SCAN_COMPLETED";
        break;    
    case WL_CONNECT_FAILED:
        ret = "WL_CONNECT_FAILED";
        break; 
    case WL_CONNECTION_LOST:
        ret = "WL_CONNECTION_LOST";
        break; 
    case WL_DISCONNECTED:
        ret = "WL_DISCONNECTED";
        break; 
    }
    return ret;
}

void restart(){
    ESP.restart();
}