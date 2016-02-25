/**
 * @file unit_test.h
 *
 * @brief ���j�b�g�e�X�g���W���[��
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
#ifndef UTEST_H_
#define UTEST_H_

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @brief �e�X�g�֐��^
 *
 * UTEST_run�ɗ^����e�X�g�֐��̌^
 */
typedef char* (*UTEST_Func)();

/** 
 * @brief �e�X�g�񐔃p�����[�^
 *
 * UTEST_run�����s����x�ɃJ�E���g�A�b�v����B�e�X�g���W���[���{�̂Ŏ�
 * �����Ă����B
 */
extern int UTEST_run_count;

/** 
 * @brief �����]��
 *
 * �w�肳�ꂽ������]�����A�U�Ȃ�Ύw�蕶�����Ԃ��ČĂяo�����֐���
 * ������B
 *
 * @param[in] message �]�����U�̂Ƃ��̃��b�Z�[�W
 * @param[in] test �]����
 */
#define UTEST_assert(message, test)                 \
    do { if (!(test)) return message; } while (0)

/** 
 * @brief �e�X�g�֐����s
 *
 * �w�肳�ꂽ�e�X�g�֐������s���A���s�����ꍇ�̓��b�Z�[�W��Ԃ��ČĂ�
 * �o�����֐��𔲂���B
 *
 * @param[in] test ���s����e�X�g�֐��ւ̃|�C���^
 */
#define UTEST_run(test)                             \
    do {                                            \
        char *message = (test)();                   \
        UTEST_run_count++;                          \
        if (message) return message;                \
    } while (0)

#ifdef __cplusplus
}
#endif

#endif /* UTEST_H_ */
