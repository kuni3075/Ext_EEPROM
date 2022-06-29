# External EEPROM Library

外部 EEPROM を使用するための Arduino ライブラリです。\
当方で動作確認が出来たものを順次追加していきます。

## 対応している EEPROM

| メーカー | 型式 | メモリサイズ | 通信方法 | ライブラリの引数 |
| --------------- | ---------- | ------------ | --- | ---------- |
| Microchip			| 24AA02	| 256 x 8 bit	| I2C | MC_24AA02	|
| Microchip			| 24LC02B	| 256 x 8 bit	| I2C | MC_24LC02B	|
| Microchip			| 24FC02	| 256 x 8 bit	| I2C | MC_24FC02	|
| Microchip/Atmel	| AT24FC128	| 16k x 8 bit	| I2C | AT24FC128	|
| Microchip/Atmel	| AT24FC256	| 32k x 8 bit	| I2C | AT24FC256	| 


## 使用方法

### ライブラリ内のデータ構造
汎用性を高めるために、メモリアドレスではなく保存番号でデータを管理しています。\
番号1つにつき4バイトを割り当てており、int、long、floatを保存できるように構築しています。\
例えばメモリサイズが256x8bitの場合、0番～511番の合計512個のデータを管理できます。\
\
※メモリアドレスが1byteか2byteかは部品型式で判断しており、ライブラリ内で自動的に処理しています。

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
基本的に1 秒ごとにデータを読み込み、インクリメントして改めて保存するプログラムです。\
マイコンに書き込む前に「インスタンス生成」でどれか1つのコメントアウトを外してください。\
## インスタンス生成の引数
部品ごとの処理の違いを判別するために、EEPROM一覧の引数を代入してください。\
スレーブアドレスが変更可能な型式では、第2引数により対応できます。\
何のことかわからない方は、ICのA1、A2、A3をGNDに接続した上で、数字を省略して型式のみ代入するか、0を代入してください。\
※詳細はいつか追記します。
<table border="1">
	<tbody>
		<tr>
			<td>X</td>
			<td>X</td>
			<td>X</td>
			<td>X</td>
			<td>A1</td>
			<td>A2</td>
			<td>A3</td>
			<td>R/W</td>
		</tr>
	</tbody>
</table>
<table border="1">
	<tbody>
		<tr>
			<td>A1</td>
			<td>A2</td>
			<td>A3</td>
			<td>パラメータ</td>
		</tr>
		<tr>
			<td>0</td>
			<td>0</td>
			<td>0</td>
			<td>0</td>
		</tr>
		<tr>
			<td>0</td>
			<td>0</td>
			<td>1</td>
			<td>1</td>
		</tr>
		<tr>
			<td>0</td>
			<td>1</td>
			<td>0</td>
			<td>2</td>
		</tr>
		<tr>
			<td>0</td>
			<td>1</td>
			<td>1</td>
			<td>3</td>
		</tr>
		<tr>
			<td>1</td>
			<td>0</td>
			<td>0</td>
			<td>4</td>
		</tr>
		<tr>
			<td>1</td>
			<td>0</td>
			<td>1</td>
			<td>5</td>
		</tr>
		<tr>
			<td>1</td>
			<td>1</td>
			<td>0</td>
			<td>6</td>
		</tr>
		<tr>
			<td>1</td>
			<td>1</td>
			<td>1</td>
			<td>7</td>
		</tr>
	</tbody>
</table>