/**
 * @file ioctl.h
 *
 * @brief I/O�|�[�g�R���g���[��
 *
 * ���̃��W���[���͊e�|�[�g�R���g���[�����W�X�^(PCR)�ւ̑��d�A�N�Z�X��
 * �Ǘ�����BPCR�͓ǂݍ��݂��s����̂��߁A�����̓Ɨ��������W���[������
 * �ݒ肷��ꍇ�A�O�ɐݒ肳�ꂽ�l����̂��̂ŏ㏑������Ď����Ă���
 * ���B���̃��W���[���͂����h�����߂�PCR�ւ̑��d�A�N�Z�X�̓��������
 * ������S���B�������A���荞�݃n���h������̐ݒ�̓T�|�[�g����Ȃ��B
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
 * @brief PCR���W�X�^���e������`�^
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
 * @brief ������
 *
 * ���W���[���̏�������PCR���W�X�^�̃[���N���A���s��
 */
void IOCTL_init();

/**
 * @brief ���W�X�^�֒l�Z�b�g
 *
 * �w��PCR���W�X�^�փr�b�g�}�X�N���w�肵�Ēl���Z�b�g����B
 * �}�X�N�r�b�g�ȊO�̒l�͕ێ������B
 *
 * @param[in] reg �Z�b�g���郌�W�X�^
 * @param[in] mask �Z�b�g����l�̗L���r�b�g�}�X�N
 * @param[in] val �Z�b�g����l
 */
void IOCTL_set(IOCTL_Reg reg, _UBYTE mask, _UBYTE val);

/**
 * @brief ���W�X�^�l�擾
 *
 * ���݂̎w��PCR���W�X�^�l���擾����B�����ŕێ�����Ă���l���Ԃ�A��
 * �ۂ�I/O�|�[�g�ւ̃A�N�Z�X�͍s��Ȃ��B
 *
 * @param[in] reg �l���擾���郌�W�X�^
 *
 * @return ���W�X�^�l
 */
_UBYTE IOCTL_get(IOCTL_Reg reg);

#ifdef __cplusplus
}
#endif

#endif /* IOCTL_H_ */
