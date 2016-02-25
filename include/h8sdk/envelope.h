/**
 * @file envelope.h
 *
 * @brief エンベロープデータ定義
 *
 * 各種エンベロープの時系列変化データが定義されている。
 * 192個で4分音符分
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
 * @brief 無音
 */
extern const SOUND_Envelope ENVELOPE_na;

/**
 * @brief ピアノ
 */
extern const SOUND_Envelope ENVELOPE_piano;

/**
 * @brief リバーブ(ピアノ)
 */
extern const SOUND_Envelope ENVELOPE_piano_reverb;

/**
 * @brief フルート
 */
extern const SOUND_Envelope ENVELOPE_flute;

/**
 * @brief リバーブ(フルート)
 */
extern const SOUND_Envelope ENVELOPE_flute_reverb;

/**
 * @brief ドラム
 */
extern const SOUND_Envelope ENVELOPE_drum;

/**
 * @brief トランペット
 */
extern const SOUND_Envelope ENVELOPE_trumpet;

/**
 * @brief リバーブ(トランペット)
 */
extern const SOUND_Envelope ENVELOPE_trumpet_reverb;

/**
 * @brief ハープ
 */
extern const SOUND_Envelope ENVELOPE_harp;

/**
 * @brief リバーブ(ハープ)
 */
extern const SOUND_Envelope ENVELOPE_harp_reverb;

#ifdef __cplusplus
}
#endif

#endif /* ENVELOPE_H */
