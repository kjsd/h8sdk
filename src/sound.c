/**
 * @file sound.c
 *
 * @brief サウンドドライバ
 *
 * サウンドドライバの実装
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
#include "../include/h8sdk/stdlib.h"
#include "../include/h8sdk/assert.h"
#include "../include/h8sdk/3694s.h"
#include "../include/h8sdk/ioctl.h"
#include "../include/h8sdk/sound.h"

#define IS_PLAYING_STATE_(x)                       \
    ((x) == SOUND_ST_PLAY || ((x) == SOUND_ST_REVERSE))

#define START_TIMER_                            \
    do                                          \
    {                                           \
        /* TCAリセット */                       \
        _TA.TMA.BIT.CKSI = 0xc;                 \
        _TW.TCNT = 0;                           \
        _TV.TCNTV = 0;                          \
        _TA.TMA.BIT.CKSI = 0x5;                 \
        _IENR1.BIT.IENTA = 1;                   \
        _TV.TCRV0.BIT.CMIEB = 1;                \
        _TV.TCRV0.BIT.CMIEA = 1;                \
    }                                           \
    while (_FALSE)

#define STOP_TIMER_                             \
    do                                          \
    {                                           \
        _TW.TMRW.BIT.PWMC = 0;                  \
        _TV.TCRV0.BIT.CMIEA = 0;                \
        _TV.TCRV0.BIT.CMIEB = 0;                \
        _IENR1.BIT.IENTA = 0;                   \
        _TW.TMRW.BIT.CTS = 0;                   \
        _IRR1.BIT.IRRTA = 0;                    \
        _TV.TCSRV.BIT.CMFA = 0;                 \
        _TV.TCSRV.BIT.CMFB = 0;                 \
        _TW.GRC = 0;                            \
        _TV.TCORA = 0;                          \
        _TV.TCORB = 0;                          \
    }                                           \
    while (_FALSE)

#define CLEAR_TIMER_                                                    \
    do                                                                  \
    {                                                                   \
        _TW.TMRW.BIT.CTS = 0;                                           \
        _TW.TCNT = 0;                                                   \
        _TW.GRC = evlp_;                                                \
        _TW.TMRW.BIT.CTS = 1;                                           \
        _TV.TCNTV = 0;                                                  \
        _TV.TCSRV.BIT.CMFA = 0;                                         \
        _TV.TCSRV.BIT.CMFB = 0;                                         \
        _TV.TCORA = tones_[tone_pos_].freq;                             \
        _TV.TCORB = tones_[tone_pos_].freq >> 1;                        \
    }                                                                   \
    while (_FALSE)

const SOUND_Api SOUND_state_handler[SOUND_NUM_OF_STATE] = {
    SOUND_stop,
    SOUND_play,
    SOUND_reverse
};

static SOUND_State current_state_ = SOUND_ST_STOP;
static SOUND_Tone tones_[SOUND_MAX_PRONOUNCE] ={
    { SOUND_NA, NULL, NULL, _FALSE }
};
static _UBYTE tone_pos_ = 0;
static _UWORD evlp_pos_[SOUND_MAX_PRONOUNCE] = { 0 };
static _BOOL is_reverb_[SOUND_MAX_PRONOUNCE] = { _FALSE };
static _BOOL remove_tone_[SOUND_MAX_PRONOUNCE] = { _FALSE };
static _UWORD evlp_ = 0;
static _UBYTE num_of_tones_ = 0;
static float volume_ = 1;
static _UWORD pronounce_cnt_ = 0;

static const _BOOL state_mtx_[SOUND_NUM_OF_STATE][SOUND_NUM_OF_STATE] = {
    { _FALSE, _TRUE, _TRUE }, /* STOP */
    { _TRUE, _FALSE, _TRUE },  /* PLAY */
    { _TRUE, _TRUE, _FALSE },  /* REVERSE */
};

static void setNextEvlp_();
static void deleteTone_(_UBYTE idx);


void SOUND_init()
{
    /* TimerW */
    IOCTL_set(IOCTL_REG_PCR8, 0x08, 0x08);
    _IO.PDR8.BIT.B3 = 0;
    _TW.TMRW.BIT.CTS = 0;
    _TW.TMRW.BIT.PWMC = 0;
    _TW.TCRW.BIT.CCLR = 1;
    _TW.TCRW.BIT.CKS = 0;
    _TW.TCRW.BIT.TOC = 1;
    _TW.TIOR1.BYTE = 0;
    _TW.GRA = 0x100;

    /* TimerV */
    _TV.TCSRV.BYTE = 0x06;
    _TV.TCRV1.BYTE = 0xe3;
    _TV.TCRV0.BYTE = 0x0b;
}

