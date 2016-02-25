/**
 * @file stddef.h
 *
 * @brief ���ʌ^�A���e������`
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
/**
 * @mainpage �͂��߂�
 *
 * @section abstract ���̕����ɂ���
 * ���̕����́AH8 Software Development Kit(�ȉ�H8SDK)�̃C���^�t�F�[�X
 * �d�l���ł���B@n
 * �����͑傫���f�[�^�\���̉���Z�N�V�����ƁA�t�@�C�����W���[���ʂ̃C
 * ���^�t�F�[�X����Z�N�V�����ɕ�����Ă���A���ꂼ��̃Z�N�V�����͖`
 * ���ŉ�����ڂ��T�������t���ŗ񋓂�����A���ڂ̏ڍא����������Ƃ���
 * �\���ɂȂ��Ă���B
 *
 * @section target �Ώ�
 * H8SDK���g�p����H8�{�[�h��A�v���P�[�V�����̍쐬���s���J���Ҍ����̕�
 * ���ł���AH8�v���b�g�t�H�[���̃n�[�h�E�F�A�d�l�𗝉����Ă��邱�Ƃ�
 * �O��ł���B
 *
 * @section namespace ���O���
 * H8SDK�́A�ȉ��̋K���Ɋ�Â��Ė��O��Ԃ��K�肳��Ă���B
 * @li '_'�Ŏn�܂閼�O���
 * @li stddef.h�Astdlib.h�Astdio.h�Aassert.h�ȊO�̃��W���[����
 * �����āA���W���[�����Ƃ��Ďg���Ă���3�����`�Ŏn�܂閼�O���
 *
 * @attention �K���O�̃V���{�����ꕔ���݂���
 *
 ***********************************************************************/
#ifndef _STDDEF_H_
#define _STDDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

/** ��������8�r�b�g�����^ */
typedef signed char _SBYTE;
/** �����Ȃ�8�r�b�g�����^ */
typedef unsigned char _UBYTE;
/** ��������16�r�b�g�����^ */
typedef signed short _SWORD;
/** �����Ȃ�16�r�b�g�����^ */
typedef unsigned short _UWORD;
/** ��������16�r�b�g�����^ */
typedef signed int _SINT;
/** �����Ȃ�16�r�b�g�����^ */
typedef unsigned int _UINT;
/** ��������32�r�b�g�����^ */
typedef signed long _SDWORD;
/** �����Ȃ�32�r�b�g�����^ */
typedef unsigned long _UDWORD;

/**
 * @brief �u�[���^
 *
 * 2�l����p�u�[���^�B���̌^���m�ł̕]���ȊO�ɂ͎g�p���Ă͂Ȃ�Ȃ��B
 */
typedef enum
{
    _FALSE = 0,
    /**< �U */
    _TRUE = ~_FALSE
    /**< �^ */
} _BOOL;

/**
 * @brief �z��̗v�f���擾
 *
 * @param[in] x �擾����z��
 *
 * @return �z��̗v�f��
 */
#define _sizeof_array(x) (sizeof(x)/sizeof(x[0]))

/**
 * @brief �\���̃����o�̗v�f�ւ̃I�t�Z�b�g���擾
 *
 * @param[in] type member�̍\���̌^�^�C�v
 * @param[in] member �I�t�Z�b�g���擾���郁���o��
 *
 * @return member�܂ł̃I�t�Z�b�g
 */
#define _offsetof(type, member) ((_UWORD)&((type*)0)->(member))


#ifdef __cplusplus
}
#endif

#endif /* _STDDEF_H_ */
