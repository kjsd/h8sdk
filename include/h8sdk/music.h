/**
 * @file music.h
 *
 * @brief �y�ȉ��t���W���[��
 *
 * ���̃��W���[���͊y�Ȃ̍Đ�/�^���C���^�t�F�[�X��񋟂���B@n
 * �T�E���h�h���C�o�K�{�̂��߁A���̃��W���[�����g���Ƃ��́A�O���ŃT�E
 * ���h�h���C�o�̏�����������K�v�͂Ȃ��B�^���@�\��L���ɂ���Ƃ���
 * USE_MUSIC_RECORD ��define���ăR���p�C������B
 *
 * @note
 * �^���@�\��L���ɂ��邽�߂̃������̈�́A�T�E���h�h���C�o�̍ő哯��
 * ���M����(SOUND_MAX_PRONOUNCE)��1�̂Ƃ��ōŒ�36�o�C�g�̃������̈悪
 * �K�v�ł���A�ȍ~������x��26�o�C�g�̗̈��K�v�Ƃ���B����Řa����
 * �܂މ����ЂƂ�^���\�ł���B@n
 * ����ɁA�^���\�ȉ���(MUSIC_NOTE_OF_RECORD_PART)�́A�ЂƂ����邽
 * �т�14�o�C�g�̗̈悪�K�v�ƂȂ邪�A�ő哯�����M�������W���Ƃ��đ���
 * ���邽�߁A�^�������T�C�Y�~�ő哯�����M�������̗̈悪�K�v�ɂȂ�B��
 * ����A�^�����ɕK�v�ȃ������T�C�Y�́A
 *
 * @par
 * @code
 * 10 + (10 + 14 * MUSIC_NOTE_OF_RECORD_PART) * SOUND_MAX_PRONOUNCE
 * @endcode
 *
 * @par
 * �ŕ\�����B���3�a���̉���5��250�o�C�g�قǕK�v�ɂȂ�B@n
 *
 * @see sound.h
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
#ifndef MUSIC_H_
#define MUSIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "sound.h"

/** �ő�Đ��p�[�g�� */
#define MUSIC_MAX_PART SOUND_MAX_PRONOUNCE

/** �S���� */
#define MUSIC_L0 768
/** 2������ */
#define MUSIC_L2 384
/** 4������ */
#define MUSIC_L4 192
/** 8������ */
#define MUSIC_L8 96
/** 16������ */
#define MUSIC_L16 48
/** 32������ */
#define MUSIC_L32 24
/** 64������ */
#define MUSIC_L64 12
/** 128������ */
#define MUSIC_L128 6
/** 3�A�� */
#define MUSIC_L3C 64
/** 6�A�� */
#define MUSIC_L6C 32


/**
 * @brief �Đ���ԃ��e�����^
 */
typedef enum
{
    MUSIC_ST_STOP = 0,
    MUSIC_ST_PLAY,
    MUSIC_ST_REVERSE,
    MUSIC_ST_PAUSE,
#ifdef USE_MUSIC_RECORD
    MUSIC_ST_RECORD,
#endif /* USE_MUSIC_RECORD */

    MUSIC_NUM_OF_STATE
} MUSIC_State;

/**
 * @brief ������`�^
 *
 * �P���̉��K�A���F�A�������`����^�B
 */
typedef struct
{
    SOUND_Tone tone;
    /**< ���������鉹�f�[�^(���K�A���F) */
    _UDWORD begin;
    /**< �������J�n����y�ȃJ�E���g�l(��Βl) */
    _UWORD len;
    /**< �����Bbegin����̑��Βl */
} MUSIC_Note;

/**
 * @brief �p�[�g��`�^
 *
 * �����̉����񂩂琬��P�p�[�g���`����^
 */
typedef struct
{
    MUSIC_Note* notes;
    /** �����f�[�^�� */
    _UWORD size;
    /** �����f�[�^��̌� */
} MUSIC_Part;