SOUND_State SOUND_getState()
{
    return current_state_;
}

void SOUND_setVolume(_UBYTE val)
{
    volume_ = (float)(val << 2) / (float)SOUND_MAX_VOLUME;
}

void SOUND_setEvlpCycle(_UWORD val)
{
    if (val != 0)
    {
        _TW.GRA = val;
    }
}

void SOUND_setTone(_UBYTE idx, const SOUND_Tone* tone)
{
    _assert(idx < SOUND_MAX_PRONOUNCE);
    _assert(tone != NULL);
    _assert((tone->freq != SOUND_NA) && (tone->evlp != NULL));

    STOP_TIMER_;

    if (tones_[idx].freq == SOUND_NA)
    {
        num_of_tones_++;
    }
    tones_[idx] = *tone;
    is_reverb_[idx] = _FALSE;
    remove_tone_[idx] = _FALSE;

    if (num_of_tones_ == 1)
    {
        tone_pos_ = idx;
    }

    switch (current_state_)
    {
    case SOUND_ST_PLAY:
        evlp_pos_[idx] = 0;
        if (num_of_tones_ == 1)
        {
            evlp_ = tones_[tone_pos_].evlp->data[evlp_pos_[tone_pos_]] *
                volume_;
        }

        CLEAR_TIMER_;
        START_TIMER_;
        break;

    case SOUND_ST_REVERSE:
        evlp_pos_[idx] = tones_[idx].evlp->size - 1;
        if (num_of_tones_ == 1)
        {
            evlp_ = tones_[tone_pos_].evlp->data[evlp_pos_[tone_pos_]] *
                volume_;
        }

        CLEAR_TIMER_;
        START_TIMER_;
        break;

    case SOUND_ST_STOP:
    case SOUND_NUM_OF_STATE:
    default:
        break;
    }
}

void SOUND_removeTone(_UBYTE idx)
{
    _SINT i;

    _assert(idx < SOUND_MAX_PRONOUNCE);

    if (tones_[idx].freq == SOUND_NA)
    {
        return;
    }

    switch (current_state_)
    {
    case SOUND_ST_PLAY:
        /* fallthrough */
    case SOUND_ST_REVERSE:
        if (!is_reverb_[idx] && (tones_[idx].reverb != NULL))
        {
            evlp_pos_[idx] = 0;
            is_reverb_[idx] = _TRUE;
        }

        remove_tone_[idx] = _TRUE;
        break;

    case SOUND_ST_STOP:
    case SOUND_NUM_OF_STATE:
    default:
        deleteTone_(idx);
        break;
    }
}

_BOOL SOUND_play()
{
    _SINT i;

    if (!state_mtx_[current_state_][SOUND_ST_PLAY]) return _FALSE;

    pronounce_cnt_ = 0;
    current_state_ = SOUND_ST_PLAY;
    CLEAR_TIMER_;
    START_TIMER_;

    return _TRUE;
}

_BOOL SOUND_reverse()
{
    _SINT i;

    if (!state_mtx_[current_state_][SOUND_ST_REVERSE]) return _FALSE;

    pronounce_cnt_ = 0;
    current_state_ = SOUND_ST_REVERSE;
    CLEAR_TIMER_;
    START_TIMER_;

    return _TRUE;
}

_BOOL SOUND_stop()
{
    _SINT i;

    if (!state_mtx_[current_state_][SOUND_ST_STOP]) return _FALSE;

    STOP_TIMER_;

    current_state_ = SOUND_ST_STOP;
    return _TRUE;
}

void SOUND_makePulse()
{
    if (!IS_PLAYING_STATE_(current_state_) || (num_of_tones_ == 0))
    {
        _TV.TCSRV.BIT.CMFA = 0;
        _TV.TCSRV.BIT.CMFB = 0;
        return;
    }

    if (_TV.TCSRV.BIT.CMFA)
    {
        _TV.TCSRV.BIT.CMFA = 0;
        _TW.TMRW.BIT.PWMC = evlp_ ? 1: 0;
    }
    if (_TV.TCSRV.BIT.CMFB)
    {
        _TV.TCSRV.BIT.CMFB = 0;
        _TW.TMRW.BIT.PWMC = 0;
    }
}

