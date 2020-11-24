#include "TSettings.h"

#define DEBUG_PRINT(...) { Serial.print(__VA_ARGS__); }
#define DEBUG_PRINTLN(...) { Serial.println(__VA_ARGS__); }

TSettings::TSettings(){
}

// 0-31 ssid
// 32-95 pass
// 96-101 bssid

// 238 def_settings 0/1
// 239 CRC8
void TSettings::WriteROM(){
    ClearROM();
    for(uint8_t i=0;i<ssid.length();i++){
        ROM[0+i] = ssid[i];
        if (i==31){
            break;
        }
    }
    for(uint8_t i=0;i<pass.length();i++){
        ROM[32+i] = pass[i];
        if (i==63){
            break;
        }
    }
    for(uint8_t i=0;i<6;i++){
        ROM[96+i] = bssid[i];
    }
    if (def_settings){
        ROM[238] = 1;
    }
    ROM[239] = GetROMCRC();
}

void TSettings::ReadROM(){
    ssid = "";
    pass = "";
    for(uint8_t i=0;i<32;i++){
        if (ROM[0+i]==0){
            break;
        }
        ssid += char(ROM[0+i]);
    }
    for(uint8_t i=0;i<63;i++){
        if (ROM[32+i]==0){
            break;
        }
        pass += char(ROM[32+i]);
    }
    for(uint8_t i=0;i<6;i++){
        bssid[i] = ROM[96+i];
    }
    if (ROM[238]==1){
        def_settings = true;
    }
}

bool TSettings::CRCCorrect(){
    return ROM[239]==GetROMCRC();
}

void TSettings::ClearROM(){
    for (uint8_t i=0;i<240;i++){
        ROM[i] = 0;
    }
}

void TSettings::SetDefault(){
    ssid = "";
    pass = "";
    bssid[0] = 0;
    bssid[1] = 0;
    bssid[2] = 0;
    bssid[3] = 0;
    bssid[4] = 0;
    bssid[5] = 0;
    def_settings = true;
    WriteROM();
}

byte TSettings::GetROMCRC(){
    return CRC8(&ROM[0], 239);
}

uint8_t TSettings::CRC8(const byte *data, byte len) {
  byte crc = 0x00;
  while (len--) {
    byte extract = *data++;
    DEBUG_PRINT(extract);
    DEBUG_PRINT(" ");
    //DEBUG_PRINT(" ");
    for (byte tempI = 8; tempI; tempI--) {
      byte sum = (crc ^ extract) & 0x01;
      crc >>= 1;
      if (sum) {
        crc ^= 0x8C;
      }
      extract >>= 1;
    }
  }
  DEBUG_PRINTLN("");
  DEBUG_PRINTLN(crc);
  return crc;
}