/**
 * @brief �y����`�^
 *
 * �����̃p�[�g���琬��ŏI�I�ȉ��t�y�Ȃ�\���y�����`����^
 */
typedef struct
{
    MUSIC_Part* parts;
    /** �p�[�g�f�[�^�� */
    _UWORD size;
    /** �p�[�g�f�[�^��̌� */
} MUSIC_Score;

/**
 * @brief �Đ��ʒu
 *
 * �Đ��ʒu���̒�`
 */
typedef struct
{
    _UWORD note[MUSIC_MAX_PART];
    /**< �p�[�g���̉����f�[�^��̈ʒu */
    _UDWORD count;
    /**< �y�Ȃ̍Đ��J�E���g */
} MUSIC_Position;

/**
 * @brief �Đ����샊�N�G�X�gAPI�̌^
 */
typedef _BOOL (*MUSIC_Api)();

/**
 * @brief ��ԃn���h���z��
 *
 * ���̔z��ɍĐ���ԃ��e�������C���f�b�N�X�Ƃ��ė^����΁A���e�����l
 * �ɉ������n���h�����Ă΂��B
 *
 * @see MUSIC_State
 */
extern const MUSIC_Api MUSIC_state_handler[MUSIC_NUM_OF_STATE];

/**
 * @brief ������
 *
 * �T�E���h�h���C�o�������������W���[�����g�p�\�ɂ���B
 * ��API�g�p�O�ɕK�����s����B
 */
void MUSIC_init();

/**
 * @brief ���݂̍Đ���Ԏ擾
 *
 * @return �Đ���ԃ��e����
 */
MUSIC_State MUSIC_getState();

/**
 * @brief �e���|�ݒ�
 *
 * �Đ����x��ݒ肷��B0�`MUSIC_MAX_TEMPO
 * ���ł��ݒ�\�B
 *
 * @param[in] val �e���|�l
 *
 * @bug ����API�͖������B�Ăяo���ƃn���O�A�b�v����B
 */
void MUSIC_setTempo(_UBYTE val);

/**
 * @brief �Đ����[�v�ݒ�
 *
 * ���[�v�Đ����邩�ǂ�����ݒ肷��B�f�t�H���g�̓I�t�B
 * ���ł��ݒ�\�B
 *
 * @param[in] val TRUE:���[�v����BFALSE:���[�v���Ȃ�
 */
void MUSIC_setLoop(_BOOL val);

/**
 * @brief �Đ��ʒu�擾
 *
 * ���݂̍Đ��ʒu���擾����B
 *
 * @param[out] pos �Đ����̃|�W�V���������i�[����̈�ւ̃|�C���^
 */
void MUSIC_getPosition(MUSIC_Position* pos);

/**
 * @brief �Đ��ʒu�ݒ�
 *
 * �Đ��ʒu���w��l�֕ύX����B���ł��ݒ�\�B
 *
 * @param[in] pos �Đ��ʒu���f�[�^�ւ̃|�C���^
 */
void MUSIC_setPosition(const MUSIC_Position* pos);

/**
 * @brief �y�ȓo�^
 *
 * �Đ�����y�Ȃ�o�^����B
 *
 * @param[in] score �y�ȃf�[�^
 */
void MUSIC_setScore(const MUSIC_Score* score);

/**
 * @brief �y�Ȏ擾
 *
 * ���ݓo�^/�^������Ă���y�ȃf�[�^���擾����B
 *
 * @return �y�ȃf�[�^�ւ̃|�C���^
 */
const MUSIC_Score* MUSIC_getScore();

/**
 * @brief �y�ȍĐ����N�G�X�g
 *
 * �o�^/�^������Ă���y�Ȃ����ɍĐ�������B
 *
 * @retval TRUE ���N�G�X�g���
 * @retval FALSE ���N�G�X�g����
 */
_BOOL MUSIC_play();

/**
 * @brief �y�ȋt�Đ����N�G�X�g
 *
 * �o�^/�^������Ă���y�Ȃ��t����Đ�������B
 *
 * @retval TRUE ���N�G�X�g���
 * @retval FALSE ���N�G�X�g����
 */
