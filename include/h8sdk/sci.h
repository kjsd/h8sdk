/**
 * @file sci.h
 *
 * @brief シリアルポートドライバ
 *
 * このモジュールはシリアルポートデバイスSCI3へのインタフェースを提供する
 *
 * @see H83694グループ_ハードウェアマニュアル.pdf 14章
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
#ifndef SCI_H_
#define SCI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

/**
 * @brief 送信バッファサイズ
 */
#define SCI_MAX_TXBUF 128

/**
 * @brief 受信バッファサイズ
 */
#define SCI_MAX_RXBUF 128

/**
 * @brief パリティエラー識別子
 */
#define SCI_ERR_PARITY (1U << 0)

/**
 * @brief フレーミングエラー識別子
 */
#define SCI_ERR_FRAMING (1U << 1)

/**
 * @brief オーバーランエラー識別子
 */
#define SCI_ERR_OVERRUN (1U << 2)


/**
 * @brief SCI初期化
 *
 * SCIを使用可能に設定する。他API使用前に必ず実行しておく。
 * 送受信は割り込みにより駆動される。@n
 * データ長8ビット、パリティなし、ストップビット1、フロー制御なし、
 * ボーレート19200bps
 */
void SCI_init();

/**
 * @brief 送受信実行
 *
 * SCIデバイスへ送受信処理を委託する。割り込みハンドラから呼ばれるのが前提。
 */
void SCI_communicate();

/**
 * @brief 文字列送信
 *
 * 文字列を送信する。文字列はNUL終端されていなければならない。
 * エラーが発生しない限り送信完了までブロックする。
 *
 * @param[in] str 送信文字列の先頭へのポインタ
 *
 * @retval 正の値 送信完了文字数
 * @retval 負の値 送信エラー
 */
_SINT SCI_puts(const _SBYTE *str);

/**
 * @brief バイトストリーム送信
 *
 * 汎用バイトデータを送信予約する。同期/非同期送信の両方に対応。
 * 指定データは内部バッファへ格納され、次回の送信可能時に処理が実行される。
 *
 * @param[in] data 送信データの先頭へのポインタ
 * @param[in] size 送信サイズ
 * @param[in] sync _TRUE: 同期型。size分送信できるか、タイムアウトするまで
 * ブロックする。_FALSE: 非同期型。タイムアウトは無効
 * @param[in] tmo_ms 同期送信時のタイムアウト値。ミリセカンド。
 *
 * @retval 正の値 送信完了サイズ
 * @retval 負の値 送信エラー
 */
_SINT SCI_write(const _UBYTE* data, _UBYTE size, _BOOL sync, _SINT tmo_ms);

/**
 * @brief バイトストリーム受信
 *
 * 内部バッファに溜まっているデータを取得する。同期/非同期受信の両方に対応。
 * 内部バッファには非同期で随時受信データが溜まっていくため、定期的に
 * このAPIを実行しないとバッファが溢れデータロスが発生する。
 *
 * @param[in] buf 受信データを格納するバッファの先頭へのポインタ
 * @param[in] size 受信サイズ
 * @param[in] sync _TRUE: 同期型。size分受信できるか、タイムアウトするまで
 * ブロックする。_FALSE: 非同期型。タイムアウトは無効
 * @param[in] tmo_ms 同期受信時のタイムアウト値。ミリセカンド。
 *
 * @retval 正の値 受信完了サイズ
 * @retval 負の値 受信エラー
 */
_SINT SCI_read(_UBYTE* buf, _UBYTE size, _BOOL sync, _SINT tmo_ms);

/**
 * @brief エラー値取得
 *
 * 最後に発生したエラー番号を取得する。
 *
 * @return エラー番号。SCI_ERR_* で定義されているコード。
 */
_UBYTE SCI_getLastError();

#ifdef __cplusplus
}
#endif

#endif /* SCI_H_ */
