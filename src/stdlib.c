/**
 * @file stdlib.c
 *
 * @version $Id: stdlib.c 153 2009-03-17 08:44:38Z minoru $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * stdlib.
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


static _SDWORD seed_ = 1;


_UWORD _check_sum(void* ary, _UWORD sz)
{
    _UWORD* p = (_UWORD*)ary;
    _UWORD sum = 0;

    while (sz--)
    {
        sum += *p++;
    }

    return sum;
}

_UINT _itoa(_UINT in, _SINT base, _SBYTE *out, _UINT size)
{
    _SBYTE* p = out;
    _SINT i;
    _SINT pow;
    _SINT diff = 0;
    _UBYTE tmp = 0;
    _BOOL start = _FALSE;

    if (size == 0) return 0;
    if (in == 0)
    {
        *p = 0x30;
        return 1;
    }

    while (size--)
    {
        for (pow = 1, i = 0; i < size; i++)
        {
            pow *= base;
        }

        tmp = (in - diff)/ pow;
        if ((tmp != 0) || start)
        {
            diff += (tmp * pow);
            *p = tmp | 0x30;
            if (*p > 0x39)
            {
                *p += 7;
            }

            *p++;
            start = _TRUE;
        }
    }

    return p - out;
}

_SDWORD _rand()
{
    seed_ = seed_ * 1103515245 + 12345;

    return (seed_ >> 16) & 32767;
}

void _srand(_SDWORD s)
{
    seed_ = s;
}
