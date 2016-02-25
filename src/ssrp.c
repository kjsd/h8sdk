/**
 * @file ssrp.c
 *
 * @version $Id: ssrp.c 156 2009-03-19 08:04:25Z minoru $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * responsibility of management of Simple Single Ring Protocol.
 *
 * @component H8 development platform.
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 *
 * @see <related_items>
 ***********************************************************************/
#include "ssrp_def.h"


_SBYTE SSRP_my_addr[3] = { '\0' };
static IFSTUB_Class* stub_ = NULL;
static SSRP_Address my_addr_ = SSRP_ADDR_INVALID;

static Pear_ pear_ = {
    { SSRP_ADDR_INVALID }, { SSRP_ADDR_INVALID }, 0, 0
};

static _UBYTE buffer_[SSRP_MAX_DATA] = { 0 };
static SSRP_TransactionId trx_count_ = 0;

static TransactionParam_ trx_[SSRP_NUM_OF_TRX] = {
    {
        { SSRP_ADDR_INVALID, SSRP_ADDR_INVALID, SSRP_CMD_INVALID,
          SSRP_FLG_INVALID, 0, SSRP_MAX_DATA, SSRP_TRXID_INVALID, 0 },
        buffer_, TRXST_PREAMBLE_
    },
    {
        { SSRP_ADDR_INVALID, SSRP_ADDR_INVALID, SSRP_CMD_INVALID,
          SSRP_FLG_INVALID, 0, 0, SSRP_TRXID_INVALID, 0 },
        NULL, TRXST_PREAMBLE_
    }
};

static _SINT recv_(_UBYTE* buf, _UBYTE len, _BOOL sync);
static _BOOL stHdlCountPear_();
static _BOOL stHdlConnect_();
static _BOOL stHdlWatch_();
static void sendResponse_();
static _SWORD findNode_(SSRP_Address addr);
static _BOOL insertNode_(SSRP_Address addr);
static _BOOL deleteNode_(SSRP_Address addr);

static const StateTable_ state_tbl_[NUM_OF_STATE_] = {
    { stHdlCountPear_, ST_DISCONNECT_ },
    { stHdlConnect_, ST_CONNECT_ },
    { stHdlWatch_, ST_DEALLOCATE_ }
};
static State_ current_state_ = ST_DEALLOCATE_;
static _BOOL start_ = _FALSE;


void SSRP_init(SSRP_Address myaddr)
{
#ifdef USE_LOOPBACK_SSRP
    stub_ = IFSTUB_getInstance(IFSTUB_SSRP_SKELETON);
#else
    stub_ = IFSTUB_getInstance(IFSTUB_SCI);
#endif /* USE_LOOPBACK_SSRP */

    my_addr_ = myaddr;
    _itoa(my_addr_, 16, SSRP_my_addr, sizeof(SSRP_my_addr));
}

void SSRP_start()
{
    start_ = _TRUE;
}

void SSRP_end()
{
    _UBYTE buf = 0;
    _SINT i;

    SSRP_sendto(SSRP_ADDR_BROADCAST, SSRP_CMD_LEAVE, SSRP_FLG_EVT,
                &buf, sizeof(buf), NULL, _TRUE);

    for (i = 0; i < SSRP_MAX_NODE; i++)
    {
        pear_.addr[i] = SSRP_ADDR_INVALID;
    }
    for (i = 0; i < SSRP_NUM_OF_CON; i++)
    {
        pear_.con[i] = SSRP_ADDR_INVALID;
    }
    pear_.total = 0;
    pear_.addr_count = 0;

    current_state_ = ST_DEALLOCATE_;
    start_ = _FALSE;
}

_BOOL SSRP_ready()
{
    return (current_state_ == ST_CONNECT_) ? _TRUE: _FALSE;
}

SSRP_Address SSRP_getNode(_UBYTE idx)
{
    _UBYTE i = 0;
    _UBYTE num = 0;
    SSRP_Address rtn = SSRP_ADDR_INVALID;

    for (i = 0; i < SSRP_MAX_NODE; i++)
    {
        if (pear_.addr[i] != SSRP_ADDR_INVALID)
        {
            if (num++ == idx)
            {
                rtn = pear_.addr[i];
                break;
            }
        }
    }

    return rtn;
}

SSRP_Address SSRP_getPear(SSRP_Connection con)
{
    _assert(con < SSRP_NUM_OF_CON);

    return pear_.con[con];
}

_UBYTE SSRP_getTotalPear()
{
    return pear_.total + (start_ ? 1: 0);
}

