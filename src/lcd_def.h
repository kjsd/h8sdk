/**
 * @file lcd_def.h
 *
 * @brief LCD�h���C�o�����\��
 *
 * ���̃t�@�C���ɂ�LCD�h���C�o���W���[���̓����\������`����Ă���B
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

/** ���W�X�^��RS�t���O */
#define REG_RS_ _IO.PDR1.BIT.B0
/** ���W�X�^��RW�t���O */
#define REG_RW_ _IO.PDR1.BIT.B1
/** ���W�X�^��E�t���O */
#define REG_E_ _IO.PDR1.BIT.B2
/** �f�[�^���W�X�^ */
#define REG_DATA_ _IO.PDR5.BYTE

/** ���W�X�^�������݂�\�����e���� */
#define FLG_WRITE_ 0
/** ���W�X�^�ǂݍ��݂�\�����e���� */
#define FLG_READ_ 1
/** �r�W�[��� */
#define FLG_BUSY_ 0x80
#define FLG_CGRAM_ 0x40
#define FLG_DDRAM_ 0x80

/**
 * @brief LCD�R���g���[�����W�X�^�̃|�[�g�ݒ�ɃA�N�Z�X
 */
#define CTRL_IN_ IOCTL_set(IOCTL_REG_PCR1, 0x07, 0)
#define CTRL_OUT_ IOCTL_set(IOCTL_REG_PCR1, 0x07, 0x07)

/**
 * @brief LCD�f�[�^���W�X�^�̃|�[�g�ݒ�ɃA�N�Z�X
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
