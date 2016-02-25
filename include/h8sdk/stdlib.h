/**
 * @file stdlib.h
 *
 * @brief ���[�e�B���e�B���C�u����
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
 * @brief NULL�|�C���^���ʎq
 *
 * �����ȃ|�C���^��\�����e����
 *
 * @note ���̃��e�����̂�H8SDK�����K���̗�O�Ƃ���
 */
#define NULL ((void*)0)

/**
 * @brief �}�C�N���b�X���[�v
 *
 * �X���[�v�֐��B�����̃r�W�[���[�v�̂��ߐ��x�͊��ɂ���đ傫���ω�����
 *
 * @param[in] us �X���[�v���鎞�ԁB�}�C�N���b
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
 * @brief �~���b�X���[�v
 *
 * �X���[�v�֐��B�����̃r�W�[���[�v�̂��ߐ��x�͊��ɂ���đ傫���ω�����
 *
 * @param[in] ms �E�F�C�g���鎞�ԁB�~���b
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
 * @brief �����O�o�b�t�@�̎��̃C���f�b�N�X���擾
 *
 * @param[in] now ���݂̃C���f�b�N�X�l
 * @param[in] last �Ō�̃C���f�b�N�X�l
 *
 * @return ���̃C���f�b�N�X�l
 */
#define _next_ring(now, last) ((now) == (last) ? 0: (now) + 1)
/**
 * @brief �����O�o�b�t�@�̑O�̃C���f�b�N�X���擾
 *
 * @param[in] now ���݂̃C���f�b�N�X�l
 * @param[in] last �Ō�̃C���f�b�N�X�l
 *
 * @return �O�̃C���f�b�N�X�l
 */
#define _prev_ring(now, last) ((now) == 0 ? (last): (now) - 1)

/**
 * @brief �n�b�V���֐�
 *
 * @param[in] x �n�b�V���v�Z�Ώ�
 * @param[in] size �n�b�V���e�[�u���̃T�C�Y 
 *
 * @return x�̃n�b�V���l
 */
#define _hash(x, size) ((x) % (size))

/**
 * @brief �`�F�b�N�T���v�Z
 *
 * 16�r�b�g�P�ʂŎw��f�[�^�̑��a�����
 *
 * @param[in] ary �f�[�^�z��擪�ւ̃|�C���^
 * @param[in] sz �f�[�^�T�C�Y
 *
 * return �`�F�b�N�T���l
 */
_UWORD _check_sum(void* ary, _UWORD sz);

/**
 * @brief ���l������ϊ�
 *
 * ���l���w��i���\�L�̐�����ɕϊ�����BNUL�I�[�͂��Ȃ��B
 * 10�i�����z���鐔����̏ꍇ��10�ȍ~�A���t�@�x�b�g�\�L�ƂȂ�B
 *
 * @param[in] in �ϊ����鐔�l�B�������������B
 * @param[in] base �i��
 * @param[out] out ���ʂ��i�[���镶���z��擪�ւ̃|�C���^
 * @param[in] size out�̃T�C�Y
 *
 * @return �ϊ�����
 */
_UINT _itoa(_UINT in, _SINT base, _SBYTE *out, _UINT size);

/**
 * @brief �����擾
 *
 * �����l���擾����B���x��15bit�B
 *
 * @return �����l
 */
_SDWORD _rand();

/**
 * @brief �����̎�ݒ�
 *
 * �����̎���Z�b�g����B
 *
 * @param[in] s �����̎�
 */
void _srand(_SDWORD s);

#ifdef __cplusplus
}
#endif

#endif /* _STDLIB_H_ */
