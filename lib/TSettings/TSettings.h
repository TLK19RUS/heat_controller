#ifndef _TSETTINGS_H
#define _TSETTINGS_H

#include <Arduino.h>


class TSettings{
    public:
    String ssid = "";
    String pass = "";
    uint8_t bssid[6] = {0,0,0,0,0,0};
    uint8_t ROM[240];
    bool def_settings = false;
    TSettings();
    void WriteROM();
    void ReadROM();
    bool CRCCorrect();
    void SetDefault();
    private:
    void ClearROM();
    byte GetROMCRC();
    byte CRC8(const byte *data, byte len);
};

#endif