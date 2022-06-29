#ifndef EXTERNAL_EEPROM_LIBRARY
#define EXTERNAL_EEPROM_LIBRARY
#include <Arduino.h>
#include <Wire.h>

/* 型式設定用の文字列を定義 */
#define MC_24AA02 0
#define MC_24LC02B 1
#define MC_24FC02 2
#define AT24FC128 3
#define AT24FC256 4

/* floatのビット演算用に共用体を定義 */
union TypeConvert {
  int i;
  long l;
  float f;
  unsigned char c[4];
};

/* クラスの定義 */
class Ext_EEPROM {
 public:
  Ext_EEPROM(int model);
  Ext_EEPROM(int model, int address);
  void begin();
  void write(int num, unsigned char *data);
  void write(int num, int data);
  void write(int num, long data);
  void write(int num, float data);
  void readChar(int num, unsigned char *data);
  int read(int num);
  long readLong(int num);
  float readFloat(int num);

 private:
  uint8_t slave_address;
  uint8_t mem_address_size;

  void setSlaveAddress(int model, int address);
  void WireWriteAddress(int num);
};

#endif