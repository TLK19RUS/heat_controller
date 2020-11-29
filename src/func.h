#ifndef __FUNC_H__
#define __FUNC_H__

String get_status_name(uint8_t status);
void restart();
String lpad(int value, uint8_t pad_len, char pad_char);

#endif