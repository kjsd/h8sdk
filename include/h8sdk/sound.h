/**
 * @file sound.h
 *
 * @brief �T�E���h�h���C�o
 *
 * ���̃��W���[���͉����Đ������邽�߂̃C���^�t�F�[�X��񋟂���B@n
 * H8-BASE2�Ŏg�p�ł���3�̃^�C�}���g���A�����A�����A�����\�킷��`�g��
 * �X�s�[�J�|�[�g�֏o�͂���B
 *
 * @attention TimerA, TimerV, TimerW�𑼂̃��W���[���Ŏg�p���Ă͂Ȃ�Ȃ��B
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
#ifndef SOUND_H_
#define SOUND_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

/** �ő哯�����M���� */
#define SOUND_MAX_PRONOUNCE 3
/** �{�����[���̍ő�l */
#define SOUND_MAX_VOLUME 255

#define SOUND_PRONOUNCE_LEN 2

/** ���� */
#define SOUND_NA 0
/** �I�N�^�[�u0 �h */
#define SOUND_C0 255
/** �I�N�^�[�u0 �h# */
#define SOUND_Cb0 241
/** �I�N�^�[�u0 �� */
#define SOUND_D0 228
/** �I�N�^�[�u0 ��# */
#define SOUND_Db0 214
/** �I�N�^�[�u0 �~ */
#define SOUND_E0 203
/** �I�N�^�[�u0 �t�@ */
#define SOUND_F0 192
/** �I�N�^�[�u0 �t�@# */
#define SOUND_Fb0 180
/** �I�N�^�[�u0 �\ */
#define SOUND_G0 171
/** �I�N�^�[�u0 �\# */
#define SOUND_Gb0 161
/** �I�N�^�[�u0 �� */
#define SOUND_A0 152
/** �I�N�^�[�u0 ��# */
#define SOUND_Ab0 143
/** �I�N�^�[�u0 �V */
#define SOUND_H0 136
/** �I�N�^�[�u1 �h */
#define SOUND_C1 128
/** �I�N�^�[�u1 �h# */
#define SOUND_Cb1 120
/** �I�N�^�[�u1 �� */
#define SOUND_D1 114
/** �I�N�^�[�u1 ��# */
#define SOUND_Db1 107
/** �I�N�^�[�u1 �~ */
#define SOUND_E1 101
/** �I�N�^�[�u1 �t�@ */
#define SOUND_F1 96
/** �I�N�^�[�u1 �t�@# */
#define SOUND_Fb1 90
/** �I�N�^�[�u1 �\ */
#define SOUND_G1 85
/** �I�N�^�[�u1 �\# */
#define SOUND_Gb1 80
/** �I�N�^�[�u1 �� */
#define SOUND_A1 76
/** �I�N�^�[�u1 ��# */
#define SOUND_Ab1 72
/** �I�N�^�[�u1 �V */
#define SOUND_H1 68
/** �I�N�^�[�u2 �h */
#define SOUND_C2 64
/** �I�N�^�[�u2 �h# */
#define SOUND_Cb2 60
/** �I�N�^�[�u2 �� */
#define SOUND_D2 57
/** �I�N�^�[�u2 ��# */
#define SOUND_Db2 54
/** �I�N�^�[�u2 �~ */
#define SOUND_E2 51
/** �I�N�^�[�u2 �t�@ */
#define SOUND_F2 48
/** �I�N�^�[�u2 �t�@# */
#define SOUND_Fb2 45
/** �I�N�^�[�u2 �\ */
#define SOUND_G2 43
/** �I�N�^�[�u2 �\# */
#define SOUND_Gb2 40
/** �I�N�^�[�u2 �� */
#define SOUND_A2 38
/** �I�N�^�[�u2 ��# */
#define SOUND_Ab2 36
/** �I�N�^�[�u2 �V */
#define SOUND_H2 34
/** �I�N�^�[�u3 �h */
#define SOUND_C3 32
/** �I�N�^�[�u3 �h# */
#define SOUND_Cb3 30
/** �I�N�^�[�u3 �� */
#define SOUND_D3 29
/** �I�N�^�[�u3 ��# */
#define SOUND_Db3 27
/** �I�N�^�[�u3 �~ */
#define SOUND_E3 25
/** �I�N�^�[�u3 �t�@ */
#define SOUND_F3 24
/** �I�N�^�[�u3 �t�@# */
#define SOUND_Fb3 23
/** �I�N�^�[�u3 �\ */
#define SOUND_G3 21
/** �I�N�^�[�u3 �\# */
#define SOUND_Gb3 20
/** �I�N�^�[�u3 �� */
#define SOUND_A3 19
/** �I�N�^�[�u3 ��# */
#define SOUND_Ab3 18
/** �I�N�^�[�u3 �V */
#define SOUND_H3 17


/**
 * @brief �Đ���ԃ��e�����^
 */
typedef enum
{
    SOUND_ST_STOP = 0,
    SOUND_ST_PLAY,
    SOUND_ST_REVERSE,

    SOUND_NUM_OF_STATE
} SOUND_State;

/**
 * @brief �G���x���[�v��`�^
 *
 * ���������̋��ヌ�x�����`����^
 */
