/**
 * @file ssrp_skel.h
 *
 * @brief SSRP�X�P���g��
 *
 * ���̃��W���[����SSRP�ʐM�����[�v�o�b�N�ōs�����߂̃X�P���g���ł���B
 *
 * @see ssrp.h
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
#ifndef SSRP_SKEL_H_
#define SSRP_SKEL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

#define SSRP_SKEL_LOOPBACK_ADDR 0xfe


/**
 * @brief �o�C�g�X�g���[�����M
 *
 * ��ɐ������鑗�MAPI�B���M�f�[�^�͔j�������B
 * ���̑��d�l��ifstub.h�ɏ����B
 *
 * @see ifstub.h
 */
_SINT SSRP_SKEL_write(const _UBYTE* data, _UBYTE size,
                      _BOOL sync, _SINT tmo_ms);

/**
 * @brief �o�C�g�X�g���[����M
 *
 * SSRP�̓�����Ԃɉ����ď�ɓK�؂Ȏ�M�f�[�^��Ԃ��B
 * ���̑��d�l��ifstub.h�ɏ����B
 *
 * @see ifstub.h
 */
_SINT SSRP_SKEL_read(_UBYTE* buf, _UBYTE size, _BOOL sync, _SINT tmo_ms);

#ifdef __cplusplus
}
#endif

#endif /* SSRP_SKEL_H_ */
