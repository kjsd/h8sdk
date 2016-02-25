/**
 * @file adc.c
 *
 * @version $Id: adc.c 156 2009-03-19 08:04:25Z minoru $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * drived A/D Convertor.
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
#include "../include/h8sdk/adc.h"

#define ADC_BASE 0xFFB0


void ADC_init(ADC_Mode mode, _BOOL interrupt)
{
    _AD.ADDRA = 0;
    _AD.ADDRB = 0;
    _AD.ADDRC = 0;
    _AD.ADDRD = 0;

    _AD.ADCSR.BYTE = 0;
    _AD.ADCSR.BIT.SCAN = mode;
    _AD.ADCSR.BIT.ADIE = (interrupt) ? 1: 0;
}

void ADC_enable(ADC_Channel ch)
{
    _AD.ADCSR.BIT.CH |= ch;
}

void ADC_disable(ADC_Channel ch)
{
    _AD.ADCSR.BIT.CH ^= ch;
}

void ADC_start()
{
    _AD.ADCSR.BIT.ADST = 1;
}

void ADC_stop()
{
    _AD.ADCSR.BIT.ADST = 0;
    if (_AD.ADCSR.BIT.ADF)
    {
        _AD.ADCSR.BIT.ADF = 0;
    }
}

_SDWORD ADC_get(ADC_Channel anx, _BOOL last)
{
    _SDWORD rtn = -1;
    _UWORD data = 0;
    static _UWORD prev[ADC_NUM_OF_CHANNEL] = { 0 };

    if (_AD.ADCSR.BIT.ADF)
    {
        data = (((volatile _UWORD *)(ADC_BASE))[anx]) >> 6;
        rtn = (data + prev[anx]) >> 1;
        prev[anx] = data;

        if (last)
        {
            _AD.ADCSR.BIT.ADF = 0;
        }
    }

    return rtn;
}

