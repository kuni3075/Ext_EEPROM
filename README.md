# External EEPROM Library

外部 EEPROM を使用するための Arduino ライブラリです。
当方で動作確認が出来たものを順次追加していきます。

## 対応している EEPROM

| メーカー  | 型式    | メモリサイズ | 通信方法 | ライブラリの引数 |
| --------- | ------- | ------------ | -------- | ---------------- |
| Microchip | 24AA02  | 256 x 8 bit  | I2C      | MC_24AA02        |
| Microchip | 24LC02B | 256 x 8 bit  | I2C      | MC_24LC02B       |
| Microchip | 24FC02  | 256 x 8 bit  | I2C      | MC_24FC02        |

## 使用方法

### ライブラリ内のデータ構造
汎用性を高めるために、メモリアドレスではなく保存番号でデータを管理しています。
番号1つにつき4バイトを割り当てており、int、long、floatを保存できるように構築しています。
例えばメモリサイズが256x8bitの場合、0番～511番の合計512個のデータを管理できます。

<table border="1">
	<tbody>
		<tr>
			<td>保存番号</td>
			<td colspan="4">0</td>
			<td colspan="4">1</td>
			<td colspan="4">2</td>
            <td>～</td>
		</tr>
		<tr>
			<td>メモリアドレス</td>
			<td>0</td>
			<td>1</td>
			<td>2</td>
			<td>3</td>
			<td>4</td>
			<td>5</td>
			<td>6</td>
			<td>7</td>
			<td>8</td>
			<td>9</td>
			<td>10</td>
			<td>11</td>
            <td>～</td>
		</tr>
	</tbody>
</table>

### サンプルコード

1 秒ごとにデータを読み込み、インクリメントして改めて保存するプログラムです。

```c++
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
```
