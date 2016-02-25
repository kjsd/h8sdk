/**
 * @file sound.h
 *
 * @brief サウンドドライバ
 *
 * このモジュールは音を再生させるためのインタフェースを提供する。@n
 * H8-BASE2で使用できる3つのタイマを使い、音程、音長、強弱を表わす矩形波を
 * スピーカポートへ出力する。
 *
 * @attention TimerA, TimerV, TimerWを他のモジュールで使用してはならない。
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

/** 最大同時発信音数 */
#define SOUND_MAX_PRONOUNCE 3
/** ボリュームの最大値 */
#define SOUND_MAX_VOLUME 255

#define SOUND_PRONOUNCE_LEN 2

/** 無音 */
#define SOUND_NA 0
/** オクターブ0 ド */
#define SOUND_C0 255
/** オクターブ0 ド# */
#define SOUND_Cb0 241
/** オクターブ0 レ */
#define SOUND_D0 228
/** オクターブ0 レ# */
#define SOUND_Db0 214
/** オクターブ0 ミ */
#define SOUND_E0 203
/** オクターブ0 ファ */
#define SOUND_F0 192
/** オクターブ0 ファ# */
#define SOUND_Fb0 180
/** オクターブ0 ソ */
#define SOUND_G0 171
/** オクターブ0 ソ# */
#define SOUND_Gb0 161
/** オクターブ0 ラ */
#define SOUND_A0 152
/** オクターブ0 ラ# */
#define SOUND_Ab0 143
/** オクターブ0 シ */
#define SOUND_H0 136
/** オクターブ1 ド */
#define SOUND_C1 128
/** オクターブ1 ド# */
#define SOUND_Cb1 120
/** オクターブ1 レ */
#define SOUND_D1 114
/** オクターブ1 レ# */
#define SOUND_Db1 107
/** オクターブ1 ミ */
#define SOUND_E1 101
/** オクターブ1 ファ */
#define SOUND_F1 96
/** オクターブ1 ファ# */
#define SOUND_Fb1 90
/** オクターブ1 ソ */
#define SOUND_G1 85
/** オクターブ1 ソ# */
#define SOUND_Gb1 80
/** オクターブ1 ラ */
#define SOUND_A1 76
/** オクターブ1 ラ# */
#define SOUND_Ab1 72
/** オクターブ1 シ */
#define SOUND_H1 68
/** オクターブ2 ド */
#define SOUND_C2 64
/** オクターブ2 ド# */
#define SOUND_Cb2 60
/** オクターブ2 レ */
#define SOUND_D2 57
/** オクターブ2 レ# */
#define SOUND_Db2 54
/** オクターブ2 ミ */
#define SOUND_E2 51
/** オクターブ2 ファ */
#define SOUND_F2 48
/** オクターブ2 ファ# */
#define SOUND_Fb2 45
/** オクターブ2 ソ */
#define SOUND_G2 43
/** オクターブ2 ソ# */
#define SOUND_Gb2 40
/** オクターブ2 ラ */
#define SOUND_A2 38
/** オクターブ2 ラ# */
#define SOUND_Ab2 36
/** オクターブ2 シ */
#define SOUND_H2 34
/** オクターブ3 ド */
#define SOUND_C3 32
/** オクターブ3 ド# */
#define SOUND_Cb3 30
/** オクターブ3 レ */
#define SOUND_D3 29
/** オクターブ3 レ# */
#define SOUND_Db3 27
/** オクターブ3 ミ */
#define SOUND_E3 25
/** オクターブ3 ファ */
#define SOUND_F3 24
/** オクターブ3 ファ# */
#define SOUND_Fb3 23
/** オクターブ3 ソ */
#define SOUND_G3 21
/** オクターブ3 ソ# */
#define SOUND_Gb3 20
/** オクターブ3 ラ */
#define SOUND_A3 19
/** オクターブ3 ラ# */
#define SOUND_Ab3 18
/** オクターブ3 シ */
#define SOUND_H3 17


/**
 * @brief 再生状態リテラル型
 */
typedef enum
{
    SOUND_ST_STOP = 0,
    SOUND_ST_PLAY,
    SOUND_ST_REVERSE,

    SOUND_NUM_OF_STATE
} SOUND_State;

/**
 * @brief エンベロープ定義型
 *
 * 音発生時の強弱レベルを定義する型
 */
