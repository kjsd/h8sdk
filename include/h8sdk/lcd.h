/**
 * @file lcd.h
 *
 * @brief LCD�h���C�o
 *
 * ���̃��W���[����LCD�f�o�C�XSC1602BS�ւ̃C���^�t�F�[�X��񋟂���B
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
#ifndef LCD_H_
#define LCD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

/**
 * @brief LCD�\�����̗�
 */
#define LCD_MAX_COLS 16

/**
 * @brief LCD�\�����̍s��
 */
#define LCD_MAX_ROWS 2

/**
 * @brief �L�����N�^���h�b�g��
 */
#define LCD_CG_COLS 5

/**
 * @brief �L�����N�^�c�h�b�g��
 */
#define LCD_CG_ROWS 8

/**
 * @brief �o�^�\�ȍő�L�����N�^��
 */
#define LCD_CG_MAXCHAR 8


/**
 * @brief LCD�f�o�C�X������
 *
 * �f�o�C�X���g�p�\�ɂ���B�S�Ă�API�̑O�ɂ�������s���Ă����B������
 * ��l�́A@n
 * @li �L�����N�^��8�r�b�g
 * @li �\��2��
 * @li �L�����N�^�T�C�Y5x10�h�b�g
 * @li �J�[�\��OFF�A�u�����NOFF
 * @li �J�[�\���C���N�������g����A�\���V�t�g�Ȃ�
 */
void LCD_init();

/**
 * @brief ������o��
 *
 * �������LCD�ɏo�͂���B�������NUL�I�[����Ă��Ȃ���΂Ȃ�Ȃ��B
 * ���ꕶ���� '\\n' �̂݁B���s�����Ɖ��߂����B
 *
 * @param[in] str �����z��̐擪�ւ̃|�C���^
 *
 * @return �o�͂��ꂽ������
 *
 * @note �o�̓J�[�\���͕\�����̗̈�����[�v����B
 */
_SINT LCD_puts(const _SBYTE *str);

/**
 * @brief �o�C�g�X�g���[����������
 *
 * �ėp�f�[�^�o�́B�J�[�\�����݈ʒu����w��T�C�Y���̃o�C�g�f�[�^��LCD
 * �ɏo�͂���B
 *
 * @param[in] data �f�[�^�̐擪�ւ̃|�C���^
 * @param[in] size �o�̓T�C�Y
 *
 * @return �o�͂��ꂽ�o�C�g��
 *
 * @note �J�[�\���͕\�����̗̈�����[�v����B
 */
_SINT LCD_write(const _UBYTE *data, _SINT size);

/**
 * @brief �o�C�g�X�g���[���ǂݏo��
 *
 * �ėp�f�[�^���́B�J�[�\�����݈ʒu����w��o�C�g�ǂݏo���B
 *
 * @param[in] buf �f�[�^���i�[����̈�̐擪�ւ̃|�C���^
 * @param[in] size �ǂݏo���T�C�Y
 *
 * @return �ǂݏo���ꂽ�o�C�g��
 *
 * @note �J�[�\���͕\�����̗̈�����[�v����B
 */
_SINT LCD_read(_UBYTE* buf, _SINT size);

/**
 * @brief �J�[�\���ʒu�擾
 *
 * ���݂̏o�͈ʒu���擾����B�����̈ʒu�w��͐�Βl�� 0 origin�B���_��
 * ������A�E���������v���X�̗̈�B
 *
 * @param[in] x ������̈ʒu���i�[����|�C���^
 * @param[in] y �s�����̈ʒu���i�[����|�C���^
 */
void LCD_getCursor(_SINT* x, _SINT* y);

/**
 * @brief �J�[�\���ړ�
 *
 * �o�͈ʒu���ړ�������B�\�����͈̔͂ł݈̂ړ��\�B�����̈ʒu�w���
 * ��Βl�� 0 origin�B���_�͍�����A�E���������v���X�̗̈�B�͈͂��z��
 * ���l�w��͖��������B
 *
 * @param[in] x ������̈ʒu���w�肷��
 * @param[in] y �s�����̈ʒu���w�肷��
 */
void LCD_setCursor(_SINT x, _SINT y);

/**
 * @brief ���s�o��
 *
 * �o�̓J�[�\������s���̍ō���ֈړ�������B
 * 
 * @note �o�̓J�[�\���͕\�����̗̈�����[�v����B
 */
void LCD_crlf();

/**
 * @brief �̈�N���A
 *
 * LCD�o�b�t�@�̓��e���N���A����
 */
void LCD_cls();

/**
 * @brief �L�����N�^�o�^
 *
 * ���[�U�[�쐬�L�����N�^�f�[�^��V�K��LCD�f�o�C�X�֓o�^����B ����A
 * �h���X�œo�^�ς݂̃L�����N�^�͏㏑�������B
 *
 * @param[in] no �o�^�A�h���X�B0�`LCD_CG_MAXCHAR-1 �܂ł��w�肷��
 * @param[in] data �o�^�L�����N�^�z��擪�ւ̃|�C���^�BLCD_CG_ROWS�o�C
 * �g�̔z���LCD_CG_COLS x LCD_CG_ROWS�̃r�b�g�p�^�[���s��Ƃ݂Ȃ����f�[
 * �^����w�肷��B
 */
void LCD_setChar(_UBYTE no, const _UBYTE *data);

/**
 * @brief �\�����[�h�ύX
 *
 * �J�[�\���A�_�łȂǂ̕\�����[�h��ύX����B������Ԃ́A�\����_TRUE�A
 * �J�[�\���A�_�ł�_FALSE�B
 *
 * @param[in] all �S�\���̃I��/�I�t�w��
 * @param[in] cur �J�[�\���̃I��/�I�t�w��
 * @param[in] blink �J�[�\���ʒu�̃u�����N�I��/�I�t�w��
 */
void LCD_setVisual(_BOOL all, _BOOL cur, _BOOL blink);

#ifdef __cplusplus
}
#endif

#endif /* LCD_H_ */
