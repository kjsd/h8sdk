/**
 * @file string.c
 *
 * @version $Id: string.c 156 2009-03-19 08:04:25Z minoru $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * std string.
 *
 * @component H8 development platform
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 *
 * @see <related_items>
 ***********************************************************************/
#include "../include/h8sdk/string.h"


_UWORD _strlen(const _SBYTE* str)
{
    _SBYTE* p;

    for (p = str; *p; p++);

    return p - str;
}

void* _memcpy(void* dst, const void* src, _UWORD size)
{
    _UBYTE* pd = (_UBYTE*)dst;
    _UBYTE* ps = (_UBYTE*)src;

    while (size--)
    {
        *pd++ = *ps++;
    }

    return dst;
}

void* _memset(void* dst, _SINT c, _UWORD size)
{
    _UBYTE* p = (_UBYTE*)dst;
    const _UBYTE ch = (_UBYTE)c;

    while (size--)
    {
        *p++ = ch;
    }

    return dst;
}
