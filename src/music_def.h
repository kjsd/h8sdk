/**
 * @file music_def.h
 *
 * @brief �y�ȉ��t���W���[���̓����݌v
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
#ifndef MUSIC_DEF_H_
#define MUSIC_DEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "../include/h8sdk/stddef.h"
#include "../include/h8sdk/stdlib.h"
#include "../include/h8sdk/assert.h"
#include "../include/h8sdk/string.h"
#include "../include/h8sdk/envelope.h"
#include "../include/h8sdk/music.h"

/** �Đ��p�[�g�f�[�^�擾 */
#define PART_(x) (score_->parts[(x)])
/** �Đ����f�[�^�擾 */
#define NOTE_(x) (PART_(x).notes[position_.note[(x)]])

/** ������ԑJ�ڃ}�g���b�N�X */
static const _BOOL state_mtx_[MUSIC_NUM_OF_STATE][MUSIC_NUM_OF_STATE];
/** ���݂̓������ */
static MUSIC_State current_state_;

/** �Đ�����y�Ȃւ̃|�C���^ */
static MUSIC_Score* score_;
/** �y�ȍĐ����[�v�t���O */
static _BOOL loop_;
/** ���݂̊y�ȍĐ��ʒu��� */
static MUSIC_Position position_;

/** 
 * @brief �Đ��I���p�[�g���ʃt���O
 *
 * LSB���珇�Ƀp�[�g1,�p�[�g2...�̍Đ��I����Ԃ��r�b�g�ŕ\���B
 * �I�����Ă���Ȃ�r�b�g�����B
 */
static _UWORD part_finish_;
/** 
 * @brief �p�[�g�Đ�����Ԏ��ʃt���O
 *
 * LSB���珇�Ƀp�[�g1,�p�[�g2...�̍Đ���Ԃ��r�b�g�ŕ\���B
 * �Đ����Ȃ�΃r�b�g�����B
 */
static _UWORD part_pronounce_;

/** �^�C�}���荞�ݎ��ɌĂ΂�������ԃn���h���e�[�u�� */
static const void (*state_handle_tbl_[MUSIC_NUM_OF_STATE])();


/** 
 * @brief �Đ��I������
 *
 * �S�Ă̊y�ȃp�[�g�̍Đ��I���`�F�b�N���s���A�I������������B
 *
 * @retval _TRUE �S�p�[�g�y�ȍĐ��I���ς�
 * @retval _FALSE �Đ����I�����Ă��Ȃ��p�[�g������
 */
static _BOOL playFinalize_(MUSIC_State prev);

/** 
 * @brief ��~��ԃn���h��
 *
 * ������Ԃ�MUSIC_ST_STOP���Ƀ^�C�}���荞�݂���Ă΂��n���h��
 *
 * @see MUSIC_State, state_handle_tbl_
 */
static void stStopHandle_();
/** 
 * @brief �Đ���ԃn���h��
 *
 * ������Ԃ�MUSIC_ST_PLAY���Ƀ^�C�}���荞�݂���Ă΂��n���h��
 *
 * @see MUSIC_State, state_handle_tbl_
 */
static void stPlayHandle_();
/** 
 * @brief �t�Đ���ԃn���h��
 *
 * ������Ԃ�MUSIC_ST_REVERSE���Ƀ^�C�}���荞�݂���Ă΂��n���h��
 *
 * @see MUSIC_State, state_handle_tbl_
 */
static void stReverseHandle_();
/** 
 * @brief �ꎞ��~��ԃn���h��
 *
 * ������Ԃ�MUSIC_ST_PAUSE���Ƀ^�C�}���荞�݂���Ă΂��n���h��
 *
 * @see MUSIC_State, state_handle_tbl_
 */
static void stPauseHandle_();


#ifdef USE_MUSIC_RECORD
/**
 * @brief �^���p�p�����[�^��`
 *
 * �^�����̏����Ɏg����f�[�^�^
 */
typedef struct
{
    MUSIC_RecordReqId reqid;
    /**< �^�����N�G�X�gID */
    _UWORD part_idx;
    /**< �^�����̃p�[�g�Brec_parts_�̃C���f�b�N�X */
    _UWORD note_idx;
    /**< �^�����̉��f�[�^�Brec_notes_[part_idx]�̃C���f�b�N�X */
} RecordParam_;

/** �^���p�y�� */
static MUSIC_Score rec_score_;
/** �^���p�y�ȃp�[�g */
static MUSIC_Part rec_parts_[MUSIC_MAX_PART];
/** �^���p�y�Ȃ̉��f�[�^ */
static MUSIC_Note rec_notes_[MUSIC_MAX_PART][MUSIC_NOTE_OF_RECORD_PART];
/** �^���p�p�����[�^ */
static RecordParam_ rec_param_[MUSIC_MAX_PART];
/** �^���ʒu��� */
static MUSIC_Position rec_position_;
/** �^���p�[�g��� */
static _UWORD rec_part_;

/** 
 * @brief �^���J�n�f�[�^�o�^
 *
 * �w�肳�ꂽ���f�[�^�̘^�����J�n����B�Ȍ�A�^�C�}�n���h���ɂ����
 * ���̃f�[�^�̉������J�E���g�A�b�v����Ă����B
 *
 * @param[in] tone �o�^����^���f�[�^
 *
 * @return ���N�G�X�gID
 * @retval MUSIC_RECREQID_INVALID �^�����E�ɒB����
 *
 * @see MUSIC_recStart, deleteRecordNote_ 
 */
static MUSIC_RecordReqId newRecordNote_(const SOUND_Tone* tone);

/** 
 * @brief �^���J�n�f�[�^�폜
 *
 * �w�肳�ꂽ���f�[�^�̘^�����~���A�o�^���폜����B
 *
 * @param[in] key �폜����^���̃��N�G�X�gID
 *
 * @retval �^�����ꂽ�����f�[�^�ւ̃|�C���^
 * @retval NULL ���N�G�X�gID���s��
 *
 * @see MUSIC_recStop, newRecordNote_
 */
static MUSIC_Note* deleteRecordNote_(MUSIC_RecordReqId key);

/** 
 * @brief �^����ԃn���h��
 *
 * ������Ԃ�MUSIC_ST_RECORD���Ƀ^�C�}���荞�݂���Ă΂��n���h��
 *
 * @see MUSIC_State, state_handle_tbl_
 */
static void stRecordHandle_();

#endif /* USE_MUSIC_RECORD */

#ifdef __cplusplus
}
#endif

#endif /* MUSIC_DEF_H_ */
