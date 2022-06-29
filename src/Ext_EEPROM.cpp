#include "Ext_EEPROM.h"

/* EEPROMの型式に応じてパラメータを設定 */
Ext_EEPROM::Ext_EEPROM(int model) { Ext_EEPROM::setSlaveAddress(model, 0); }

Ext_EEPROM::Ext_EEPROM(int model, int address) {
  Ext_EEPROM::setSlaveAddress(model, address);
}

void Ext_EEPROM::setSlaveAddress(int model, int address) {
  /* 型式によるプリプロセッサ条件分岐用 */
  if (model == MC_24AA02 || model == MC_24LC02B || model == MC_24FC02) {
    mem_address_size = 1;
    slave_address = (uint8_t)(0b1010000 | address);
  }

  if (model == AT24FC128 || model == AT24FC256) {
    mem_address_size = 2;
    slave_address = (uint8_t)(0b1010000 | address);
  }
}

/* 初期化処理 */
void Ext_EEPROM::begin() {
  /* I2Cの初期化 */
  Wire.begin();
}

void Ext_EEPROM::WireWriteAddress(int num) {
  if (mem_address_size == 1) {
    Wire.write(num * 4);
  } else if (mem_address_size == 2) {
    union TypeConvert add;
    add.l = (long)(num * 4);
    Wire.write(add.c[1]);
    Wire.write(add.c[0]);
  }
}

/* ----------------------------------------------------- */

/* 4byte書き込み(char) */
void Ext_EEPROM::write(int num, unsigned char *data) {
  /* 指定のメモリアドレスに書き込み */
  Wire.beginTransmission(slave_address);
  Ext_EEPROM::WireWriteAddress(num);
  Wire.write(data[0]);
  Wire.write(data[1]);
  Wire.write(data[2]);
  Wire.write(data[3]);
  Wire.endTransmission();

  delay(10);
}

/* 4byte書き込み(int) */
void Ext_EEPROM::write(int num, int data) {
  union TypeConvert val;
  val.l = (long)(data);
  Ext_EEPROM::write(num, val.c);
}

/* 4byte書き込み(long) */
void Ext_EEPROM::write(int num, long data) {
  union TypeConvert val;
  val.l = data;
  Ext_EEPROM::write(num, val.c);
}

/* 4byte書き込み(float) */
void Ext_EEPROM::write(int num, float data) {
  union TypeConvert val;
  val.f = data;
  Ext_EEPROM::write(num, val.c);
}

/* ----------------------------------------------------- */

/* 4byte読み出し(char) */
void Ext_EEPROM::readChar(int num, unsigned char *data) {
  /* 読みだすメモリアドレスを設定 */
  Wire.beginTransmission(slave_address);
  Ext_EEPROM::WireWriteAddress(num);
  Wire.endTransmission();

  /* データを1byteずつ読み出し */
  Wire.requestFrom(slave_address, 4);
  data[0] = Wire.read();
  data[1] = Wire.read();
  data[2] = Wire.read();
  data[3] = Wire.read();
}

/* 4byte読み出し(int) */
int Ext_EEPROM::read(int num) {
  union TypeConvert val;
  Ext_EEPROM::readChar(num, val.c);
  return (int)(val.l);
}

/* 4byte読み出し(long) */
long Ext_EEPROM::readLong(int num) {
  union TypeConvert val;
  Ext_EEPROM::readChar(num, val.c);
  return val.l;
}

/* 4byte読み出し(float) */
float Ext_EEPROM::readFloat(int num) {
  union TypeConvert val;
  Ext_EEPROM::readChar(num, val.c);
  return val.f;
}