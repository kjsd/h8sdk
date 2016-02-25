/**
 * @file ioctl.h
 *
 * @brief I/Oポートコントローラ
 *
 * このモジュールは各ポートコントロールレジスタ(PCR)への多重アクセスを
 * 管理する。PCRは読み込みが不安定のため、複数の独立したモジュールから
 * 設定する場合、前に設定された値が後のもので上書きされて失われてしま
 * う。このモジュールはそれを防ぐためにPCRへの多重アクセスの同期を取る
 * 役割を担う。ただし、割り込みハンドラからの設定はサポートされない。
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
#ifndef IOCTL_H_
#define IOCTL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"


/**
 * @brief PCRレジスタリテラル定義型
 */
typedef enum
{
    IOCTL_REG_PCR1 = 0,
    /**< PCR1 */
    IOCTL_REG_PCR2,
    /**< PCR2 */
    IOCTL_REG_PCR5,
    /**< PCR5 */
    IOCTL_REG_PCR7,
    /**< PCR7 */
    IOCTL_REG_PCR8,
    /**< PCR8 */

    IOCTL_NUM_OF_REG
} IOCTL_Reg;

/**
 * @brief 初期化
 *
 * モジュールの初期化とPCRレジスタのゼロクリアを行う
 */
void IOCTL_init();

/**
 * @brief レジスタへ値セット
 *
 * 指定PCRレジスタへビットマスクを指定して値をセットする。
 * マスクビット以外の値は保持される。
 *
 * @param[in] reg セットするレジスタ
 * @param[in] mask セットする値の有効ビットマスク
 * @param[in] val セットする値
 */
void IOCTL_set(IOCTL_Reg reg, _UBYTE mask, _UBYTE val);

/**
 * @brief レジスタ値取得
 *
 * 現在の指定PCRレジスタ値を取得する。内部で保持されている値が返り、実
 * 際のI/Oポートへのアクセスは行わない。
 *
 * @param[in] reg 値を取得するレジスタ
 *
 * @return レジスタ値
 */
_UBYTE IOCTL_get(IOCTL_Reg reg);

#ifdef __cplusplus
}
#endif

#endif /* IOCTL_H_ */
