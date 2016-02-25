/**
 * @file assert.h
 *
 * @brief �A�T�[�g
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
 * @brief �A�T�[�g
 *
 * �����~�X�ȊO�ł͂��肦�Ȃ��o�O���`�F�b�N���邽�߂̎��s���G���[�`�F�b
 * �J�B�f�o�b�O��p�B�����[�X�o�C�i������͊O�����B
 *
 * @param[in] x �]������p�����[�^�B���ꂪ�U�ɂȂ�Ə������ً}��~����
 * LED�_�łŏ�Ԉُ��m�点��B
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
