/**
 * @file music.h
 *
 * @brief 楽曲演奏モジュール
 *
 * このモジュールは楽曲の再生/録音インタフェースを提供する。@n
 * サウンドドライバ必須のため、このモジュールを使うときは、外部でサウ
 * ンドドライバの初期化をする必要はない。録音機能を有効にするときは
 * USE_MUSIC_RECORD をdefineしてコンパイルする。
 *
 * @note
 * 録音機能を有効にするためのメモリ領域は、サウンドドライバの最大同時
 * 発信音数(SOUND_MAX_PRONOUNCE)が1のときで最低36バイトのメモリ領域が
 * 必要であり、以降増える度に26バイトの領域を必要とする。これで和音を
 * 含む音符ひとつを録音可能である。@n
 * さらに、録音可能な音符(MUSIC_NOTE_OF_RECORD_PART)は、ひとつ増えるた
 * びに14バイトの領域が必要となるが、最大同時発信音数を係数として増大
 * するため、録音音符サイズ×最大同時発信音数分の領域が必要になる。以
 * 上より、録音時に必要なメモリサイズは、
 *
 * @par
 * @code
 * 10 + (10 + 14 * MUSIC_NOTE_OF_RECORD_PART) * SOUND_MAX_PRONOUNCE
 * @endcode
 *
 * @par
 * で表される。大体3和音の音符5つで250バイトほど必要になる。@n
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

/** 最大再生パート数 */
#define MUSIC_MAX_PART SOUND_MAX_PRONOUNCE

/** 全音符 */
#define MUSIC_L0 768
/** 2分音符 */
#define MUSIC_L2 384
/** 4分音符 */
#define MUSIC_L4 192
/** 8分音符 */
#define MUSIC_L8 96
/** 16分音符 */
#define MUSIC_L16 48
/** 32分音符 */
#define MUSIC_L32 24
/** 64分音符 */
#define MUSIC_L64 12
/** 128分音符 */
#define MUSIC_L128 6
/** 3連符 */
#define MUSIC_L3C 64
/** 6連符 */
#define MUSIC_L6C 32


/**
 * @brief 再生状態リテラル型
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
 * @brief 音符定義型
 *
 * 単音の音階、音色、音長を定義する型。
 */
typedef struct
{
    SOUND_Tone tone;
    /**< 発生させる音データ(音階、音色) */
    _UDWORD begin;
    /**< 発音を開始する楽曲カウント値(絶対値) */
    _UWORD len;
    /**< 音長。beginからの相対値 */
} MUSIC_Note;

/**
 * @brief パート定義型
 *
 * 複数の音符列から成る単パートを定義する型
 */
typedef struct
{
    MUSIC_Note* notes;
    /** 音符データ列 */
    _UWORD size;
    /** 音符データ列の個数 */
} MUSIC_Part;

/**
 * @brief 楽譜定義型
 *
 * 複数のパートから成る最終的な演奏楽曲を表す楽譜を定義する型
 */
typedef struct
{
    MUSIC_Part* parts;
    /** パートデータ列 */
    _UWORD size;
    /** パートデータ列の個数 */
} MUSIC_Score;

/**
 * @brief 再生位置
 *
 * 再生位置情報の定義
 */
typedef struct
{
    _UWORD note[MUSIC_MAX_PART];
    /**< パート毎の音符データ列の位置 */
    _UDWORD count;
    /**< 楽曲の再生カウント */
} MUSIC_Position;

/**
 * @brief 再生操作リクエストAPIの型
 */
typedef _BOOL (*MUSIC_Api)();

/**
 * @brief 状態ハンドラ配列
 *
 * この配列に再生状態リテラルをインデックスとして与えれば、リテラル値
 * に応じたハンドラが呼ばれる。
 *
 * @see MUSIC_State
 */
extern const MUSIC_Api MUSIC_state_handler[MUSIC_NUM_OF_STATE];

/**
 * @brief 初期化
 *
 * サウンドドライバを初期化しモジュールを使用可能にする。
 * 他API使用前に必ず実行する。
 */
void MUSIC_init();

/**
 * @brief 現在の再生状態取得
 *
 * @return 再生状態リテラル
 */
MUSIC_State MUSIC_getState();

/**
 * @brief テンポ設定
 *
 * 再生速度を設定する。0～MUSIC_MAX_TEMPO
 * いつでも設定可能。
 *
 * @param[in] val テンポ値
 *
 * @bug このAPIは未実装。呼び出すとハングアップする。
 */
void MUSIC_setTempo(_UBYTE val);

/**
 * @brief 再生ループ設定
 *
 * ループ再生するかどうかを設定する。デフォルトはオフ。
 * いつでも設定可能。
 *
 * @param[in] val TRUE:ループする。FALSE:ループしない
 */
