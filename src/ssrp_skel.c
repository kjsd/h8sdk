/**
 * @file ssrp_skel.c
 *
 * @version $Id: ssrp_skel.c 156 2009-03-19 08:04:25Z minoru $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * drived SSRP Skeleton.
 *
 * @component H8 development platform
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 *
 * @see <related_items>
 ***********************************************************************/
#include "ssrp_def.h"
#include "../include/h8sdk/ssrp_skel.h"


static State_ current_state_ = ST_DEALLOCATE_;
static _BOOL send_loop_ = _FALSE;
static _BOOL send_join_ = _FALSE;
static SSRP_Header header_;

static _SINT stHdlDeallocate_(TransactionState_ st, _UBYTE* buf);
static _SINT stHdlDisconnect_(TransactionState_ st, _UBYTE* buf);
static _SINT stHdlConnect_(TransactionState_ st, _UBYTE* buf);

static const _SINT (*state_handlers_[NUM_OF_STATE_])(TransactionState_ st,
                                                     _UBYTE* buf) = {
    stHdlDeallocate_,
    stHdlDisconnect_,
    stHdlConnect_
};


_SINT SSRP_SKEL_write(const _UBYTE* data, _UBYTE size,
                      _BOOL sync, _SINT tmo_ms)
{
    static TransactionState_ trst = TRXST_PREAMBLE_;

    _assert(data);

    switch (trst)
    {
    case TRXST_PREAMBLE_:
        break;

    case TRXST_HEADER_:
        if ((((SSRP_Header*)data)->command == SSRP_CMD_LOOP) &&
            (((SSRP_Header*)data)->flag == SSRP_FLG_EVT))
        {
            send_loop_ = _TRUE;
            _memcpy(&header_, data, sizeof(header_));
        }
        else if ((((SSRP_Header*)data)->command == SSRP_CMD_JOIN) &&
                 (((SSRP_Header*)data)->flag == SSRP_FLG_REQ))
        {
            current_state_ = ST_DISCONNECT_;
            send_join_ = _TRUE;
            _memcpy(&header_, data, sizeof(header_));
        }
        else if ((((SSRP_Header*)data)->command == SSRP_CMD_LEAVE) &&
                 (((SSRP_Header*)data)->flag == SSRP_FLG_EVT))
        {
            current_state_ = ST_DEALLOCATE_;
        }
        break;

    case TRXST_DATA_:
        break;

    case NUM_OF_TRXST_:
    default:
        _assert(_FALSE);
    }

    trst = _next_ring(trst, NUM_OF_TRXST_ - 1);
    return size;
}

_SINT SSRP_SKEL_read(_UBYTE* buf, _UBYTE size, _BOOL sync, _SINT tmo_ms)
{
    static TransactionState_ trst = TRXST_PREAMBLE_;
    _SINT rsize = -1;

    _assert(buf);

    rsize = state_handlers_[current_state_](trst, buf);
    if (rsize >= 0)
    {
        trst = _next_ring(trst, NUM_OF_TRXST_ - 1);
    }
    else
    {
        rsize = 0;
    }

    return rsize;
}

static _SINT stHdlDeallocate_(TransactionState_ st, _UBYTE* buf)
{
    _SINT size = 0;

    if (!send_loop_) return -1;

    switch (st)
    {
    case TRXST_PREAMBLE_:
        *buf = SSRP_VAL_PREAMBLE;
        size = 1;
        break;

    case TRXST_HEADER_:
        header_.hop++;
        header_.cksum = _check_sum(&header_,
                                   (sizeof(SSRP_Header) -
                                    sizeof(header_.cksum)) /
                                   sizeof(_UWORD));
        header_.cksum = ~(header_.cksum) + 1;
        
        _memcpy(buf, &header_, sizeof(header_));
        size = sizeof(header_);
        break;

    case TRXST_DATA_:
        *buf = 0;
        size = 1;
        send_loop_ = _FALSE;
        break;

    case NUM_OF_TRXST_:
    default:
        _assert(_FALSE);
    }

    return size;
}

static _SINT stHdlDisconnect_(TransactionState_ st, _UBYTE* buf)
{
    static _UBYTE send_join_res = 0;
    _SINT size = 0;
    SSRP_Header* p;

    if (!send_join_) return -1;

    switch (st)
    {
    case TRXST_PREAMBLE_:
        *buf = SSRP_VAL_PREAMBLE;
        size = 1;
        break;

    case TRXST_HEADER_:
        p = (SSRP_Header*)buf;
        p->from = SSRP_SKEL_LOOPBACK_ADDR;
        p->to = header_.from;
        p->command = SSRP_CMD_JOIN;
        p->flag = SSRP_FLG_RES;
        p->hop = 0;
        p->data_length = 1;
        p->cksum = _check_sum(p,
                              (sizeof(SSRP_Header) - sizeof(p->cksum)) /
                              sizeof(_UWORD));
        p->cksum = ~(p->cksum) + 1;
        size = sizeof(SSRP_Header);
        break;

    case TRXST_DATA_:
        if (send_join_res & 1U)
        {
            *buf = SSRP_CON_BACK;
            send_join_ = _FALSE;
            current_state_ = ST_CONNECT_;
        }
        else
        {
            *buf = SSRP_CON_FRONT;
        }
        size = 1;
        send_join_res++;
        break;

    case NUM_OF_TRXST_:
    default:
        _assert(_FALSE);
    }

    return size;
}

static _SINT stHdlConnect_(TransactionState_ st, _UBYTE* buf)
{
    _SINT size = 0;
    SSRP_Header* p;

    switch (st)
    {
    case TRXST_PREAMBLE_:
        *buf = SSRP_VAL_PREAMBLE;
        size = 1;
        break;

    case TRXST_HEADER_:
        p = (SSRP_Header*)buf;
        p->from = SSRP_SKEL_LOOPBACK_ADDR;
        p->to = header_.from;
        p->command = SSRP_CMD_EX;
        p->flag = SSRP_FLG_EVT;
        p->hop = 0;
        p->data_length = 1;
        p->cksum = _check_sum(p,
                              (sizeof(SSRP_Header) - sizeof(p->cksum)) /
                              sizeof(_UWORD));
        p->cksum = ~(p->cksum) + 1;
        size = sizeof(SSRP_Header);
        break;

    case TRXST_DATA_:
        *buf = 0;
        size = 1;
        break;

    case NUM_OF_TRXST_:
    default:
        _assert(_FALSE);
    }

    return size;
}

