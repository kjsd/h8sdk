/**
 * @file ifstub.h
 *
 * @brief 通信インタフェーススタブ
 *
 * このモジュールは他基板と通信するときのインタフェースのみを定義した
 * スタブである。
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
#ifndef IFSTUB_H_
#define IFSTUB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"


/** インタフェースタイプ型定義 */
typedef enum
{
    IFSTUB_SCI = 0,
    /**< シルアルポート */
#ifdef USE_LOOPBACK_SSRP
    IFSTUB_SSRP_SKELETON,
    /**< SSRP単体動作ドライバ */
#endif /* USE_LOOPBACK_SSRP */

    IFSTUB_NUM_OF_TYPE
} IFSTUB_Type;

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
typedef _SINT (*IFSTUB_WriteStream)(const _UBYTE* data, _UBYTE size,
                                    _BOOL sync, _SINT tmo_ms);

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
typedef _SINT (*IFSTUB_ReadStream)(_UBYTE* buf, _UBYTE size,
                                   _BOOL sync, _SINT tmo_ms);

/** スタブ本体型 */
typedef struct
{
    IFSTUB_WriteStream write;
    /**< 出力メソッド */
    IFSTUB_ReadStream read;
    /**< 入力メソッド */
} IFSTUB_Class;


const IFSTUB_Class* IFSTUB_getInstance(IFSTUB_Type t);

#ifdef __cplusplus
}
#endif

#endif /* IFSTUB_H_ */
