/**
 * @file push_switch.h
 *
 * @brief プッシュスイッチドライバ
 *
 * このモジュールはプッシュスイッチへのインタフェースを提供する。
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
#ifndef PSW_H_
#define PSW_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

/**
 * @brief 押下状態判定用のカウンタ
 *
 * 一度判定されたらこの値分カウントされるまで押下状態の判定は行わない
 */
#define PSW_BORDER 0x800

/**
 * @brief スイッチタイプ識別子
 */
typedef enum
{
    PSW_SW1 = 0,
    /**< S1番ポートのスイッチ */
    PSW_SW2,
    /**< S2番ポートのスイッチ */

    PSW_NUM_OF_TYPE
    /**< スイッチの数 */
} PSW_Type;

/**
 * @brief スイッチデバイス初期化。
 *
 * スイッチデバイスを使用可能に設定する。他API使用前に必ず実行する。
 *
 * @param[in] interrupt
 * _TRUE：割り込みを使う。@n
 * _FALSE：割り込みを使わない。
 *
 * @note 割り込みハンドラは外部で定義する。
 */
void PSW_init(_BOOL interrupt);

/**
 * @brief スイッチ押下状態の取得
 *
 * スイッチの押下状態を得る。一度押下と判定された場合、PSW_BORDERカウ
 * ント分呼び出されるまで次の状態判定は行われない。なので、定期的に一
 * 定回数このAPIを実行することで正確な状態を連続的に取得できるようにな
 * る。ポーリング用。
 *
 * @param[in] t 取得するスイッチのタイプ
 *
 * @retval _TRUE 押されている
 * @retval _FALSE 押されていない
 *
 * @note 割り込みを使用する場合はこのAPIを使う必要はない
 */
_BOOL PSW_get(PSW_Type t);

/**
 * @brief スイッチ押下状態を一度だけ取得
 *
 * スイッチの押下状態を得る。一度押下と判定されたらスイッチがオフにな
 * るまで押下判定は行われない
 *
 * @param[in] t 取得するスイッチのタイプ
 *
 * @retval _TRUE 押されている
 * @retval _FALSE 押されていない
 *
 * @note 割り込みを使用する場合はこのAPIを使う必要はない
 */
_BOOL PSW_oneShot(PSW_Type t);

/**
 * @brief スイッチ押下状態スナップショットの取得
 *
 * スイッチの押下状態を得る。取得されるのはその瞬間の状態。
 *
 * @param[in] t 取得するスイッチのタイプ
 *
 * @retval _TRUE 押されている
 * @retval _FALSE 押されていない
 *
 * @note 割り込みを使用する場合はこのAPIを使う必要はない
 */
_BOOL PSW_snapShot(PSW_Type t);

#ifdef __cplusplus
}
#endif

#endif /* PSW_H_ */
