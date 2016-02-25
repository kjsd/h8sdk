/**
 * @file lcd.h
 *
 * @brief LCDドライバ
 *
 * このモジュールはLCDデバイスSC1602BSへのインタフェースを提供する。
 *
 * @htmlonly
 * @version $Id:$
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 * @endhtmlonly
 *
 ***********************************************************************/
#ifndef LCD_H_
#define LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

/**
 * @brief LCD表示部の列数
 */
#define LCD_MAX_COLS 16

/**
 * @brief LCD表示部の行数
 */
#define LCD_MAX_ROWS 2

/**
 * @brief キャラクタ横ドット数
 */
#define LCD_CG_COLS 5

/**
 * @brief キャラクタ縦ドット数
 */
#define LCD_CG_ROWS 8

/**
 * @brief 登録可能な最大キャラクタ数
 */
#define LCD_CG_MAXCHAR 8


/**
 * @brief LCDデバイス初期化
 *
 * デバイスを使用可能にする。全てのAPIの前にこれを実行しておく。初期設
 * 定値は、@n
 * @li キャラクタ長8ビット
 * @li 表示2桁
 * @li キャラクタサイズ5x10ドット
 * @li カーソルOFF、ブリンクOFF
 * @li カーソルインクリメントあり、表示シフトなし
 */
void LCD_init();

/**
 * @brief 文字列出力
 *
 * 文字列をLCDに出力する。文字列はNUL終端されていなければならない。
 * 特殊文字は '\\n' のみ。改行文字と解釈される。
 *
 * @param[in] str 文字配列の先頭へのポインタ
 *
 * @return 出力された文字数
 *
 * @note 出力カーソルは表示部の領域をループする。
 */
_SINT LCD_puts(const _SBYTE *str);

/**
 * @brief バイトストリーム書き込み
 *
 * 汎用データ出力。カーソル現在位置から指定サイズ分のバイトデータをLCD
 * に出力する。
 *
 * @param[in] data データの先頭へのポインタ
 * @param[in] size 出力サイズ
 *
 * @return 出力されたバイト数
 *
 * @note カーソルは表示部の領域をループする。
 */
_SINT LCD_write(const _UBYTE *data, _SINT size);

/**
 * @brief バイトストリーム読み出し
 *
 * 汎用データ入力。カーソル現在位置から指定バイト読み出す。
 *
 * @param[in] buf データを格納する領域の先頭へのポインタ
 * @param[in] size 読み出しサイズ
 *
 * @return 読み出されたバイト数
 *
 * @note カーソルは表示部の領域をループする。
 */
_SINT LCD_read(_UBYTE* buf, _SINT size);

/**
 * @brief カーソル位置取得
 *
 * 現在の出力位置を取得する。引数の位置指定は絶対値の 0 origin。原点は
 * 左上隅、右下方向がプラスの領域。
 *
 * @param[in] x 列方向の位置を格納するポインタ
 * @param[in] y 行方向の位置を格納するポインタ
 */
void LCD_getCursor(_SINT* x, _SINT* y);

/**
 * @brief カーソル移動
 *
 * 出力位置を移動させる。表示部の範囲でのみ移動可能。引数の位置指定は
 * 絶対値の 0 origin。原点は左上隅、右下方向がプラスの領域。範囲を越え
 * た値指定は無視される。
 *
 * @param[in] x 列方向の位置を指定する
 * @param[in] y 行方向の位置を指定する
 */
void LCD_setCursor(_SINT x, _SINT y);

/**
 * @brief 改行出力
 *
 * 出力カーソルを一行下の最左列へ移動させる。
 * 
 * @note 出力カーソルは表示部の領域をループする。
 */
void LCD_crlf();

/**
 * @brief 領域クリア
 *
 * LCDバッファの内容をクリアする
 */
void LCD_cls();

/**
 * @brief キャラクタ登録
 *
 * ユーザー作成キャラクタデータを新規にLCDデバイスへ登録する。 同一ア
 * ドレスで登録済みのキャラクタは上書きされる。
 *
 * @param[in] no 登録アドレス。0～LCD_CG_MAXCHAR-1 までを指定する
 * @param[in] data 登録キャラクタ配列先頭へのポインタ。LCD_CG_ROWSバイ
 * トの配列をLCD_CG_COLS x LCD_CG_ROWSのビットパターン行列とみなしたデー
 * タ列を指定する。
 */
void LCD_setChar(_UBYTE no, const _UBYTE *data);

/**
 * @brief 表示モード変更
 *
 * カーソル、点滅などの表示モードを変更する。初期状態は、表示は_TRUE、
 * カーソル、点滅は_FALSE。
 *
 * @param[in] all 全表示のオン/オフ指定
 * @param[in] cur カーソルのオン/オフ指定
 * @param[in] blink カーソル位置のブリンクオン/オフ指定
 */
void LCD_setVisual(_BOOL all, _BOOL cur, _BOOL blink);

#ifdef __cplusplus
}
#endif

#endif /* LCD_H_ */
