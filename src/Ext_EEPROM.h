#ifndef EXTERNAL_EEPROM_LIBRARY
#define EXTERNAL_EEPROM_LIBRARY
#include <Arduino.h>
#include <Wire.h>

/* 型式設定用の文字列を定義 */
#define MC_24AA02 0
#define MC_24LC02B 1
#define MC_24FC02 2

/* floatのビット演算用に共用体を定義 */
union TypeConvert {
  long l;
  float f;
  unsigned char c[4];
};

/* クラスの定義 */
class Ext_EEPROM {
 public:
  Ext_EEPROM(int model);
  void begin();
  void put(uint8_t address, uint8_t data);
  uint8_t get(uint8_t address);
  void write(uint8_t num, unsigned char *data);
  void write(uint8_t num, int data);
  void write(uint8_t num, long data);
  void write(uint8_t num, float data);
  void readChar(uint8_t num, unsigned char *data);
  int read(uint8_t num);
  long readLong(uint8_t num);
  float readFloat(uint8_t num);

 private:
  uint8_t slave_address;
};

#endif