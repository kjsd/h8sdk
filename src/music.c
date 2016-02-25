/**
 * @file music.c
 *
 * @brief äyã»ââëtÉÇÉWÉÖÅ[ÉãÇÃé¿ëï
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
#include "music_def.h"


const MUSIC_Api MUSIC_state_handler[MUSIC_NUM_OF_STATE] = {
    MUSIC_stop,
    MUSIC_play,
    MUSIC_reverse,
    MUSIC_pause,
#ifdef USE_MUSIC_RECORD
    MUSIC_record
#endif /* USE_MUSIC_RECORD */
};

static const _BOOL state_mtx_[MUSIC_NUM_OF_STATE][MUSIC_NUM_OF_STATE] = {
#ifdef USE_MUSIC_RECORD
    { _FALSE, _TRUE, _TRUE, _TRUE, _TRUE },  /* STOP */
    { _TRUE, _FALSE, _TRUE, _TRUE, _FALSE },   /* PLAY */
    { _TRUE, _TRUE, _FALSE, _TRUE, _FALSE },   /* REVERSE */
    { _FALSE, _TRUE, _TRUE, _FALSE, _FALSE }, /* PAUSE */
    { _TRUE, _TRUE, _TRUE, _FALSE, _FALSE } /* RECORD */
#else
    { _FALSE, _TRUE, _TRUE, _TRUE },  /* STOP */
    { _TRUE, _FALSE, _TRUE, _TRUE },   /* PLAY */
    { _TRUE, _TRUE, _FALSE, _TRUE },   /* REVERSE */
    { _FALSE, _TRUE, _TRUE, _FALSE }, /* PAUSE */
#endif /* USE_MUSIC_RECORD */
};

static MUSIC_State current_state_ = MUSIC_ST_STOP;
static _BOOL loop_ = _FALSE;
static MUSIC_Position position_ = { 0, { 0 }, 0 };
static MUSIC_Score* score_ = NULL;
static _UWORD part_finish_ = 0;
static _UWORD part_pronounce_ = 0;

#ifdef USE_MUSIC_RECORD
static MUSIC_Score rec_score_ = { rec_parts_, 0 };
static MUSIC_Part rec_parts_[MUSIC_MAX_PART];
static MUSIC_Note rec_notes_[MUSIC_MAX_PART][MUSIC_NOTE_OF_RECORD_PART] = {
    { { { SOUND_NA, NULL, NULL, _FALSE }, 0, 0 } }
};
static RecordParam_ rec_param_[MUSIC_MAX_PART] = {
    MUSIC_RECREQID_INVALID, 0, 0
};
static MUSIC_Position rec_position_ = { 0, { 0 }, 0 };
static _UWORD rec_part_ = 0;
#endif /* USE_MUSIC_RECORD */

static const void (*state_handle_tbl_[MUSIC_NUM_OF_STATE])() = {
    stStopHandle_,
    stPlayHandle_,
    stReverseHandle_,
    stPauseHandle_,
#ifdef USE_MUSIC_RECORD
    stRecordHandle_
#endif /* USE_MUSIC_RECORD */
};


void MUSIC_init()
{
    SOUND_init();
}

MUSIC_State MUSIC_getState()
{
    return current_state_;
}

void MUSIC_setTempo(_UBYTE val)
{
    /* T.B.D. */
    _assert(_FALSE);
}

void MUSIC_setLoop(_BOOL val)
{
    loop_ = val;
}

void MUSIC_getPosition(MUSIC_Position* pos)
{
    _assert(pos);

    *pos = position_;
}

void MUSIC_setPosition(const MUSIC_Position* pos)
{
    _assert(pos);

    position_ = *pos;
}

void MUSIC_setScore(const MUSIC_Score* score)
{
    _assert(score);

    score_ = score;
}

const MUSIC_Score* MUSIC_getScore()
{
    return score_;
}

_BOOL MUSIC_play()
{
    if (!state_mtx_[current_state_][MUSIC_ST_PLAY]) return _FALSE;

    _assert(score_);

    current_state_ = MUSIC_ST_PLAY;
    SOUND_play();

    return _TRUE;
}