_SINT SSRP_send(SSRP_Header* header, const _UBYTE* data, _UBYTE len, _BOOL sync)
{
    _SINT rsize = 0;
    _UBYTE pre = SSRP_VAL_PREAMBLE;
    _SINT i;

    _assert(stub_);
    _assert(len <= header->data_length);

    for (i = trx_[SSRP_TRX_SEND].state; i < NUM_OF_TRXST_; i++)
    {
        switch (i)
        {
        case TRXST_PREAMBLE_:
            rsize = stub_->write(&pre, sizeof(pre), sync, SSRP_TMO_SEND);
            if (rsize != sizeof(pre)) rsize = -1;
            break;

        case TRXST_HEADER_:
            if (header->from == my_addr_)
            {
                header->trx_id = trx_count_++;
            }
            header->cksum = _check_sum(header,
                                       (sizeof(SSRP_Header) -
                                        sizeof(header->cksum)) /
                                       sizeof(_UWORD));
            header->cksum = ~(header->cksum) + 1;

            rsize = stub_->write((_UBYTE*)header, sizeof(SSRP_Header), _TRUE,
                                 SSRP_TMO_SEND);
            break;

        case TRXST_DATA_:
            rsize = stub_->write(data, len, sync, SSRP_TMO_SEND);
            break;

        default:
            _assert(_FALSE);
            break;
        }

        if (rsize < 0) goto func_END;
    }
    
    if (i > TRXST_DATA_)
    {
        trx_[SSRP_TRX_SEND].state = (rsize < len) ?
            TRXST_DATA_: TRXST_PREAMBLE_;
    }
    else
    {
        trx_[SSRP_TRX_SEND].state = i;
    }

func_END:
    return rsize;
}

_SINT SSRP_sendto(SSRP_Address to, SSRP_Command cmd, SSRP_Flag flg,
                  const _UBYTE* data, _UBYTE len,
                  SSRP_TransactionId* trx_id, _BOOL sync)
{
    _SINT rtn;

    trx_[SSRP_TRX_SEND].header.from = my_addr_;
    trx_[SSRP_TRX_SEND].header.to = to;
    trx_[SSRP_TRX_SEND].header.command = cmd;
    trx_[SSRP_TRX_SEND].header.flag = flg;
    trx_[SSRP_TRX_SEND].header.data_length = len;

    rtn = SSRP_send(&trx_[SSRP_TRX_SEND].header, data, len, sync);
    if (trx_id != NULL)
    {
        *trx_id = trx_[SSRP_TRX_SEND].header.trx_id;
    }
    
    return rtn;
}

_SINT SSRP_recvfrom(SSRP_Header** header_p, _UBYTE** data_p)
{
    if ((trx_[SSRP_TRX_RECV].header.to != my_addr_) &&
        (trx_[SSRP_TRX_RECV].header.to != SSRP_ADDR_BROADCAST))
    {
        return -1;
    }
    if (trx_[SSRP_TRX_RECV].state != TRXST_PREAMBLE_)
    {
        return -1;
    }

    *header_p = &trx_[SSRP_TRX_RECV].header;
    *data_p = trx_[SSRP_TRX_RECV].buffer;

    return trx_[SSRP_TRX_RECV].header.data_length;
}

void SSRP_shutdown(SSRP_Transaction tr)
{
    trx_[tr].state = TRXST_PREAMBLE_;
    SSRP_INVALIDATE_PACKET(&trx_[tr].header);
}

void SSRP_exec()
{
    _SINT rtn;
    _UBYTE rsize;
    _UBYTE buf;
    
    SSRP_INVALIDATE_PACKET(&trx_[SSRP_TRX_RECV].header);

    rtn = recv_(trx_[SSRP_TRX_RECV].buffer, SSRP_MAX_DATA, _FALSE);
    if (rtn >= 0)
    {
        for (rsize = rtn;
             rsize < trx_[SSRP_TRX_RECV].header.data_length;
             rsize += rtn)
        {
            rtn = recv_(trx_[SSRP_TRX_RECV].buffer + rsize,
                            trx_[SSRP_TRX_RECV].header.data_length - rsize,
                            _FALSE);
            if (rtn < 0)
            {
                SSRP_shutdown(SSRP_TRX_RECV);
                break;
            }
        }
    }
    else
    {
        SSRP_shutdown(SSRP_TRX_RECV);
    }

    if (start_)
    {
        if (state_tbl_[current_state_].handle())
        {
            current_state_ = state_tbl_[current_state_].next;
        }
    }

    if (SSRP_IS_INVALID_PACKET(&trx_[SSRP_TRX_RECV].header)) return;

    if (trx_[SSRP_TRX_RECV].header.from == my_addr_) return;
    if (trx_[SSRP_TRX_RECV].header.to == my_addr_) return;
    if (trx_[SSRP_TRX_RECV].header.hop >= pear_.total) return;

    if (start_)
    {
        trx_[SSRP_TRX_RECV].header.hop++;
    }
    SSRP_send(&trx_[SSRP_TRX_RECV].header,
              trx_[SSRP_TRX_RECV].buffer,
              trx_[SSRP_TRX_RECV].header.data_length,
              _TRUE);
}

