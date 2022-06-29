#include "Ext_EEPROM.h"

/* EEPROMの型式に応じてパラメータを設定 */
Ext_EEPROM::Ext_EEPROM(int model) {
  /* 型式によるプリプロセッサ条件分岐用 */
  if (model == MC_24AA02) {
#define MC_24AA02_PROG
  } else if (model == MC_24LC02B) {
#define MC_24LC02B_PROG
  } else if (model == MC_24FC02) {
#define MC_24FC02_PROG
  }

/* I2Cのスレーブアドレスを設定 */
#ifdef MC_24AA02_PROG || MC_24LC02B_PROG || MC_24FC02_PROG
  slave_address = (uint8_t)0b1010000;
#endif
}

/* 初期化処理 */
void Ext_EEPROM::begin() {
  /* I2Cの初期化 */
  Wire.begin();
}

/* ----------------------------------------------------- */

/* 1byte書き込み */
void Ext_EEPROM::put(uint8_t address, uint8_t data) {
  /* 指定のメモリアドレスに書き込み */
  Wire.beginTransmission(slave_address);
  Wire.write(address);
  Wire.write(data);
  Wire.endTransmission();

  delay(10);
}

/* 1byte読み出し */
uint8_t Ext_EEPROM::get(uint8_t address) {
  uint8_t data = 0;

  /* 読みだすメモリアドレスを設定 */
  Wire.beginTransmission(slave_address);
  Wire.write(address);
  Wire.endTransmission();

  /* データの読み出し */
  Wire.requestFrom(slave_address, 1);
  data = Wire.read();
  return data;
}

/* ----------------------------------------------------- */

/* 4byte書き込み(char) */
void Ext_EEPROM::write(uint8_t num, unsigned char *data) {
  /* 指定のメモリアドレスに書き込み */
  Wire.beginTransmission(slave_address);
  Wire.write(num * 4);
  Wire.write(data[0]);
  Wire.write(data[1]);
  Wire.write(data[2]);
  Wire.write(data[3]);
  Wire.endTransmission();

  delay(10);
}

/* 4byte書き込み(int) */
void Ext_EEPROM::write(uint8_t num, int data) {
  union TypeConvert val;
  val.l = (long)(data);
  Ext_EEPROM::write(num, val.c);
}

/* 4byte書き込み(long) */
void Ext_EEPROM::write(uint8_t num, long data) {
  union TypeConvert val;
  val.l = data;
  Ext_EEPROM::write(num, val.c);
}

/* 4byte書き込み(float) */
void Ext_EEPROM::write(uint8_t num, float data) {
  union TypeConvert val;
  val.f = data;
  Ext_EEPROM::write(num, val.c);
}

/* ----------------------------------------------------- */

/* 4byte読み出し(char) */
void Ext_EEPROM::readChar(uint8_t num, unsigned char *data) {
  /* 読みだすメモリアドレスを設定 */
  Wire.beginTransmission(slave_address);
  Wire.write(num * 4);
  Wire.endTransmission();

  /* データを1byteずつ読み出し */
  Wire.requestFrom(slave_address, 4);
  data[0] = Wire.read();
  data[1] = Wire.read();
  data[2] = Wire.read();
  data[3] = Wire.read();
}

/* 4byte読み出し(int) */
int Ext_EEPROM::read(uint8_t num) {
  union TypeConvert val;
  Ext_EEPROM::readChar(num, val.c);
  return (int)(val.l);
}

/* 4byte読み出し(long) */
long Ext_EEPROM::readLong(uint8_t num) {
  union TypeConvert val;
  Ext_EEPROM::readChar(num, val.c);
  return val.l;
}

/* 4byte読み出し(float) */
float Ext_EEPROM::readFloat(uint8_t num) {
  union TypeConvert val;
  Ext_EEPROM::readChar(num, val.c);
  return val.f;
}