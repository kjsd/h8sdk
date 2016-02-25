/**
 * @file assert.h
 *
 * @brief アサート
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
#ifndef _ASSERT_H_
#define _ASSERT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"
#include "stdlib.h"
#include "led.h"

#if defined(NDEBUG)
#define _assert(x)
#else
/**
 * @brief アサート
 *
 * 実装ミス以外ではありえないバグをチェックするための実行時エラーチェッ
 * カ。デバッグ専用。リリースバイナリからは外される。
 *
 * @param[in] x 評価するパラメータ。これが偽になると処理を緊急停止して
 * LED点滅で状態異常を知らせる。
 */
#define _assert(x)                              \
    if (!(x))                                   \
    {                                           \
        LED_INIT;                               \
        while (_TRUE)                           \
        {                                       \
            LED_ON(LED_D5);                     \
            LED_OFF(LED_D6);                    \
            _msleep(500);                       \
            LED_OFF(LED_D5);                    \
            LED_ON(LED_D6);                     \
            _msleep(500);                       \
        }                                       \
    }
#endif /* NDEBUG */

#ifdef __cplusplus
}
#endif

#endif /* _ASSERT_H_ */
