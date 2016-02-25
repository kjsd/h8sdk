/**
 * @file ioctl.c
 *
 * @brief I/Oポートコントローラ
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
#include "../include/h8sdk/3694s.h"
#include "../include/h8sdk/ioctl.h"


typedef struct
{
    _UBYTE* const addr;
    _UBYTE val;
} IOCTL_Pair;

static IOCTL_Pair pcr_[IOCTL_NUM_OF_REG] = {
    { &_IO.PCR1, 0 },
    { &_IO.PCR2, 0 },
    { &_IO.PCR5, 0 },
    { &_IO.PCR7, 0 },
    { &_IO.PCR8, 0 }
};


void IOCTL_init()
{
    _SINT i;
    for (i = 0; i < IOCTL_NUM_OF_REG; i++)
    {
        pcr_[i].val = 0;
        *(pcr_[i].addr) = 0;
    }
}

void IOCTL_set(IOCTL_Reg reg, _UBYTE mask, _UBYTE val)
{
    pcr_[reg].val = (pcr_[reg].val & ~mask) | (val & mask);
    *(pcr_[reg].addr) = pcr_[reg].val;
}

_UBYTE IOCTL_get(IOCTL_Reg reg)
{
    return pcr_[reg].val;
}
