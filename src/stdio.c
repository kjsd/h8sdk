/**
 * @file stdio.c
 *
 * @version $Id: stdio.c 156 2009-03-19 08:04:25Z minoru $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * stdio.
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
#include "../include/h8sdk/string.h"
#include "../include/h8sdk/stdio.h"


IFSTUB_Type _STDOUT = IFSTUB_SCI;
IFSTUB_Type _STDIN = IFSTUB_SCI;
IFSTUB_Type _STDERR = IFSTUB_SCI;

typedef _UBYTE (*format_handler_)(_UBYTE* argv);
static _UBYTE fmt_digit_(_UBYTE* argv);
static _UBYTE fmt_unsigned_(_UBYTE* argv);
static _UBYTE fmt_hexa_(_UBYTE* argv);
static _UBYTE fmt_octal_(_UBYTE* argv);
static _UBYTE fmt_string_(_UBYTE* argv);
static _UBYTE fmt_percent_(_UBYTE* argv);

static const _SBYTE format_symbols_[] = "duxos%";
static const format_handler_ format_hdl_table_[] = {
    fmt_digit_,
    fmt_unsigned_,
    fmt_hexa_,
    fmt_octal_,
    fmt_string_,
    fmt_percent_
};

void _printf(const _SBYTE* format, ...)
{
    _UBYTE* p;
    _UBYTE* argv;
    _SINT i;

    /* argvが第2引数を指すようにセット */
    argv = (_UBYTE*)(&format) + sizeof(format);
    if (((_UINT)argv & 1) == 1)
    {
        argv++;
    }

    for (p = (_UBYTE*)format; *p; p++)
    {
        if (*p != '%')
        {
            IFSTUB_getInstance(_STDOUT)->write(p, 1, _TRUE, -1);
            continue;
        }

        p++;
        if (*p == '\0') return;

        for (i = 0; i < sizeof(format_symbols_); i++)
        {
            if (*p == format_symbols_[i])
            {
                argv += format_hdl_table_[i](argv);
                if (((_UINT)argv & 1) == 1)
                {
                    argv++;
                }
                break;
            }
        }
    }
}

static _UBYTE fmt_digit_(_UBYTE* argv)
{
    _SINT i;
    _SBYTE str[7] = { '\0' };
    _SINT num = *(_SINT*)argv;

    if (num >= 0)
    {
        i = _itoa(*(_UINT*)argv, 10, str, _sizeof_array(str));
    }
    else
    {
        num *= -1;
        str[0] = '-';
        i = _itoa((_UINT)num, 10, &str[1], _sizeof_array(str) - 1) + 1;
    }

    IFSTUB_getInstance(_STDOUT)->write((_UBYTE*)str, i, _TRUE, -1);

    return sizeof(_SINT);
}

static _UBYTE fmt_unsigned_(_UBYTE* argv)
{
    _SINT i;
    _SBYTE str[6] = { '\0' };

    i = _itoa(*(_UINT*)argv, 10, str, _sizeof_array(str));
    IFSTUB_getInstance(_STDOUT)->write((_UBYTE*)str, i, _TRUE, -1);

    return sizeof(_UINT);
}

static _UBYTE fmt_hexa_(_UBYTE* argv)
{
    _SINT i;
    _SBYTE str[6] = { '\0' };

    i = _itoa(*(_UINT*)argv, 16, str, _sizeof_array(str));
    IFSTUB_getInstance(_STDOUT)->write((_UBYTE*)str, i, _TRUE, -1);

    return sizeof(_UINT);
}

static _UBYTE fmt_octal_(_UBYTE* argv)
{
    _SINT i;
    _SBYTE str[6] = { '\0' };

    i = _itoa(*(_UINT*)argv, 8, str, _sizeof_array(str));
    IFSTUB_getInstance(_STDOUT)->write((_UBYTE*)str, i, _TRUE, -1);

    return sizeof(_UINT);
}

static _UBYTE fmt_string_(_UBYTE* argv)
{
    _UWORD len = _strlen(*(_SBYTE**)argv);

    IFSTUB_getInstance(_STDOUT)->write(*(_UBYTE**)argv, len, _TRUE, -1);

    return sizeof(_SBYTE*);
}

static _UBYTE fmt_percent_(_UBYTE* argv)
{
    const _UBYTE p = '%';

    IFSTUB_getInstance(_STDOUT)->write(&p, 1, _TRUE, -1);

    return 0;
}
