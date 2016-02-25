/**
 * @file led.h
 *
 * @brief LED�h���C�o
 *
 * ���̃��W���[����LED�f�o�C�X�ւ̃C���^�t�F�[�X��񋟂���B
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
 * @brief LED�^�C�v���ʎq
 */
typedef enum
{
    LED_D5 = 0,
    /**< D5�ԃ|�[�g��LED */
    LED_D6,
    /**< D6�ԃ|�[�g��LED */

    LED_NUM_OF_TYPE
    /**< LED�^�C�v�̐� */
} LED_Type;

/**
 * @brief LED���ڑ�����Ă���GPIO���W�X�^�̃x�[�X�l
 */
#define LED_BASE (1U << 1)

/**
 * @brief LED������
 *
 * LED�f�o�C�X���g�p�\�ɐݒ肷��B�S�Ă�API�̑O�ɂ�������s���Ă����B
 */
#define LED_INIT                                                      \
    do                                                                \
    {                                                                 \
        IOCTL_set(IOCTL_REG_PCR8, 0x06, 0x06);                        \
        _IO.PDR8.BYTE |= (LED_BASE << LED_D5 | LED_BASE << LED_D6);   \
    }                                                                 \
    while (_FALSE)

/**
 * @brief LED�_��
 *
 * LED���ЂƂ_��������B
 *
 * @param[in] t �_��������LED�̎�ށBLED_Type
 */
#define LED_ON(t) (_IO.PDR8.BYTE &= ~(LED_BASE << (t)))

/**
 * @brief LED����
 *
 * LED���ЂƂ���������B
 *
 * @param[in] t ����������LED�̎�ށBLED_Type
 */
#define LED_OFF(t) (_IO.PDR8.BYTE |= LED_BASE << (t))

/**
 * @brief LED�\�����]
 *
 * �w�肳�ꂽLED�̕\�������݂̂��̂Ɣ��]������B
 *
 * @param[in] t ���]������LED�̎�ށBLED_Type
 */
#define LED_TURN(t) (_IO.PDR8.BYTE ^= LED_BASE << (t))


#ifdef __cplusplus
}
#endif

#endif /* LED_H_ */
