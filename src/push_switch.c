/**
 * @file push_switch.c
 *
 * @version $Id: push_switch.c 156 2009-03-19 08:04:25Z minoru $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * drived Push Switch.
 *
 * @component H8 development platform
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 *
 * @see <related_items>
 ***********************************************************************/
#include "../include/h8sdk/3694s.h"
#include "../include/h8sdk/ioctl.h"
#include "../include/h8sdk/push_switch.h"

#define DATA_MASK_(x) (1U << ((x) + 6))


void PSW_init(_BOOL interrupt)
{
    _UBYTE b = (interrupt) ? 1: 0;

    IOCTL_set(IOCTL_REG_PCR1, 0xc0, 0);

    _IO.PMR1.BIT.IRQ2 = b;
    _IEGR1.BIT.IEG2 = b;
    _IENR1.BIT.IEN2 = b;
    _IO.PMR1.BIT.IRQ3 = b;
    _IEGR1.BIT.IEG3 = b;
    _IENR1.BIT.IEN3 = b;
}

_BOOL PSW_get(PSW_Type t)
{
    static _UWORD counter[PSW_NUM_OF_TYPE] = { 0 };
    static _BOOL wait[PSW_NUM_OF_TYPE] = { _FALSE };
    _BOOL s;
    _BOOL rtn = _FALSE;
    _SINT i;

    s = PSW_snapShot(t);
    if (s && !wait[t])
    {
        rtn = s;
        wait[t] = _TRUE;
    }

    if (wait[t])
    {
        if (++counter[t] == PSW_BORDER)
        {
            wait[t] = _FALSE;
            counter[t] = 0;
        }
    }

    return rtn;
}

_BOOL PSW_oneShot(PSW_Type t)
{
    static _BOOL prev[PSW_NUM_OF_TYPE] = { _FALSE };
    _BOOL s;
    _BOOL rtn = _FALSE;

    s = PSW_snapShot(t);
    if (s && !prev[t])
    {
        rtn = _TRUE;
    }
    prev[t] = s;

    return rtn;
}

_BOOL PSW_snapShot(PSW_Type t)
{
    static _BOOL prev[PSW_NUM_OF_TYPE] = { _FALSE };
    _BOOL s;
    _BOOL rtn = _FALSE;

    s = (_IO.PDR1.BYTE & DATA_MASK_(t)) ? _TRUE: _FALSE;
    if (s && prev[t])
    {
        rtn = s;
    }
    prev[t] = s;

    return rtn;
}
