/**
 * @file ps2.h
 *
 * @brief PS/2ドライバ
 *
 * このモジュールはPS/2ポートへのインタフェースを提供する。
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
#ifndef PS2_H_
#define PS2_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

#define PS2_MAX_RXBUF 8

typedef enum
{
    PS2_ERR_OK = 0,
    PS2_ERR_FRAMING,
    PS2_ERR_PARITY,

    PS2_NUM_OF_ERR
} PS2_Status;

/**
 * @brief PS2ポート初期化
 *
 * デバイスを使用可能にする。全てのAPIの前にこれを実行しておく。
 */
void PS2_init();

/**
 * @brief 送受信実行
 *
 * PS/2デバイスへ送受信処理を委託する。割り込みハンドラから呼ばれるの
 * が前提。
 */
void PS2_communicate();

/**
 * @brief バイトストリーム受信
 *
 * 内部バッファに溜まっているデータを取得する。同期/非同期受信の両方に
 * 対応。内部バッファには非同期で随時受信データが溜まっていくため、定
 * 期的にこのAPIを実行しないとバッファが溢れデータロスが発生する。
 *
 * @param[in] buf 受信データを格納するバッファの先頭へのポインタ
 * @param[in] size 受信サイズ
 * @param[in] sync _TRUE: 同期型。size分受信できるか、タイムアウトする
 * までブロックする。@n
 * _FALSE: 非同期型。タイムアウトは無効
 * @param[in] tmo_ms 同期受信時のタイムアウト値。ミリセカンド。
 *
 * @retval 正の値 受信完了サイズ
 * @retval 負の値 受信エラー
 */
_SINT PS2_read(_UBYTE* buf, _UBYTE size, _BOOL sync, _SINT tmo_ms);


#ifdef __cplusplus
}
#endif

#endif /* PS2_H_ */
