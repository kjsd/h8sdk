/**
 * @file sci.h
 *
 * @brief �V���A���|�[�g�h���C�o
 *
 * ���̃��W���[���̓V���A���|�[�g�f�o�C�XSCI3�ւ̃C���^�t�F�[�X��񋟂���
 *
 * @see H83694�O���[�v_�n�[�h�E�F�A�}�j���A��.pdf 14��
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
#ifndef SCI_H_
#define SCI_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

/**
 * @brief ���M�o�b�t�@�T�C�Y
 */
#define SCI_MAX_TXBUF 128

/**
 * @brief ��M�o�b�t�@�T�C�Y
 */
#define SCI_MAX_RXBUF 128

/**
 * @brief �p���e�B�G���[���ʎq
 */
#define SCI_ERR_PARITY (1U << 0)

/**
 * @brief �t���[�~���O�G���[���ʎq
 */
#define SCI_ERR_FRAMING (1U << 1)

/**
 * @brief �I�[�o�[�����G���[���ʎq
 */
#define SCI_ERR_OVERRUN (1U << 2)


/**
 * @brief SCI������
 *
 * SCI���g�p�\�ɐݒ肷��B��API�g�p�O�ɕK�����s���Ă����B
 * ����M�͊��荞�݂ɂ��쓮�����B@n
 * �f�[�^��8�r�b�g�A�p���e�B�Ȃ��A�X�g�b�v�r�b�g1�A�t���[����Ȃ��A
 * �{�[���[�g19200bps
 */
void SCI_init();

/**
 * @brief ����M���s
 *
 * SCI�f�o�C�X�֑���M�������ϑ�����B���荞�݃n���h������Ă΂��̂��O��B
 */
void SCI_communicate();

/**
 * @brief �����񑗐M
 *
 * ������𑗐M����B�������NUL�I�[����Ă��Ȃ���΂Ȃ�Ȃ��B
 * �G���[���������Ȃ����著�M�����܂Ńu���b�N����B
 *
 * @param[in] str ���M������̐擪�ւ̃|�C���^
 *
 * @retval ���̒l ���M����������
 * @retval ���̒l ���M�G���[
 */
_SINT SCI_puts(const _SBYTE *str);

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
_SINT SCI_write(const _UBYTE* data, _UBYTE size, _BOOL sync, _SINT tmo_ms);

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
_SINT SCI_read(_UBYTE* buf, _UBYTE size, _BOOL sync, _SINT tmo_ms);

/**
 * @brief �G���[�l�擾
 *
 * �Ō�ɔ��������G���[�ԍ����擾����B
 *
 * @return �G���[�ԍ��BSCI_ERR_* �Œ�`����Ă���R�[�h�B
 */
_UBYTE SCI_getLastError();

#ifdef __cplusplus
}
#endif

#endif /* SCI_H_ */