typedef struct
{
    _UBYTE* data;
    /**< �G���x���[�v�f�[�^��̐擪�ւ̃|�C���^ */
    _UWORD size;
    /**< �G���x���[�v�f�[�^��̃T�C�Y */
} SOUND_Envelope;

/**
 * @brief ����`�^
 *
 * ����^�C�~���O�ł̔��������`����^
 */
typedef struct
{
    _UBYTE freq;
     /**< ���̎��g�� */
    SOUND_Envelope* evlp;
     /**< ���̉��𔭐�������Ƃ��̃G���x���[�v */
    SOUND_Envelope* reverb;
     /**< �Đ���̎c�����ʁB���o�[�u */
    _BOOL loop;
     /**< ���o�[�u�̃��[�v�t���O */
} SOUND_Tone;

/**
 * @brief �Đ����샊�N�G�X�gAPI�̌^
 */
typedef _BOOL (*SOUND_Api)();

/**
 * @brief ��ԃn���h���z��
 *
 * ���̔z��ɍĐ���ԃ��e�������C���f�b�N�X�Ƃ��ė^����΁A���e�����ɉ�����
 * �n���h�����Ă΂��B
 *
 * @see SOUND_State
 */
extern const SOUND_Api SOUND_state_handler[SOUND_NUM_OF_STATE];

/**
 * @brief �T�E���h�h���C�o������
 *
 * �^�C�}�ƃ|�[�g�̏��������s���B��API�g�p�O�ɕK�����s����B
 */
void SOUND_init();

/**
 * @brief ���݂̍Đ���Ԏ擾
 *
 * @return �Đ���ԃ��e����
 */
SOUND_State SOUND_getState();

/**
 * @brief �{�����[���ݒ�
 *
 * �Đ����ʂ�ݒ肷��B0�`SOUND_MAX_VOLUME
 * ���ł��ݒ�\�B
 *
 * @param[in] val �{�����[���l
 */
void SOUND_setVolume(_UBYTE val);

/**
 * @brief �G���x���[�v�����ݒ�
 *
 * �G���x���[�v���Z�b�g���������ݒ肷��B
 * ���̐ݒ�l�͍Đ������ƃ{�����[�����߂ׂ̍����ɉe�����A���҂̓g���[�h�I�t��
 * �֌W�ɂ���B�����l��256�B
 *
 * @param[in] val �ݒ�l
 */
void SOUND_setEvlpCycle(_UWORD val);

/**
 * @brief ���o�^
 *
 * ����o�^����BSOUND_MAX_PRONOUNCE�̃o���N�ɓ����ɃZ�b�g���邱�Ƃ��ł���B
 * ���ł��ݒ�\�B
 *
 * @param[in] idx �o���N�̃C���f�b�N�X�B0�`SOUND_MAX_PRONOUNCE-1
 * @param[in] tone �ݒ肷��SOUND_Tone�ւ̃|�C���^ @n
 * ����(SOUND_Tone::freq == 0)�A�܂���SOUND_Tone::evlp��NULL�̃f�[�^��
 * �o�^���邱�Ƃ͂ł��Ȃ��B
 */
void SOUND_setTone(_UBYTE idx, const SOUND_Tone* tone);

/**
 * @brief ���폜
 *
 * �o���N���w�肵�Đݒ肳�ꂽ�����폜����B
 * ���ł��ݒ�\�B
 *
 * @param[in] idx �폜����o���N�̃C���f�b�N�X�B0�`SOUND_MAX_PRONOUNCE-1
 */
void SOUND_removeTone(_UBYTE idx);

/**
 * @brief ���Đ����N�G�X�g
 *
 * ���̍Đ��B�G���x���[�v�͏������B
 *
 * @retval _TRUE ���N�G�X�g���
 * @retval _FALSE ���N�G�X�g����
 */
_BOOL SOUND_play();

/**
 * @brief ���t�Đ����N�G�X�g
 *
 * ���̍Đ��B�G���x���[�v�͋t�����B
 *
 * @retval _TRUE ���N�G�X�g���
 * @retval _FALSE ���N�G�X�g����
 */
_BOOL SOUND_reverse();

/**
 * @brief ��~���N�G�X�g
 *
 * �Đ����̉����~������B
 *
 * @retval _TRUE ���N�G�X�g���
 * @retval _FALSE ���N�G�X�g����
 */
_BOOL SOUND_stop();

/**
 * @brief �g�`����
 *
 * SOUND_pronounce�ɂ���͂��ꂽ�����ɂ����ۂɋ�`�g�𐶐�������B
 * TimerV���荞�݃n���h�����炱��API���ĂԕK�v������B���荞�݃t���O�͓�����
 * �N���A���Ă���B
 *
 * @see 
 */
void SOUND_makePulse();

/**
 * @brief ���f�[�^����
 *
 * �g�`�����̂��߂̃^�C�}�J�E���g���Ȃǂ�ݒ肷��B
 * TimerA���荞�݃n���h�����炱��API���ĂԕK�v������B���荞�݃t���O�̓N���A
 * ����Ȃ��B
 */
void SOUND_pronounce();

#ifdef __cplusplus
}
#endif

#endif /* SOUND_H_ */