static _SINT recv_(_UBYTE* buf, _UBYTE len, _BOOL sync)
{
    _SINT rsize = 0;
    _UBYTE pre = 0;
    _SINT i;

    _assert(stub_);
    _assert(len <= SSRP_MAX_DATA);

    for (i = trx_[SSRP_TRX_RECV].state; i < NUM_OF_TRXST_; i++)
    {
        switch (i)
        {
        case TRXST_PREAMBLE_:
            rsize = stub_->read(&pre, sizeof(pre), sync, SSRP_TMO_RECV);
            if (pre != SSRP_VAL_PREAMBLE)
            {
                rsize = -1;
            }
            break;

        case TRXST_HEADER_:
            rsize = stub_->read((_UBYTE*)&trx_[SSRP_TRX_RECV].header,
                                sizeof(SSRP_Header), _TRUE, SSRP_TMO_RECV);

            if (rsize != sizeof(SSRP_Header))
            {
                rsize = -1;
                break;
            }

            if (_check_sum(&trx_[SSRP_TRX_RECV].header,
                           sizeof(SSRP_Header) / sizeof(_UWORD)) != 0)
            {
                rsize = -1;
            }
            break;

        case TRXST_DATA_:
            if (len > trx_[SSRP_TRX_RECV].header.data_length)
            {
                len = trx_[SSRP_TRX_RECV].header.data_length;
            }
            rsize = stub_->read(buf, len, sync, SSRP_TMO_RECV);
            break;

        default:
            _assert(_FALSE);
            break;
        }

        if (rsize < 0) goto func_END;
    }

    if (i > TRXST_DATA_)
    {
        trx_[SSRP_TRX_RECV].state = (rsize < len) ?
            TRXST_DATA_: TRXST_PREAMBLE_;
    }
    else
    {
        trx_[SSRP_TRX_RECV].state = i;
    }

func_END:
    return rsize;
}

static _BOOL stHdlCountPear_()
{
    static _UWORD counter = SSRP_PACKET_SPC;
    _UBYTE buf = 0;


    if (!SSRP_IS_INVALID_PACKET(&trx_[SSRP_TRX_RECV].header))
    {
        if ((trx_[SSRP_TRX_RECV].header.from == my_addr_) &&
            SSRP_COMMAND_EQ(&trx_[SSRP_TRX_RECV].header,
                            SSRP_CMD_LOOP, SSRP_FLG_EVT))
        {
            pear_.total = trx_[SSRP_TRX_RECV].header.hop;

            return _TRUE;
        }
    }

    if (counter++ & SSRP_PACKET_SPC)
    {
        SSRP_sendto(SSRP_ADDR_BROADCAST, SSRP_CMD_LOOP, SSRP_FLG_EVT,
                    &buf, sizeof(buf), NULL, _TRUE);
    }

    return _FALSE;
}

static _BOOL stHdlConnect_()
{
    static _UWORD counter = SSRP_PACKET_SPC;
    _UBYTE buf = 0;
    _SINT i;

    if ((trx_[SSRP_TRX_RECV].header.to == my_addr_) &&
        SSRP_COMMAND_EQ(&trx_[SSRP_TRX_RECV].header,
                        SSRP_CMD_JOIN, SSRP_FLG_RES))
    {
        insertNode_(trx_[SSRP_TRX_RECV].header.from);

        pear_.con[*(trx_[SSRP_TRX_RECV].buffer)] =
            trx_[SSRP_TRX_RECV].header.from;
    }
    else
    {
        sendResponse_();
    }

    if (pear_.addr_count == pear_.total)
    {
        for (i = 0; i < SSRP_NUM_OF_CON; i++)
        {
            if (pear_.con[i] == SSRP_ADDR_INVALID)
            {
                goto func_END;
            }
        }
        return _TRUE;
    }

func_END:
    if (counter++ & SSRP_PACKET_SPC)
    {
        SSRP_sendto(SSRP_ADDR_BROADCAST, SSRP_CMD_JOIN, SSRP_FLG_REQ,
                    &buf, sizeof(buf), NULL, _TRUE);
    }

    return _FALSE;
}

