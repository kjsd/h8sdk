/**
 * @file ps2.h
 *
 * @brief PS/2�h���C�o
 *
 * ���̃��W���[����PS/2�|�[�g�ւ̃C���^�t�F�[�X��񋟂���B
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
#ifndef PS2_H_
#define PS2_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

#define PS2_MAX_RXBUF 8

typedef enum
{
    PS2_ERR_OK = 0,
    PS2_ERR_FRAMING,
    PS2_ERR_PARITY,

    PS2_NUM_OF_ERR
} PS2_Status;

/**
 * @brief PS2�|�[�g������
 *
 * �f�o�C�X���g�p�\�ɂ���B�S�Ă�API�̑O�ɂ�������s���Ă����B
 */
void PS2_init();

/**
 * @brief ����M���s
 *
 * PS/2�f�o�C�X�֑���M�������ϑ�����B���荞�݃n���h������Ă΂���
 * ���O��B
 */
void PS2_communicate();

/**
 * @brief �o�C�g�X�g���[����M
 *
 * �����o�b�t�@�ɗ��܂��Ă���f�[�^���擾����B����/�񓯊���M�̗�����
 * �Ή��B�����o�b�t�@�ɂ͔񓯊��Ő�����M�f�[�^�����܂��Ă������߁A��
 * ���I�ɂ���API�����s���Ȃ��ƃo�b�t�@�����f�[�^���X����������B
 *
 * @param[in] buf ��M�f�[�^���i�[����o�b�t�@�̐擪�ւ̃|�C���^
 * @param[in] size ��M�T�C�Y
 * @param[in] sync _TRUE: �����^�Bsize����M�ł��邩�A�^�C���A�E�g����
 * �܂Ńu���b�N����B@n
 * _FALSE: �񓯊��^�B�^�C���A�E�g�͖���
 * @param[in] tmo_ms ������M���̃^�C���A�E�g�l�B�~���Z�J���h�B
 *
 * @retval ���̒l ��M�����T�C�Y
 * @retval ���̒l ��M�G���[
 */
_SINT PS2_read(_UBYTE* buf, _UBYTE size, _BOOL sync, _SINT tmo_ms);


#ifdef __cplusplus
}
#endif

#endif /* PS2_H_ */
