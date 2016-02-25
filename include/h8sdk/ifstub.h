/**
 * @file ifstub.h
 *
 * @brief �ʐM�C���^�t�F�[�X�X�^�u
 *
 * ���̃��W���[���͑���ƒʐM����Ƃ��̃C���^�t�F�[�X�݂̂��`����
 * �X�^�u�ł���B
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
#ifndef IFSTUB_H_
#define IFSTUB_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"


/** �C���^�t�F�[�X�^�C�v�^��` */
typedef enum
{
    IFSTUB_SCI = 0,
    /**< �V���A���|�[�g */
#ifdef USE_LOOPBACK_SSRP
    IFSTUB_SSRP_SKELETON,
    /**< SSRP�P�̓���h���C�o */
#endif /* USE_LOOPBACK_SSRP */

    IFSTUB_NUM_OF_TYPE
} IFSTUB_Type;

/**
 * @brief �o�C�g�X�g���[�����M
 *
 * �ėp�o�C�g�f�[�^�𑗐M�\�񂷂�B����/�񓯊����M�̗����ɑΉ��B
 * �w��f�[�^�͓����o�b�t�@�֊i�[����A����̑��M�\���ɏ��������s�����B
 *
 * @param[in] data ���M�f�[�^�̐擪�ւ̃|�C���^
 * @param[in] size ���M�T�C�Y
 * @param[in] sync _TRUE: �����^�Bsize�����M�ł��邩�A�^�C���A�E�g����܂�
 * �u���b�N����B_FALSE: �񓯊��^�B�^�C���A�E�g�͖���
 * @param[in] tmo_ms �������M���̃^�C���A�E�g�l�B�~���Z�J���h�B
 *
 * @retval ���̒l ���M�����T�C�Y
 * @retval ���̒l ���M�G���[
 */
typedef _SINT (*IFSTUB_WriteStream)(const _UBYTE* data, _UBYTE size,
                                    _BOOL sync, _SINT tmo_ms);

/**
 * @brief �o�C�g�X�g���[����M
 *
 * �����o�b�t�@�ɗ��܂��Ă���f�[�^���擾����B����/�񓯊���M�̗����ɑΉ��B
 * �����o�b�t�@�ɂ͔񓯊��Ő�����M�f�[�^�����܂��Ă������߁A����I��
 * ����API�����s���Ȃ��ƃo�b�t�@�����f�[�^���X����������B
 *
 * @param[in] buf ��M�f�[�^���i�[����o�b�t�@�̐擪�ւ̃|�C���^
 * @param[in] size ��M�T�C�Y
 * @param[in] sync _TRUE: �����^�Bsize����M�ł��邩�A�^�C���A�E�g����܂�
 * �u���b�N����B_FALSE: �񓯊��^�B�^�C���A�E�g�͖���
 * @param[in] tmo_ms ������M���̃^�C���A�E�g�l�B�~���Z�J���h�B
 *
 * @retval ���̒l ��M�����T�C�Y
 * @retval ���̒l ��M�G���[
 */
typedef _SINT (*IFSTUB_ReadStream)(_UBYTE* buf, _UBYTE size,
                                   _BOOL sync, _SINT tmo_ms);

/** �X�^�u�{�̌^ */
typedef struct
{
    IFSTUB_WriteStream write;
    /**< �o�̓��\�b�h */
    IFSTUB_ReadStream read;
    /**< ���̓��\�b�h */
} IFSTUB_Class;


const IFSTUB_Class* IFSTUB_getInstance(IFSTUB_Type t);

#ifdef __cplusplus
}
#endif

#endif /* IFSTUB_H_ */