typedef struct
{
    _UBYTE* data;
    /**< エンベロープデータ列の先頭へのポインタ */
    _UWORD size;
    /**< エンベロープデータ列のサイズ */
} SOUND_Envelope;

/**
 * @brief 音定義型
 *
 * あるタイミングでの発生音を定義する型
 */
typedef struct
{
    _UBYTE freq;
     /**< 音の周波数 */
    SOUND_Envelope* evlp;
     /**< この音を発生させるときのエンベロープ */
    SOUND_Envelope* reverb;
     /**< 再生後の残響効果。リバーブ */
    _BOOL loop;
     /**< リバーブのループフラグ */
} SOUND_Tone;

/**
 * @brief 再生操作リクエストAPIの型
 */
typedef _BOOL (*SOUND_Api)();

/**
 * @brief 状態ハンドラ配列
 *
 * この配列に再生状態リテラルをインデックスとして与えれば、リテラルに応じた
 * ハンドラが呼ばれる。
 *
 * @see SOUND_State
 */
extern const SOUND_Api SOUND_state_handler[SOUND_NUM_OF_STATE];

/**
 * @brief サウンドドライバ初期化
 *
 * タイマとポートの初期化を行う。他API使用前に必ず実行する。
 */
void SOUND_init();

/**
 * @brief 現在の再生状態取得
 *
 * @return 再生状態リテラル
 */
SOUND_State SOUND_getState();

/**
 * @brief ボリューム設定
 *
 * 再生音量を設定する。0～SOUND_MAX_VOLUME
 * いつでも設定可能。
 *
 * @param[in] val ボリューム値
 */
void SOUND_setVolume(_UBYTE val);

/**
 * @brief エンベロープ周期設定
 *
 * エンベロープをセットする周期を設定する。
 * この設定値は再生音質とボリューム調節の細かさに影響し、両者はトレードオフの
 * 関係にある。初期値は256。
 *
 * @param[in] val 設定値
 */
void SOUND_setEvlpCycle(_UWORD val);

/**
 * @brief 音登録
 *
 * 音を登録する。SOUND_MAX_PRONOUNCE個のバンクに同時にセットすることができる。
 * いつでも設定可能。
 *
 * @param[in] idx バンクのインデックス。0～SOUND_MAX_PRONOUNCE-1
 * @param[in] tone 設定するSOUND_Toneへのポインタ @n
 * 無音(SOUND_Tone::freq == 0)、またはSOUND_Tone::evlpがNULLのデータを
 * 登録することはできない。
 */
void SOUND_setTone(_UBYTE idx, const SOUND_Tone* tone);

/**
 * @brief 音削除
 *
 * バンクを指定して設定された音を削除する。
 * いつでも設定可能。
 *
 * @param[in] idx 削除するバンクのインデックス。0～SOUND_MAX_PRONOUNCE-1
 */
void SOUND_removeTone(_UBYTE idx);

/**
 * @brief 音再生リクエスト
 *
 * 音の再生。エンベロープは順方向。
 *
 * @retval _TRUE リクエスト受諾
 * @retval _FALSE リクエスト拒否
 */
_BOOL SOUND_play();

/**
 * @brief 音逆再生リクエスト
 *
 * 音の再生。エンベロープは逆方向。
 *
 * @retval _TRUE リクエスト受諾
 * @retval _FALSE リクエスト拒否
 */
_BOOL SOUND_reverse();

/**
 * @brief 停止リクエスト
 *
 * 再生中の音を停止させる。
 *
 * @retval _TRUE リクエスト受諾
 * @retval _FALSE リクエスト拒否
 */
_BOOL SOUND_stop();

/**
 * @brief 波形生成
 *
 * SOUND_pronounceにより解析された音情報により実際に矩形波を生成させる。
 * TimerV割り込みハンドラからこのAPIを呼ぶ必要がある。割り込みフラグは内部で
 * クリアしている。
 *
 * @see 
 */
void SOUND_makePulse();

/**
 * @brief 音データ発音
 *
 * 波形生成のためのタイマカウント情報などを設定する。
 * TimerA割り込みハンドラからこのAPIを呼ぶ必要がある。割り込みフラグはクリア
 * されない。
 */
void SOUND_pronounce();

#ifdef __cplusplus
}
#endif

#endif /* SOUND_H_ */
