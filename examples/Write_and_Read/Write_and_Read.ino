#include "Ext_EEPROM.h"

/* データごとの保存番号を設定 */
const uint8_t num_int = 0;
const uint8_t num_long = 1;
const uint8_t num_float = 2;

/* インスタンス生成 */
Ext_EEPROM eeprom = Ext_EEPROM(MC_24FC02);

void setup() {
  Serial.begin(9600);
  /* 初期設定 */
  eeprom.begin();

  /* 初期値をEEPROMに書き込み */
  eeprom.write(num_int, (int)0);
  eeprom.write(num_long, (long)0);
  eeprom.write(num_float, (float)0.0);
}

void loop() {
  /* 変数定義 */
  int data_int;
  long data_long;
  float data_float;

  /* EEPROMからデータ読み出し */
  data_int = eeprom.read(num_int);
  data_long = eeprom.readLong(num_long);
  data_float = eeprom.readFloat(num_float);

  /* 読み出した結果を出力 */
  Serial.print("int:");
  Serial.print(data_int);
  Serial.print(", ");
  Serial.print("long:");
  Serial.print(data_long);
  Serial.print(", ");
  Serial.print("float:");
  Serial.println(data_float);

  /* 各データの値を変更 */
  data_int += 1;
  data_long += 1000;
  data_float += 0.1;

  /* EEPROMに変更したデータを書き込み */
  eeprom.write(num_int, data_int);
  eeprom.write(num_long, data_long);
  eeprom.write(num_float, data_float);

  delay(1000);
}