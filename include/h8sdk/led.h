/**
 * @file led.h
 *
 * @brief LEDドライバ
 *
 * このモジュールはLEDデバイスへのインタフェースを提供する。
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
#ifndef LED_H_
#define LED_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"
#include "3694s.h"
#include "ioctl.h"

/**
 * @brief LEDタイプ識別子
 */
typedef enum
{
    LED_D5 = 0,
    /**< D5番ポートのLED */
    LED_D6,
    /**< D6番ポートのLED */

    LED_NUM_OF_TYPE
    /**< LEDタイプの数 */
} LED_Type;

/**
 * @brief LEDが接続されているGPIOレジスタのベース値
 */
#define LED_BASE (1U << 1)

/**
 * @brief LED初期化
 *
 * LEDデバイスを使用可能に設定する。全てのAPIの前にこれを実行しておく。
 */
#define LED_INIT                                                      \
    do                                                                \
    {                                                                 \
        IOCTL_set(IOCTL_REG_PCR8, 0x06, 0x06);                        \
        _IO.PDR8.BYTE |= (LED_BASE << LED_D5 | LED_BASE << LED_D6);   \
    }                                                                 \
    while (_FALSE)

/**
 * @brief LED点灯
 *
 * LEDをひとつ点灯させる。
 *
 * @param[in] t 点灯させるLEDの種類。LED_Type
 */
#define LED_ON(t) (_IO.PDR8.BYTE &= ~(LED_BASE << (t)))

/**
 * @brief LED消灯
 *
 * LEDをひとつ消灯させる。
 *
 * @param[in] t 消灯させるLEDの種類。LED_Type
 */
#define LED_OFF(t) (_IO.PDR8.BYTE |= LED_BASE << (t))

/**
 * @brief LED表示反転
 *
 * 指定されたLEDの表示を現在のものと反転させる。
 *
 * @param[in] t 反転させるLEDの種類。LED_Type
 */
#define LED_TURN(t) (_IO.PDR8.BYTE ^= LED_BASE << (t))


#ifdef __cplusplus
}
#endif

#endif /* LED_H_ */
