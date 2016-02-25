/**
 * @file sci.c
 *
 * @version $Id: sci.c 156 2009-03-19 08:04:25Z minoru $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * drived Serial Communication Interface.
 *
 * @component H8 development platform
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 *
 * @see <related_items>
 ***********************************************************************/
#include "../include/h8sdk/stdlib.h"
#include "../include/h8sdk/3694s.h"
#include "../include/h8sdk/led.h"
#include "../include/h8sdk/sci.h"

#define MASK_TDRE_ (1U << 7)
#define MASK_RDRF_ (1U << 6)
#define MASK_TEND_ (1U << 2)
#define MASK_ERR_ ((SCI_ERR_PARITY | SCI_ERR_FRAMING | SCI_ERR_OVERRUN) << 3)


static _UBYTE tx_buf_[SCI_MAX_TXBUF] = { '\0' };
static _UBYTE rx_buf_[SCI_MAX_RXBUF] = { '\0' };
static volatile _UINT tx_in_ = 0;
static volatile _UINT rx_in_ = 0;
static volatile _UINT tx_out_ = 0;
static volatile _UINT rx_out_ = 0;
static _UBYTE lasterr_ = 0;


void SCI_init()
{
    _SCI3.SCR3.BYTE = 0;
    /* data len 8 bit, no parity, stop bit 1 */
    _SCI3.SMR.BYTE = 0;
    /* 19200bps */
    _SCI3.BRR = 0x20;

    _msleep(1);

    _IO.PMR1.BIT.TXD = 1;
    _SCI3.SCR3.BYTE = 0x70;
}

void SCI_communicate()
{
    _UBYTE ssr = _SCI3.SSR.BYTE;

    if (ssr & MASK_TDRE_)
    {
        if (tx_out_ != tx_in_)
        {
            _SCI3.TDR = tx_buf_[tx_out_];
            tx_out_ = _next_ring(tx_out_, SCI_MAX_TXBUF - 1);
            LED_ON(LED_D5);
        }
        else
        {
            _SCI3.SCR3.BIT.TIE = 0;
            LED_OFF(LED_D5);
        }
    }
    if (ssr & MASK_RDRF_)
    {
        _UINT next = _next_ring(rx_in_, SCI_MAX_RXBUF - 1);
        if (next != rx_out_)
        {
            rx_buf_[rx_in_] = _SCI3.RDR;
            rx_in_ = next;
        }
        else
        {
            _SCI3.SSR.BIT.RDRF = 0;
        }

        LED_TURN(LED_D6);
    }
    if (ssr & MASK_ERR_)
    {
        lasterr_ = (_SCI3.SSR.BYTE & MASK_ERR_) >> 3;
        _SCI3.SSR.BYTE &= 0xc7;
    }
}

_SINT SCI_puts(const _SBYTE* str)
{
    _SBYTE* p = str;

    while (*p)
    {
        while (_next_ring(tx_in_, SCI_MAX_TXBUF - 1) == tx_out_)
        {
            _msleep(100);
        }

        tx_buf_[tx_in_] = *p++;
        tx_in_ = _next_ring(tx_in_, SCI_MAX_TXBUF - 1);

        _SCI3.SCR3.BIT.TIE = 1;
    }

    return p - str;
}

_SINT SCI_write(const _UBYTE* data, _UBYTE size, _BOOL sync, _SINT tmo_ms)
{
    _UBYTE* p = data;

    while (size--)
    {
        while (_next_ring(tx_in_, SCI_MAX_TXBUF - 1) == tx_out_)
        {
            if (!sync) goto func_END;
            if ((tmo_ms >= 0) && (tmo_ms-- == 0)) goto func_END;

            _msleep(1);
        }

        tx_buf_[tx_in_] = *p++;
        tx_in_ = _next_ring(tx_in_, SCI_MAX_TXBUF - 1);
    }

func_END:
    if (p - data)
    {
        _SCI3.SCR3.BIT.TIE = 1;
    }
    return p - data;
}

_SINT SCI_read(_UBYTE* buf, _UBYTE size, _BOOL sync, _SINT tmo_ms)
{
    _SINT i;

    for (i = 0; i < size; i++)
    {
        while (rx_out_ == rx_in_)
        {
            if (!sync) goto func_END;
            if ((tmo_ms >= 0) && (tmo_ms-- == 0)) goto func_END;

            _msleep(1);
        }

        *buf++ = rx_buf_[rx_out_];
        rx_out_ = _next_ring(rx_out_, SCI_MAX_RXBUF - 1);
    }

func_END:
    return i;
}

_UBYTE SCI_getLastError()
{
    return lasterr_;
}