_BOOL MUSIC_reverse();

/**
 * @brief �y�Ȉꎞ��~���N�G�X�g
 *
 * �Đ����̊y�Ȃ��ꎞ��~������B
 *
 * @retval TRUE ���N�G�X�g���
 * @retval FALSE ���N�G�X�g����
 */
_BOOL MUSIC_pause();

/**
 * @brief �y�Ȓ�~���N�G�X�g
 *
 * �Đ����̊y�Ȃ��~������B����Đ����͐擪����ɂȂ�B
 *
 * @retval TRUE ���N�G�X�g���
 * @retval FALSE ���N�G�X�g����
 */
_BOOL MUSIC_stop();

/**
 * @brief �y�ȉ��t/�^��
 *
 * ���t���(MUSIC_play�AMUSIC_reverse)�������͘^�����(MUSIC_record)��
 * ����ꍇ�A����API���ĂԂ��ƂŊy�Ȃ̉��t/�^�������s�����B�����ł�
 * �Ăяo���񐔂�����(MUSIC_Note::len)�Ƃ��ăJ�E���g����Ă���A�����y
 * ����ǂݐi�߂Ȃ��特�̍Đ����s���Ă���B�Ȃ̂ŁA�ʏ��TimerA���荞
 * �݃n���h������Ă΂��悤�ɂ��Ă����΂悢�B
 */
void MUSIC_render();

#ifdef USE_MUSIC_RECORD

/** �^���ł��鉹���̐� */
#ifdef NDEBUG
#define MUSIC_NOTE_OF_RECORD_PART 37
#else
#define MUSIC_NOTE_OF_RECORD_PART 5
#endif /* NDEBUG */

/** �^�����N�G�X�gID�^ */
typedef _UWORD MUSIC_RecordReqId;
/** �^�����N�G�X�gID�̖����l */
#define MUSIC_RECREQID_INVALID 0

/**
 * @brief �y�Ș^�����N�G�X�g
 *
 * �y�Ȃ̘^�����J�n����B�Ȍ�A���̑���API(MUSIC_play, MUSIC_reverse,
 * MUSIC_stop)���Ăяo�����܂Ř^�����[�h�ƂȂ�A���̘^�����󂯕t����B
 * �܂��A���ݓo�^����Ă���y�Ȃ͔j�������B���̊y�ȍĐ����͘^���ł�
 * �Ȃ��B
 *
 * @retval TRUE ���N�G�X�g���
 * @retval FALSE ���N�G�X�g����
 */
_BOOL MUSIC_record();

/**
 * @brief �^���J�n
 *
 * �w�艹�̋L�^���J�n����B���̌��~���N�G�X�g�����s����邱�Ƃŉ���
 * ���m�肵�����Ƃ��ēo�^�����B
 *
 * @param[in] tone �^�����鉹�f�[�^�ւ̃|�C���^�Btone->freq�ɉ��K���Z�b
 * �g���Ă����B���K��0�A��������tone->evlp��NULL�̃f�[�^�͎󂯂����
 * �Ȃ��B
 *
 * @return ���N�G�X�gID
 * @retval MUSIC_RECREQID_INVALID �^���\���̌��E�ɒB����
 *
 * @see MUSIC_recStop
 */
MUSIC_RecordReqId MUSIC_recStart(const SOUND_Tone* tone);

/**
 * @brief �^����~
 *
 * �w�艹�̋L�^���~����B�J�n����̎��Ԃ��J�E���g����A�������m�肷
 * ��B
 *
 * @param[in] id ��~����^���̃��N�G�X�gID
 *
 * @retval �^�����ꂽ�����f�[�^�ւ̃|�C���^
 * @retval NULL ���N�G�X�gID���s��
 */
const MUSIC_Note* MUSIC_recStop(MUSIC_RecordReqId id);

#endif /* USE_MUSIC_RECORD */

#ifdef __cplusplus
}
#endif

#endif /* MUSIC_H_ */