void SOUND_pronounce()
{
    _UWORD tcnt;
    _BOOL tone_change = _FALSE;

    if (!IS_PLAYING_STATE_(current_state_) || (num_of_tones_ == 0))
    {
        return;
    }

    if (num_of_tones_ > 1)
    {
        if (++pronounce_cnt_ == SOUND_PRONOUNCE_LEN)
        {
            _SINT i;
            for (i = 0; i < SOUND_MAX_PRONOUNCE; i++)
            {
                tone_pos_ = _next_ring(tone_pos_, SOUND_MAX_PRONOUNCE - 1);
                if (tones_[tone_pos_].evlp != NULL)
                {
                    tone_change = _TRUE;
                    break;
                }
            }
            pronounce_cnt_ = 0;
        }
    }

    setNextEvlp_();

    if (tone_change)
    {
        _TW.TMRW.BIT.PWMC = 0;
        CLEAR_TIMER_;
        _TW.TMRW.BIT.PWMC = 1;
    }
    else
    {
        if (_TW.GRA >= 0x100)
        {
            tcnt = (_TW.GRC < _TW.GRA) ? _TW.GRC: _TW.GRA;
            while (_TW.TCNT < tcnt);
        }
        _TW.GRC = evlp_;
    }
}

static void setNextEvlp_()
{
    SOUND_Envelope* p;

    p = (is_reverb_[tone_pos_]) ?
        tones_[tone_pos_].reverb: tones_[tone_pos_].evlp;

    if (p == NULL)
    {
        evlp_ = 0;
        return;
    }

    switch (current_state_)
    {
    case SOUND_ST_PLAY:
        if (evlp_pos_[tone_pos_] < p->size)
        {
            evlp_ = p->data[evlp_pos_[tone_pos_]] * volume_;
            evlp_pos_[tone_pos_] += num_of_tones_;
            return;
        }

        if (!is_reverb_[tone_pos_] && (tones_[tone_pos_].reverb != NULL))
        {
            evlp_pos_[tone_pos_] = 0;
            is_reverb_[tone_pos_] = _TRUE;
        }
        else
        {
            if (tones_[tone_pos_].loop && !remove_tone_[tone_pos_])
            {
                evlp_pos_[tone_pos_] = 0;
            }
            else
            {
                evlp_ = 0;
                deleteTone_(tone_pos_);
            }
        }
        break;

    case SOUND_ST_REVERSE:
        if (is_reverb_[tone_pos_])
        {
            if (evlp_pos_[tone_pos_] < p->size)
            {
                evlp_ = p->data[evlp_pos_[tone_pos_]] * volume_;
                evlp_pos_[tone_pos_] += num_of_tones_;
                return;
            }
        }
        else
        {
            if (evlp_pos_[tone_pos_] >= num_of_tones_)
            {
                evlp_ = p->data[evlp_pos_[tone_pos_]] * volume_;
                evlp_pos_[tone_pos_] -= num_of_tones_;
                return;
            }
        }

        if (!is_reverb_[tone_pos_] && (tones_[tone_pos_].reverb != NULL))
        {
            evlp_pos_[tone_pos_] = 0;
            is_reverb_[tone_pos_] = _TRUE;
        }
        else
        {
            if (tones_[tone_pos_].loop && !remove_tone_[tone_pos_])
            {
                evlp_pos_[tone_pos_] = tones_[tone_pos_].evlp->size - 1;
            }
            else
            {
                evlp_ = 0;
                deleteTone_(tone_pos_);
            }
        }
        break;

    case SOUND_ST_STOP:
    case SOUND_NUM_OF_STATE:
    default:
        _assert(_FALSE);
        break;
    }
}

static void deleteTone_(_UBYTE idx)
{
    _assert(idx < SOUND_MAX_PRONOUNCE);
    _assert((tones_[idx].freq != SOUND_NA) &&
                (tones_[idx].evlp != NULL));

    --num_of_tones_;

    tones_[idx].freq = SOUND_NA;
    tones_[idx].evlp = NULL;
    tones_[idx].reverb = NULL;
    tones_[idx].loop = _FALSE;
    evlp_ = 0;

    if ((num_of_tones_ > 0) && (tone_pos_ == idx))
    {
        _SINT i;

        for (i = 0; i < SOUND_MAX_PRONOUNCE; i++)
        {
            if (tones_[i].evlp != NULL)
            {
                tone_pos_ = i;
                CLEAR_TIMER_;
                break;
            }
        }
    }
}

