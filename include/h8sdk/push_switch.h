/**
 * @file push_switch.h
 *
 * @brief �v�b�V���X�C�b�`�h���C�o
 *
 * ���̃��W���[���̓v�b�V���X�C�b�`�ւ̃C���^�t�F�[�X��񋟂���B
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
 * @brief ������Ԕ���p�̃J�E���^
 *
 * ��x���肳�ꂽ�炱�̒l���J�E���g�����܂ŉ�����Ԃ̔���͍s��Ȃ�
 */
#define PSW_BORDER 0x800

/**
 * @brief �X�C�b�`�^�C�v���ʎq
 */
typedef enum
{
    PSW_SW1 = 0,
    /**< S1�ԃ|�[�g�̃X�C�b�` */
    PSW_SW2,
    /**< S2�ԃ|�[�g�̃X�C�b�` */

    PSW_NUM_OF_TYPE
    /**< �X�C�b�`�̐� */
} PSW_Type;

/**
 * @brief �X�C�b�`�f�o�C�X�������B
 *
 * �X�C�b�`�f�o�C�X���g�p�\�ɐݒ肷��B��API�g�p�O�ɕK�����s����B
 *
 * @param[in] interrupt
 * _TRUE�F���荞�݂��g���B@n
 * _FALSE�F���荞�݂��g��Ȃ��B
 *
 * @note ���荞�݃n���h���͊O���Œ�`����B
 */
void PSW_init(_BOOL interrupt);

/**
 * @brief �X�C�b�`������Ԃ̎擾
 *
 * �X�C�b�`�̉�����Ԃ𓾂�B��x�����Ɣ��肳�ꂽ�ꍇ�APSW_BORDER�J�E
 * ���g���Ăяo�����܂Ŏ��̏�Ԕ���͍s���Ȃ��B�Ȃ̂ŁA����I�Ɉ�
 * ��񐔂���API�����s���邱�ƂŐ��m�ȏ�Ԃ�A���I�Ɏ擾�ł���悤�ɂ�
 * ��B�|�[�����O�p�B
 *
 * @param[in] t �擾����X�C�b�`�̃^�C�v
 *
 * @retval _TRUE ������Ă���
 * @retval _FALSE ������Ă��Ȃ�
 *
 * @note ���荞�݂��g�p����ꍇ�͂���API���g���K�v�͂Ȃ�
 */
_BOOL PSW_get(PSW_Type t);

/**
 * @brief �X�C�b�`������Ԃ���x�����擾
 *
 * �X�C�b�`�̉�����Ԃ𓾂�B��x�����Ɣ��肳�ꂽ��X�C�b�`���I�t�ɂ�
 * ��܂ŉ�������͍s���Ȃ�
 *
 * @param[in] t �擾����X�C�b�`�̃^�C�v
 *
 * @retval _TRUE ������Ă���
 * @retval _FALSE ������Ă��Ȃ�
 *
 * @note ���荞�݂��g�p����ꍇ�͂���API���g���K�v�͂Ȃ�
 */
_BOOL PSW_oneShot(PSW_Type t);

/**
 * @brief �X�C�b�`������ԃX�i�b�v�V���b�g�̎擾
 *
 * �X�C�b�`�̉�����Ԃ𓾂�B�擾�����̂͂��̏u�Ԃ̏�ԁB
 *
 * @param[in] t �擾����X�C�b�`�̃^�C�v
 *
 * @retval _TRUE ������Ă���
 * @retval _FALSE ������Ă��Ȃ�
 *
 * @note ���荞�݂��g�p����ꍇ�͂���API���g���K�v�͂Ȃ�
 */
_BOOL PSW_snapShot(PSW_Type t);

#ifdef __cplusplus
}
#endif

#endif /* PSW_H_ */