_BOOL MUSIC_reverse()
{
    _SINT i, j;

    if (!state_mtx_[current_state_][MUSIC_ST_REVERSE]) return _FALSE;

    _assert(score_);

    SOUND_stop();

    if (current_state_ == MUSIC_ST_STOP)
    {
        for (i = 0; i < score_->size; i++)
        {
            position_.note[i] = PART_(i).size - 1;
            if (position_.count < (NOTE_(i).begin + NOTE_(i).len))
            {
                position_.count = (NOTE_(i).begin + NOTE_(i).len);
            }
        }
    }

    current_state_ = MUSIC_ST_REVERSE;
    SOUND_reverse();

    return _TRUE;
}

_BOOL MUSIC_pause()
{
    if (!state_mtx_[current_state_][MUSIC_ST_PAUSE]) return _FALSE;

    SOUND_stop();
    current_state_ = MUSIC_ST_PAUSE;

    return _TRUE;
}

_BOOL MUSIC_stop()
{
    _SINT i;

    if (!state_mtx_[current_state_][MUSIC_ST_STOP]) return _FALSE;

    SOUND_stop();

    for (i = 0; i < score_->size; i++)
    {
        SOUND_removeTone(i);
    }

    part_finish_ = 0;
    part_pronounce_ = 0;
    _memset(&position_, 0, sizeof(position_));
    current_state_ = MUSIC_ST_STOP;

    return _TRUE;
}

void MUSIC_render()
{
    state_handle_tbl_[current_state_]();
}

static _BOOL playFinalize_(MUSIC_State prev)
{
    if (part_finish_ == ((1U << score_->size) - 1))
    {
        MUSIC_stop();
        if (loop_)
        {
            MUSIC_state_handler[prev]();
        }

        return _TRUE;
    }
    return _FALSE;
}

static void stStopHandle_()
{
    return;
}

static void stPlayHandle_()
{
    _SINT i;

    if (playFinalize_(MUSIC_ST_PLAY)) return;

    for (i = 0; i < score_->size; i++)
    {
        if (part_finish_ & (1U << i)) continue;

        if (part_pronounce_ & (1U << i))
        {
            _BOOL tone_change = _FALSE;
            while (position_.count > (NOTE_(i).begin + NOTE_(i).len))
            {
                if (++position_.note[i] == PART_(i).size)
                {
                    part_finish_ |= (1U << i);
                    SOUND_removeTone(i);
                    tone_change = _FALSE;
                    break;
                }
                tone_change = _TRUE;
            }
            if (!tone_change) continue;

            if (position_.count >= NOTE_(i).begin)
            {
                if (NOTE_(i).tone.freq == SOUND_NA)
                {
                    SOUND_removeTone(i);
                }
                else
                {
                    SOUND_setTone(i, &NOTE_(i).tone);
                }
            }
            else
            {
                SOUND_removeTone(i);
                part_pronounce_ &= ~(1U << i);
            }
        }
        else
        {
            if (position_.count >= NOTE_(i).begin)
            {
                if (NOTE_(i).tone.freq != SOUND_NA)
                {
                    SOUND_setTone(i, &NOTE_(i).tone);
                }
                part_pronounce_ |= (1U << i);
            }
        }
    }

    position_.count++;
}

static void stReverseHandle_()
{
    _SINT i;

    if (playFinalize_(MUSIC_ST_REVERSE)) return;

    for (i = 0; i < score_->size; i++)
    {
        if (part_finish_ & (1U << i)) continue;

        if (part_pronounce_ & (1U << i))
        {
            _BOOL tone_change = _FALSE;
            while (position_.count <= NOTE_(i).begin)
            {
                if (position_.note[i]-- == 0)
                {
                    part_finish_ |= (1U << i);
                    SOUND_removeTone(i);
                    tone_change = _FALSE;
                    break;
                }
                tone_change = _TRUE;
            }
            if (!tone_change) continue;

            if (position_.count <= (NOTE_(i).begin + NOTE_(i).len))
            {
                if (NOTE_(i).tone.freq == SOUND_NA)
                {
                    SOUND_removeTone(i);
                }
                else
                {
                    SOUND_setTone(i, &NOTE_(i).tone);
                }
            }
            else
            {
                SOUND_removeTone(i);
                part_pronounce_ &= ~(1U << i);
            }
        }
        else
        {
            if (position_.count <= (NOTE_(i).begin + NOTE_(i).len))
            {
                if (NOTE_(i).tone.freq != SOUND_NA)
                {
                    SOUND_setTone(i, &NOTE_(i).tone);
                }
                part_pronounce_ |= (1U << i);
            }
        }
    }

    --position_.count;
}

static void stPauseHandle_()
{
    return;
}

