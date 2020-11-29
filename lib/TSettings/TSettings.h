#ifndef _TSETTINGS_H
#define _TSETTINGS_H

#include <Arduino.h>


class TSettings{
    public:
    String ssid = "";
    String pass = "";
    uint8_t bssid[6] = {0,0,0,0,0,0};
    sint8_t timeZone;
    uint8_t ROM[235];
    bool def_settings = false;
    TSettings();
    void WriteROM();
    void ReadROM();
    bool CRCCorrect();
    void SetDefault();
    long GetTimeZoneOffset(){
        return timeZone * 3600;
    }
    private:
    void ClearROM();
    byte GetROMCRC();
    byte CRC8(const byte *data, byte len);
    
};

#endif