/**
 * @file adc.h
 *
 * @brief A/Dコンバータドライバ
 *
 * このモジュールはA/Dコンバータへのインタフェースを提供する。@n
 * 初期化、使用チャネルの設定を行うことで変換データを取得できるように
 * なる。
 *
 * @see H83694グループ_ハードウェアマニュアル.pdf 16章
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
#ifndef _ADC_H_
#define _ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"


/**
 * @brief 設定モード識別子
 */
typedef enum
{
    ADC_NORMAL = 0,
    /**< ノーマルモード */
    ADC_SCAN,
    /**< スキャンモード */
    ADC_NUM_OF_MODE
    /**< モード数 */
} ADC_Mode;

/**
 * @brief チャネル識別子
 */
typedef enum
{
    ADC_AN0 = 0,
    /**< チャネルポートAN0 */
    ADC_AN1,
    /**< チャネルポートAN1 */
    ADC_AN2,
    /**< チャネルポートAN2 */
    ADC_AN3,
    /**< チャネルポートAN3 */
    ADC_NUM_OF_CHANNEL
    /**< チャネルポート数 */
} ADC_Channel;

/**
 * @brief A/Dコンバータ初期化
 *
 * A/Dコンバータ初期化。他API使用前に必ず実行する。
 *
 * @param[in] mode 使用するモードの種類
 * @param[in] interrupt _TRUE：割り込みを使う。@n
 * _FALSE：割り込みを使わない。
 *
 * @note 割り込みハンドラは外部で定義する。
 */
void ADC_init(ADC_Mode mode, _BOOL interrupt);

/**
 * @brief チャネル有効化
 *
 * 使用するチャネルを設定する。ノーマルモード時は指定チャネルのみ。ス
 * キャンモード時は指定チャネルより若い番号のチャネルは全て使用可能に
 * セットされる。例えば、ADC_AN2 を与えた場合 AN0～AN2のチャネルが有効
 * になる。
 *
 * @param[in] ch 有効にするチャネル
 *
 * @see ADC_disable
 */
void ADC_enable(ADC_Channel ch);

/**
 * @brief チャネル無効化
 *
 * 使用停止するチャネルを設定する。ノーマルモード時は指定チャネルのみ。
 * 指定チャネルより若い番号のチャネルは全て使用不可にセットされる。例
 * えば、ADC_AN2 を与えた場合 AN0～AN2のチャネルが無効になる。
 *
 * @param[in] ch 無効にするチャネル
 *
 * @see ADC_enable
 */
void ADC_disable(ADC_Channel ch);

/**
 * @brief A/D変換開始
 *
 * A/D変換が開始される。スキャンモード時は変換データが随時取得できるよ
 * うになる。ノーマルモード時は一回のみ。
 *
 * @see ADC_stop
 */
void ADC_start();

/**
 * @brief A/D変換停止
 *
 * A/D変換が停止される。以降変換データは取得できない。
 *
 * @see ADC_start
 */
void ADC_stop();

/**
 * @brief A/D変換データを取得する
 *
 * A/D変換データを取得する。読み込むチャネルが全て完了したときは必ず引
 * 数lastに_TRUEをセットして実行する。
 *
 * @param[in] anx データを取得するチャネル
 * @param[in] last この取得で今回の変換データを全チャネルで破棄するかどうか
 *
 * @retval 正の値 変換完了データ。有効値は10bit
 * @retval -1 変換処理が未完
 */
_SDWORD ADC_get(ADC_Channel anx, _BOOL last);

#ifdef __cplusplus
}
#endif

#endif /* _ADC_H_ */
