/**
 * @file envelope.h
 *
 * @brief �G���x���[�v�f�[�^��`
 *
 * �e��G���x���[�v�̎��n��ω��f�[�^����`����Ă���B
 * 192��4��������
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
#ifndef ENVELOPE_H
#define ENVELOPE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sound.h"

/**
 * @brief ����
 */
extern const SOUND_Envelope ENVELOPE_na;

/**
 * @brief �s�A�m
 */
extern const SOUND_Envelope ENVELOPE_piano;

/**
 * @brief ���o�[�u(�s�A�m)
 */
extern const SOUND_Envelope ENVELOPE_piano_reverb;

/**
 * @brief �t���[�g
 */
extern const SOUND_Envelope ENVELOPE_flute;

/**
 * @brief ���o�[�u(�t���[�g)
 */
extern const SOUND_Envelope ENVELOPE_flute_reverb;

/**
 * @brief �h����
 */
extern const SOUND_Envelope ENVELOPE_drum;

/**
 * @brief �g�����y�b�g
 */
extern const SOUND_Envelope ENVELOPE_trumpet;

/**
 * @brief ���o�[�u(�g�����y�b�g)
 */
extern const SOUND_Envelope ENVELOPE_trumpet_reverb;

/**
 * @brief �n�[�v
 */
extern const SOUND_Envelope ENVELOPE_harp;

/**
 * @brief ���o�[�u(�n�[�v)
 */
extern const SOUND_Envelope ENVELOPE_harp_reverb;

#ifdef __cplusplus
}
#endif

#endif /* ENVELOPE_H */
