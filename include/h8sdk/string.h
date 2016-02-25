/**
 * @file string.h
 *
 * @brief �����񑀍샆�[�e�B���e�B���C�u����
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
#ifndef _STRING_H_
#define _STRING_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

/**
 * @brief �����񒷎擾
 *
 * �w�蕶����擪����NUL'\0'�����܂ł̐���Ԃ��BNUL�͊܂܂Ȃ��B
 *
 * @param[in] str �������擾���镶����擪�ւ̃|�C���^
 *
 * @return ������
 */
_UWORD _strlen(const _SBYTE* str);

/**
 * @brief �������̈�R�s�[
 *
 * �������̈���w��o�C�g���R�s�[����B�̈�͏d�Ȃ��Ă͂Ȃ�Ȃ��B
 *
 * @param[in] dst �R�s�[��ւ̃|�C���^
 * @param[in] src �R�s�[���ւ̃|�C���^
 * @param[in] size �R�s�[�o�C�g��
 *
 * @return dst�ւ̃|�C���^
 */
void* _memcpy(void* dst, const void* src, _UWORD size);

/**
 * @brief �������̈�Z�b�g
 *
 * �������̈�Ɏw��l���Z�b�g����B
 *
 * @param[in] dst �Z�b�g��ւ̃|�C���^
 * @param[in] c �Z�b�g����l
 * @param[in] size �Z�b�g����o�C�g��
 *
 * @return dst�ւ̃|�C���^
 */
void* _memset(void* dst, _SINT c, _UWORD size);

#ifdef __cplusplus
}
#endif

#endif /* _STRING_H_ */