#ifdef USE_MUSIC_RECORD
_BOOL MUSIC_record()
{
    _SINT i;
    SOUND_State st;

    if (!state_mtx_[current_state_][MUSIC_ST_RECORD]) return _FALSE;

    st = SOUND_getState();
    if (st != SOUND_ST_STOP)
    {
        SOUND_stop();
    }

    rec_score_.size = 0;

    for (i = 0; i < _sizeof_array(rec_parts_); i++)
    {
        rec_parts_[i].notes = rec_notes_[i];
        rec_parts_[i].size = 0;
    }
    _memset(rec_notes_, 0, sizeof(rec_notes_));
    _memset(rec_param_, 0, sizeof(rec_param_));
    _memset(&rec_position_, 0, sizeof(rec_position_));
    rec_part_ = 0;

    _memset(&position_, 0, sizeof(position_));
    score_ = &rec_score_;

    current_state_ = MUSIC_ST_RECORD;

    if (st != SOUND_ST_STOP)
    {
        SOUND_state_handler[st]();
    }
    else
    {
        SOUND_play();
    }

    return _TRUE;
}

MUSIC_RecordReqId MUSIC_recStart(const SOUND_Tone* tone)
{
    _UBYTE idx;
    MUSIC_RecordReqId reqid;
    SOUND_State st;

    _assert(tone);
    _assert(tone->evlp);
    _assert(current_state_ == MUSIC_ST_RECORD);

    return newRecordNote_(tone);
}

const MUSIC_Note* MUSIC_recStop(MUSIC_RecordReqId id)
{
    _SWORD idx;
    MUSIC_Note* p;
    SOUND_State st;

    _assert(current_state_ == MUSIC_ST_RECORD);
    _assert(id != MUSIC_RECREQID_INVALID);

    return deleteRecordNote_(id);
}

static MUSIC_RecordReqId newRecordNote_(const SOUND_Tone* tone)
{
    static _UWORD req_id = 1;
    _SINT i;
    _UBYTE idx;
    _UWORD size = _sizeof_array(rec_param_);

    idx = _hash(req_id, size);
    while (size--)
    {
        if (rec_param_[idx].reqid == MUSIC_RECREQID_INVALID)
        {
            if (rec_position_.note[rec_part_] == MUSIC_NOTE_OF_RECORD_PART)
            {
                return MUSIC_RECREQID_INVALID;
            }

            rec_param_[idx].reqid = req_id;
            rec_param_[idx].part_idx = rec_part_;
            rec_param_[idx].note_idx = rec_position_.
                note[rec_param_[idx].part_idx];
            rec_notes_[rec_param_[idx].part_idx][rec_param_[idx].note_idx].
                begin = rec_position_.count;

            _memcpy(&rec_notes_[rec_param_[idx].part_idx]
                    [rec_param_[idx].note_idx].tone,
                    tone,
                    sizeof(SOUND_Tone));

            rec_part_++;
            rec_position_.note[rec_param_[idx].part_idx]++;

            rec_parts_[rec_param_[idx].part_idx].size++;
            if (rec_score_.size < rec_part_)
            {
                rec_score_.size = rec_part_;
            }

            if (++req_id == MUSIC_RECREQID_INVALID)
            {
                req_id++;
            }
            return rec_param_[idx].reqid;
        }

        idx = _next_ring(idx, _sizeof_array(rec_param_) - 1);
    }

    return MUSIC_RECREQID_INVALID;
}

static MUSIC_Note* deleteRecordNote_(MUSIC_RecordReqId key)
{
    _UBYTE idx;
    _UWORD size = _sizeof_array(rec_param_);

    idx = _hash(key, size);
    while (size--)
    {
        if (rec_param_[idx].reqid == key)
        {
            rec_param_[idx].reqid = MUSIC_RECREQID_INVALID;
            --rec_part_;

            return &rec_notes_[rec_param_[idx].part_idx]
                [rec_param_[idx].note_idx];
        }

        idx = _next_ring(idx, _sizeof_array(rec_param_) - 1);
    }

    return NULL;
}

static void stRecordHandle_()
{
    _SINT i;

    rec_position_.count++;

    for (i = 0; i < _sizeof_array(rec_param_); i++)
    {
        if (rec_param_[i].reqid != MUSIC_RECREQID_INVALID)
        {
            rec_notes_[rec_param_[i].part_idx][rec_param_[i].note_idx].len++;
        }
    }
}

#endif /* USE_MUSIC_RECORD */

