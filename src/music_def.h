/**
 * @file music_def.h
 *
 * @brief 楽曲演奏モジュールの内部設計
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

/** 再生パートデータ取得 */
#define PART_(x) (score_->parts[(x)])
/** 再生音データ取得 */
#define NOTE_(x) (PART_(x).notes[position_.note[(x)]])

/** 内部状態遷移マトリックス */
static const _BOOL state_mtx_[MUSIC_NUM_OF_STATE][MUSIC_NUM_OF_STATE];
/** 現在の内部状態 */
static MUSIC_State current_state_;

/** 再生する楽曲へのポインタ */
static MUSIC_Score* score_;
/** 楽曲再生ループフラグ */
static _BOOL loop_;
/** 現在の楽曲再生位置情報 */
static MUSIC_Position position_;

/** 
 * @brief 再生終了パート識別フラグ
 *
 * LSBから順にパート1,パート2...の再生終了状態をビットで表す。
 * 終了しているならビットが立つ。
 */
static _UWORD part_finish_;
/** 
 * @brief パート再生中状態識別フラグ
 *
 * LSBから順にパート1,パート2...の再生状態をビットで表す。
 * 再生中ならばビットが立つ。
 */
static _UWORD part_pronounce_;

/** タイマ割り込み時に呼ばれる内部状態ハンドラテーブル */
static const void (*state_handle_tbl_[MUSIC_NUM_OF_STATE])();


/** 
 * @brief 再生終了処理
 *
 * 全ての楽曲パートの再生終了チェックを行い、終了処理をする。
 *
 * @retval _TRUE 全パート楽曲再生終了済み
 * @retval _FALSE 再生が終了していないパートがある
 */
static _BOOL playFinalize_(MUSIC_State prev);

/** 
 * @brief 停止状態ハンドラ
 *
 * 内部状態がMUSIC_ST_STOP時にタイマ割り込みから呼ばれるハンドラ
 *
 * @see MUSIC_State, state_handle_tbl_
 */
static void stStopHandle_();
/** 
 * @brief 再生状態ハンドラ
 *
 * 内部状態がMUSIC_ST_PLAY時にタイマ割り込みから呼ばれるハンドラ
 *
 * @see MUSIC_State, state_handle_tbl_
 */
static void stPlayHandle_();
/** 
 * @brief 逆再生状態ハンドラ
 *
 * 内部状態がMUSIC_ST_REVERSE時にタイマ割り込みから呼ばれるハンドラ
 *
 * @see MUSIC_State, state_handle_tbl_
 */
static void stReverseHandle_();
/** 
 * @brief 一時停止状態ハンドラ
 *
 * 内部状態がMUSIC_ST_PAUSE時にタイマ割り込みから呼ばれるハンドラ
 *
 * @see MUSIC_State, state_handle_tbl_
 */
static void stPauseHandle_();


#ifdef USE_MUSIC_RECORD
/**
 * @brief 録音用パラメータ定義
 *
 * 録音時の処理に使われるデータ型
 */
typedef struct
{
    MUSIC_RecordReqId reqid;
    /**< 録音リクエストID */
    _UWORD part_idx;
    /**< 録音中のパート。rec_parts_のインデックス */
    _UWORD note_idx;
    /**< 録音中の音データ。rec_notes_[part_idx]のインデックス */
} RecordParam_;

/** 録音用楽曲 */
static MUSIC_Score rec_score_;
/** 録音用楽曲パート */
static MUSIC_Part rec_parts_[MUSIC_MAX_PART];
/** 録音用楽曲の音データ */
static MUSIC_Note rec_notes_[MUSIC_MAX_PART][MUSIC_NOTE_OF_RECORD_PART];
/** 録音用パラメータ */
static RecordParam_ rec_param_[MUSIC_MAX_PART];
/** 録音位置情報 */
static MUSIC_Position rec_position_;
/** 録音パート情報 */
static _UWORD rec_part_;

/** 
 * @brief 録音開始データ登録
 *
 * 指定された音データの録音を開始する。以後、タイマハンドラによって
 * このデータの音長がカウントアップされていく。
 *
 * @param[in] tone 登録する録音データ
 *
 * @return リクエストID
 * @retval MUSIC_RECREQID_INVALID 録音限界に達した
 *
 * @see MUSIC_recStart, deleteRecordNote_ 
 */
static MUSIC_RecordReqId newRecordNote_(const SOUND_Tone* tone);

/** 
 * @brief 録音開始データ削除
 *
 * 指定された音データの録音を停止し、登録を削除する。
 *
 * @param[in] key 削除する録音のリクエストID
 *
 * @retval 録音された音符データへのポインタ
 * @retval NULL リクエストIDが不正
 *
 * @see MUSIC_recStop, newRecordNote_
 */
static MUSIC_Note* deleteRecordNote_(MUSIC_RecordReqId key);

/** 
 * @brief 録音状態ハンドラ
 *
 * 内部状態がMUSIC_ST_RECORD時にタイマ割り込みから呼ばれるハンドラ
 *
 * @see MUSIC_State, state_handle_tbl_
 */
static void stRecordHandle_();

#endif /* USE_MUSIC_RECORD */

#ifdef __cplusplus
}
#endif

#endif /* MUSIC_DEF_H_ */
