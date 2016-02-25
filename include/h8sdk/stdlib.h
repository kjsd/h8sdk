/**
 * @file stdlib.h
 *
 * @brief ユーティリティライブラリ
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
#ifndef _STDLIB_H_
#define _STDLIB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

/**
 * @brief NULLポインタ識別子
 *
 * 無効なポインタを表すリテラル
 *
 * @note このリテラルのみH8SDK命名規則の例外とする
 */
#define NULL ((void*)0)

/**
 * @brief マイクロ秒スリープ
 *
 * スリープ関数。ただのビジーループのため精度は環境によって大きく変化する
 *
 * @param[in] us スリープする時間。マイクロ秒
 */
#define _usleep(us)                             \
    do                                          \
    {                                           \
        _UWORD i;                               \
        const _UWORD border = (us) * 3;         \
        for (i = 0; i < border; i++);           \
    }                                           \
    while (_FALSE)

/**
 * @brief ミリ秒スリープ
 *
 * スリープ関数。ただのビジーループのため精度は環境によって大きく変化する
 *
 * @param[in] ms ウェイトする時間。ミリ秒
 */
#define _msleep(ms)                             \
    do                                          \
    {                                           \
        _UWORD i;                               \
        const _UWORD border = (ms);             \
        for (i = 0; i < border; i++)            \
        {                                       \
            _usleep(1000);                      \
        }                                       \
    }                                           \
    while (_FALSE)

/**
 * @brief リングバッファの次のインデックスを取得
 *
 * @param[in] now 現在のインデックス値
 * @param[in] last 最後のインデックス値
 *
 * @return 次のインデックス値
 */
#define _next_ring(now, last) ((now) == (last) ? 0: (now) + 1)
/**
 * @brief リングバッファの前のインデックスを取得
 *
 * @param[in] now 現在のインデックス値
 * @param[in] last 最後のインデックス値
 *
 * @return 前のインデックス値
 */
#define _prev_ring(now, last) ((now) == 0 ? (last): (now) - 1)

/**
 * @brief ハッシュ関数
 *
 * @param[in] x ハッシュ計算対象
 * @param[in] size ハッシュテーブルのサイズ 
 *
 * @return xのハッシュ値
 */
#define _hash(x, size) ((x) % (size))

/**
 * @brief チェックサム計算
 *
 * 16ビット単位で指定データの総和を取る
 *
 * @param[in] ary データ配列先頭へのポインタ
 * @param[in] sz データサイズ
 *
 * return チェックサム値
 */
_UWORD _check_sum(void* ary, _UWORD sz);

/**
 * @brief 数値文字列変換
 *
 * 数値を指定進数表記の数字列に変換する。NUL終端はしない。
 * 10進数を越える数字列の場合は10以降アルファベット表記となる。
 *
 * @param[in] in 変換する数値。符号無し整数。
 * @param[in] base 進数
 * @param[out] out 結果を格納する文字配列先頭へのポインタ
 * @param[in] size outのサイズ
 *
 * @return 変換桁数
 */
_UINT _itoa(_UINT in, _SINT base, _SBYTE *out, _UINT size);

/**
 * @brief 乱数取得
 *
 * 乱数値を取得する。精度は15bit。
 *
 * @return 乱数値
 */
_SDWORD _rand();

/**
 * @brief 乱数の種設定
 *
 * 乱数の種をセットする。
 *
 * @param[in] s 乱数の種
 */
void _srand(_SDWORD s);

#ifdef __cplusplus
}
#endif

#endif /* _STDLIB_H_ */
