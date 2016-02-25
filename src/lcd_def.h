/**
 * @file lcd_def.h
 *
 * @brief LCDドライバ内部構造
 *
 * このファイルにはLCDドライバモジュールの内部構造が定義されている。
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
#ifndef LCD_DEF_H
#define LCD_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/h8sdk/stdlib.h"
#include "../include/h8sdk/3694s.h"
#include "../include/h8sdk/ioctl.h"
#include "../include/h8sdk/assert.h"
#include "../include/h8sdk/lcd.h"

/** レジスタのRSフラグ */
#define REG_RS_ _IO.PDR1.BIT.B0
/** レジスタのRWフラグ */
#define REG_RW_ _IO.PDR1.BIT.B1
/** レジスタのEフラグ */
#define REG_E_ _IO.PDR1.BIT.B2
/** データレジスタ */
#define REG_DATA_ _IO.PDR5.BYTE

/** レジスタ書き込みを表すリテラル */
#define FLG_WRITE_ 0
/** レジスタ読み込みを表すリテラル */
#define FLG_READ_ 1
/** ビジー状態 */
#define FLG_BUSY_ 0x80
#define FLG_CGRAM_ 0x40
#define FLG_DDRAM_ 0x80

/**
 * @brief LCDコントロールレジスタのポート設定にアクセス
 */
#define CTRL_IN_ IOCTL_set(IOCTL_REG_PCR1, 0x07, 0)
#define CTRL_OUT_ IOCTL_set(IOCTL_REG_PCR1, 0x07, 0x07)

/**
 * @brief LCDデータレジスタのポート設定にアクセス
 */
#define DATA_IN_ IOCTL_set(IOCTL_REG_PCR5, 0xff, 0)
#define DATA_OUT_ IOCTL_set(IOCTL_REG_PCR5, 0xff, 0xff)


typedef enum
{
    SYM_INST_ = 0,
    SYM_DATA_ = 1
} Registor_;

static _SINT x_;
static _SINT y_;

static _UBYTE readReg_(Registor_ sym);
static void writeReg_(_UBYTE data, Registor_ rs);

#ifdef __cplusplus
}
#endif

#endif /* LCD_DEF_H */