void MUSIC_setLoop(_BOOL val);

/**
 * @brief 再生位置取得
 *
 * 現在の再生位置を取得する。
 *
 * @param[out] pos 再生中のポジション情報を格納する領域へのポインタ
 */
void MUSIC_getPosition(MUSIC_Position* pos);

/**
 * @brief 再生位置設定
 *
 * 再生位置を指定値へ変更する。いつでも設定可能。
 *
 * @param[in] pos 再生位置情報データへのポインタ
 */
void MUSIC_setPosition(const MUSIC_Position* pos);

/**
 * @brief 楽曲登録
 *
 * 再生する楽曲を登録する。
 *
 * @param[in] score 楽曲データ
 */
void MUSIC_setScore(const MUSIC_Score* score);

/**
 * @brief 楽曲取得
 *
 * 現在登録/録音されている楽曲データを取得する。
 *
 * @return 楽曲データへのポインタ
 */
const MUSIC_Score* MUSIC_getScore();

/**
 * @brief 楽曲再生リクエスト
 *
 * 登録/録音されている楽曲を順に再生させる。
 *
 * @retval TRUE リクエスト受諾
 * @retval FALSE リクエスト拒否
 */
_BOOL MUSIC_play();

/**
 * @brief 楽曲逆再生リクエスト
 *
 * 登録/録音されている楽曲を逆から再生させる。
 *
 * @retval TRUE リクエスト受諾
 * @retval FALSE リクエスト拒否
 */
_BOOL MUSIC_reverse();

/**
 * @brief 楽曲一時停止リクエスト
 *
 * 再生中の楽曲を一時停止させる。
 *
 * @retval TRUE リクエスト受諾
 * @retval FALSE リクエスト拒否
 */
_BOOL MUSIC_pause();

/**
 * @brief 楽曲停止リクエスト
 *
 * 再生中の楽曲を停止させる。次回再生時は先頭からになる。
 *
 * @retval TRUE リクエスト受諾
 * @retval FALSE リクエスト拒否
 */
_BOOL MUSIC_stop();

/**
 * @brief 楽曲演奏/録音
 *
 * 演奏状態(MUSIC_play、MUSIC_reverse)もしくは録音状態(MUSIC_record)に
 * ある場合、このAPIを呼ぶことで楽曲の演奏/録音が実行される。内部では
 * 呼び出し回数が音長(MUSIC_Note::len)としてカウントされており、逐次楽
 * 譜を読み進めながら音の再生を行っている。なので、通常はTimerA割り込
 * みハンドラから呼ばれるようにしておけばよい。
 */
void MUSIC_render();

#ifdef USE_MUSIC_RECORD

/** 録音できる音符の数 */
#ifdef NDEBUG
#define MUSIC_NOTE_OF_RECORD_PART 37
#else
#define MUSIC_NOTE_OF_RECORD_PART 5
#endif /* NDEBUG */

/** 録音リクエストID型 */
typedef _UWORD MUSIC_RecordReqId;
/** 録音リクエストIDの無効値 */
#define MUSIC_RECREQID_INVALID 0

/**
 * @brief 楽曲録音リクエスト
 *
 * 楽曲の録音を開始する。以後、他の操作API(MUSIC_play, MUSIC_reverse,
 * MUSIC_stop)が呼び出されるまで録音モードとなり、音の録音を受け付ける。
 * また、現在登録されている楽曲は破棄される。他の楽曲再生中は録音でき
 * ない。
 *
 * @retval TRUE リクエスト受諾
 * @retval FALSE リクエスト拒否
 */
_BOOL MUSIC_record();

/**
 * @brief 録音開始
 *
 * 指定音の記録を開始する。この後停止リクエストが発行されることで音長
 * が確定し音符として登録される。
 *
 * @param[in] tone 録音する音データへのポインタ。tone->freqに音階をセッ
 * トしておく。音階が0、もしくはtone->evlpがNULLのデータは受けつけられ
 * ない。
 *
 * @return リクエストID
 * @retval MUSIC_RECREQID_INVALID 録音可能数の限界に達した
 *
 * @see MUSIC_recStop
 */
MUSIC_RecordReqId MUSIC_recStart(const SOUND_Tone* tone);

/**
 * @brief 録音停止
 *
 * 指定音の記録を停止する。開始からの時間がカウントされ、音長が確定す
 * る。
 *
 * @param[in] id 停止する録音のリクエストID
 *
 * @retval 録音された音符データへのポインタ
 * @retval NULL リクエストIDが不正
 */
const MUSIC_Note* MUSIC_recStop(MUSIC_RecordReqId id);

#endif /* USE_MUSIC_RECORD */

#ifdef __cplusplus
}
#endif

#endif /* MUSIC_H_ */
