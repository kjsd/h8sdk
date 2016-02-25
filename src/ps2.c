/**
 * @file ps2.c
 *
 * @brief PS/2ドライバ
 *
 * PS/2ドライバの実装
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
#include "../include/h8sdk/ps2.h"

#define PIN_CLOCK_ _IO.PDR1.BIT.B5
#define PIN_DATA_  _IO.PDR8.BIT.B7
#define CLOCK_IN_ IOCTL_set(IOCTL_REG_PCR1, 0x20, 0)
#define CLOCK_OUT_ IOCTL_set(IOCTL_REG_PCR1, 0x20, 0x20)
#define DATA_IN_ IOCTL_set(IOCTL_REG_PCR8, 0x80, 0)
#define DATA_OUT_ IOCTL_set(IOCTL_REG_PCR8, 0x80, 0x80)

#define RX_ENABLE_                              \
    do                                          \
    {                                           \
        CLOCK_OUT_;                             \
        DATA_OUT_;                              \
        PIN_CLOCK_ = 1;                         \
        PIN_DATA_ = 1;                          \
        CLOCK_IN_;                              \
        DATA_IN_;                               \
    }                                           \
    while (_FALSE)

#define RX_DISABLE_ do { CLOCK_OUT_; PIN_CLOCK_ = 0; } while(_FALSE)
#define WAIT_EDGE_  do { while(!PIN_CLOCK_); while(PIN_CLOCK_) } while(_FALSE)

static _UBYTE rx_buf_[PS2_MAX_RXBUF] = { '\0' };
static volatile _UINT rx_in_ = 0;
static volatile _UINT rx_out_ = 0;
static PS2_Status lasterr_ = PS2_ERR_OK;


void PS2_init()
{
    _IENR1.BIT.IEN1 = 0;

    _IO.PMR1.BIT.IRQ1 = 0;
    RX_DISABLE_;
    _usleep(100);
    RX_ENABLE_;

    _IO.PMR1.BIT.IRQ1 = 1;
    _usleep(1);

    _IRR1.BIT.IRRI1 = 0;
    _IEGR1.BIT.IEG1 = 0;
    _IENR1.BIT.IEN1 = 1;
}

void PS2_communicate()
{
    static enum {
        START = 0,
        DATA0,
        DATA1,
        DATA2,
        DATA3,
        DATA4,
        DATA5,
        DATA6,
        DATA7,
        PARITY,
        STOP
    } current_frame = START;

    static _UBYTE data = 0;
    static _UBYTE parity = 0;
    static _UBYTE ienr1 = 0;
    static _UBYTE shift = 0;
    _UINT next;

    switch (current_frame)
    {
    case START:
        data = 0;
        parity = 0;
        shift = 0;
        if (PIN_DATA_)
        {
            lasterr_ = PS2_ERR_FRAMING;
            return;
        }
        _IRR1.BYTE = 0;
        ienr1 = _IENR1.BYTE;
        _IENR1.BYTE = 1U << 1;
        break;
    case DATA7:
        /* fallthrough */
    case DATA6:
        /* fallthrough */
    case DATA5:
        /* fallthrough */
    case DATA4:
        /* fallthrough */
    case DATA3:
        /* fallthrough */
    case DATA2:
        /* fallthrough */
    case DATA1:
        /* fallthrough */
    case DATA0:
        data |= (PIN_DATA_ << shift);
        parity += PIN_DATA_;
        shift++;
        break;
    case PARITY:
        parity += PIN_DATA_;
        if ((parity & 1) == 0)
        {
            lasterr_ = PS2_ERR_PARITY;
            current_frame = START;
            _IENR1.BYTE = ienr1;
            return;
        }
        break;
    case STOP:
        if (!PIN_DATA_)
        {
            lasterr_ = PS2_ERR_FRAMING;
            current_frame = START;
            _IENR1.BYTE = ienr1;
            return;
        }

        next = _next_ring(rx_in_, PS2_MAX_RXBUF - 1);
        if (next != rx_out_)
        {
            rx_buf_[rx_in_] = data;
            rx_in_ = next;
        }
        _IENR1.BYTE = ienr1;
        break;
    default:
        _assert(_FALSE);
        break;
    }

    current_frame = _next_ring(current_frame, STOP);
}

_SINT PS2_read(_UBYTE* buf, _UBYTE size, _BOOL sync, _SINT tmo_ms)
{
    _UBYTE* p = buf;

    while (size--)
    {
        while (rx_out_ == rx_in_)
        {
            if (!sync) goto func_END;
            if ((tmo_ms >= 0) && (tmo_ms-- == 0)) goto func_END;

            _msleep(1);
        }

        *p++ = rx_buf_[rx_out_];
        rx_out_ = _next_ring(rx_out_, PS2_MAX_RXBUF - 1);
    }

func_END:
    return p - buf;
}

_UBYTE PS2_getLastError()
{
    return lasterr_;
}
