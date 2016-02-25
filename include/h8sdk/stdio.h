/**
 * @file stdio.h
 *
 * @brief I/O���[�e�B���e�B���C�u����
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
#ifndef _STDIO_H_
#define _STDIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ifstub.h"

/** �W���o�̓|�[�g�B�f�t�H���g�̓V���A���|�[�g */
extern IFSTUB_Type _STDOUT;
/** �W�����̓|�[�g�B�f�t�H���g�̓V���A���|�[�g */
extern IFSTUB_Type _STDIN;
/** �W���G���[�o�̓|�[�g�B�f�t�H���g�̓V���A���|�[�g */
extern IFSTUB_Type _STDERR;

/**
 * @brief �����t�������o��
 *
 * �w��t�H�[�}�b�g�̃p�^�[���ɏ]���ĕ������
 * �Ăяo���O�ɃV���A���h���C�o���W���[��������������Ă���K�v������B
 *
 * @param[in] format �o�͏����B�g�p�ł���ϊ��`���� "%d"(��������10�i
 * ���l), "%u"(�����Ȃ�10�i���l), "%x"(16�i���l), "%o"(8�i���l),
 * "%s"(������)�̂݁B"%"���o�͂���Ƃ��� "%%" �ƋL�q����B
 * @param[in] ... �o�̓p�����[�^��
 *
 * @see sci.h
 */
void _printf(const _SBYTE* format, ...);

#ifdef NDEBUG
#define _dprintf(x)
#else

#if __STDC_VERSION__ == 199901L
#define _dprintf(...) _printf(__VA_ARGS__)
#else
/**
 * @brief �f�o�b�O�p������o��
 *
 * @param[in] x �o�͏����ƃp�����[�^�B�K�����ʕt���ŌĂяo�����ƁB@n
 * e.g. _dprintf(("aaa = %d\n", aaa));
 */
#define _dprintf(x) (_printf x)
#endif

#endif /* NDEBUG */

#ifdef __cplusplus
}
#endif

#endif /* _STDIO_H_ */
