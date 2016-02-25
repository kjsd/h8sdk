/**
 * @file lcd.c
 *
 * @version $Id: lcd.c 153 2009-03-17 08:44:38Z minoru $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * drived LCD charactor display.
 *
 * @component H8 development platform
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 *
 * @see <related_items>
 ***********************************************************************/
#include "lcd_def.h"


static _SINT x_ = 0;
static _SINT y_ = 0;

void LCD_init()
{
    CTRL_OUT_;
    DATA_OUT_;

    REG_RS_ = SYM_INST_;
    REG_RW_ = FLG_WRITE_;
    REG_E_ = 0;

    _msleep(15);
    REG_E_ = 1;
    REG_DATA_ = 0x30;
    REG_E_ = 0;

    _msleep(5);
    REG_E_ = 1;
    REG_DATA_ = 0x30;
    REG_E_ = 0;
  
    _msleep(1);
    REG_E_ = 1;
    REG_DATA_ = 0x30;
    REG_E_ = 0;

    _msleep(1);
    REG_E_ = 1;
    REG_DATA_ = 0x30;
    REG_E_ = 0;

    writeReg_(0x38, SYM_INST_);
    writeReg_(0x08, SYM_INST_);
    writeReg_(0x01, SYM_INST_);
    writeReg_(0x06, SYM_INST_);
    writeReg_(0x0c, SYM_INST_);
}

_SINT LCD_puts(const _SBYTE *str)
{
    _SBYTE* p = str;

    while (*p)
    {
        _assert(p);

        if (*p == '\n')
        {
            LCD_crlf();
        }
        else
        {
            writeReg_(*p, SYM_DATA_);
            if (++x_ == LCD_MAX_COLS)
            {
                LCD_crlf();
            }
        }

        p++;
    }

    return p - str;
}

_SINT LCD_write(const _UBYTE* data, _SINT size)
{
    _UBYTE* p = data;

    while (size--)
    {
        _assert(p);

        writeReg_(*p++, SYM_DATA_);
        if (++x_ == LCD_MAX_COLS)
        {
            LCD_crlf();
        }
    }

    return p - data;
}

_SINT LCD_read(_UBYTE* buf, _SINT size)
{
    _UBYTE* p = buf;

    while (size--)
    {
        _assert(p);

        *p++ = readReg_(SYM_DATA_);
        if (++x_ == LCD_MAX_COLS)
        {
            LCD_crlf();
        }
    }

    return p - buf;
}

void LCD_getCursor(_SINT* x, _SINT* y)
{
    *x = x_;
    *y = y_;
}

void LCD_setCursor(_SINT x, _SINT y)
{
    if (x < LCD_MAX_COLS)
    {
        x_ = x;
    }
    if (y < LCD_MAX_ROWS)
    {
        y_ = y;
    }

    writeReg_((x_ + y_ * 0x40) | FLG_DDRAM_, SYM_INST_);
}

void LCD_crlf()
{
    x_ = 0;
    if (++y_ == LCD_MAX_ROWS)
    {
        y_ = 0;
    }
    writeReg_((x_ + y_ * 0x40) | FLG_DDRAM_, SYM_INST_);
}

void LCD_cls()
{
    writeReg_(0x01, SYM_INST_);
    LCD_setCursor(0, 0);
}

void LCD_setChar(_UBYTE no, const _UBYTE* data)
{
    _UINT i;

    _assert(no < LCD_CG_MAXCHAR);

    no = (no & (LCD_CG_MAXCHAR - 1)) << 3;

    for (i = 0; i < LCD_CG_ROWS; i++)
    {
        writeReg_(no | (i & (LCD_CG_ROWS - 1)) | FLG_CGRAM_, SYM_INST_);
        writeReg_(*data++, SYM_DATA_);
    }

    writeReg_((x_ + y_ * 0x40) | FLG_DDRAM_, SYM_INST_);
}

void LCD_setVisual(_BOOL all, _BOOL cur, _BOOL blink)
{
    _UBYTE d = 0x08;

    d |= all ? (1U << 2): 0;
    d |= cur ? (1U << 1): 0;
    d |= blink ? (1U << 0): 0;

    writeReg_(d, SYM_INST_);
}

static _UBYTE readReg_(Registor_ rs)
{
    _UBYTE data = 0;

    DATA_IN_;
    REG_RS_ = rs;
    REG_RW_ = FLG_READ_;
    REG_E_ = 1;
    data = REG_DATA_;
    REG_E_ = 0;

    _msleep(1);

    return data;
}

static void writeReg_(_UBYTE data, Registor_ rs)
{
    while (readReg_(SYM_INST_) & FLG_BUSY_);

    DATA_OUT_;
    REG_RS_ = rs;
    REG_RW_ = FLG_WRITE_;
    REG_E_ = 1;
    REG_DATA_ = data;
    REG_E_ = 0;

    _msleep(1);
}