static _BOOL stHdlWatch_()
{
    _SINT i;

    sendResponse_();

    if (pear_.addr_count != pear_.total)
    {
        for (i = 0; i < SSRP_MAX_NODE; i++)
        {
            pear_.addr[i] = SSRP_ADDR_INVALID;
        }
        for (i = 0; i < SSRP_NUM_OF_CON; i++)
        {
            pear_.con[i] = SSRP_ADDR_INVALID;
        }
        pear_.total = 0;
        pear_.addr_count = 0;
        return _TRUE;
    }

    return _FALSE;
}

static void sendResponse_()
{
    _UBYTE buf;
    _SINT rsize;

    if (SSRP_IS_INVALID_PACKET(&trx_[SSRP_TRX_RECV].header)) return;
    if (trx_[SSRP_TRX_RECV].header.from == my_addr_) return;

    if (SSRP_COMMAND_EQ(&trx_[SSRP_TRX_RECV].header,
                        SSRP_CMD_JOIN, SSRP_FLG_REQ))
    {
        insertNode_(trx_[SSRP_TRX_RECV].header.from);

        if (trx_[SSRP_TRX_RECV].header.hop == 0)
        {
            buf = SSRP_CON_FRONT;
            rsize = SSRP_sendto(trx_[SSRP_TRX_RECV].header.from,
                                SSRP_CMD_JOIN, SSRP_FLG_RES,
                                &buf, sizeof(buf), NULL, _TRUE);
            if (rsize > 0)
            {
                pear_.con[SSRP_CON_BACK] =
                    trx_[SSRP_TRX_RECV].header.from;
            }
        }

        if (trx_[SSRP_TRX_RECV].header.hop == (pear_.total - 1))
        {
            buf = SSRP_CON_BACK;
            rsize = SSRP_sendto(trx_[SSRP_TRX_RECV].header.from,
                                SSRP_CMD_JOIN, SSRP_FLG_RES,
                                &buf, sizeof(buf), NULL, _TRUE);
            if (rsize > 0)
            {
                pear_.con[SSRP_CON_FRONT] = trx_[SSRP_TRX_RECV].header.from;
            }
        }
    }
    else if (SSRP_COMMAND_EQ(&trx_[SSRP_TRX_RECV].header,
                             SSRP_CMD_LEAVE, SSRP_FLG_EVT))
    {
        _SINT i;

        for (i = 0; i < SSRP_NUM_OF_CON; i++)
        {
            if (pear_.con[i] == trx_[SSRP_TRX_RECV].header.from)
            {
                pear_.con[i] = SSRP_ADDR_INVALID;
            }
        }

        deleteNode_(trx_[SSRP_TRX_RECV].header.from);
    }
}

static _SWORD findNode_(SSRP_Address addr)
{
    _SWORD rtn = -1;
    _SWORD idx = _hash(addr, SSRP_MAX_NODE);
    _SINT i = SSRP_MAX_NODE;
    
    while (i--)
    {
        if (pear_.addr[idx] == addr)
        {
            rtn = idx;
            break;
        }
        idx++;
    }

    return rtn;
}

static _BOOL insertNode_(SSRP_Address addr)
{
    _BOOL rtn = _FALSE;
    _SWORD idx = _hash(addr, SSRP_MAX_NODE);
    _SINT i = SSRP_MAX_NODE;
    
    while (i--)
    {
        if (pear_.addr[idx] == SSRP_ADDR_INVALID)
        {
            pear_.addr[idx] = addr;
            pear_.addr_count++;
            rtn = _TRUE;
            break;
        }
        else if (pear_.addr[idx] == addr)
        {
            break;
        }
        idx++;
    }

    return rtn;
}

static _BOOL deleteNode_(SSRP_Address addr)
{
    _BOOL rtn = _FALSE;
    _SWORD idx = _hash(addr, SSRP_MAX_NODE);
    _SINT i = SSRP_MAX_NODE;
    
    while (i--)
    {
        if (pear_.addr[idx] == addr)
        {
            pear_.addr[idx] = SSRP_ADDR_INVALID;
            --pear_.addr_count;
            rtn = _TRUE;
            break;
        }
        idx++;
    }

    return rtn;
}
