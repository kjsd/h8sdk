/**
 * @file test.c
 *
 * @version $Id: test.c 157 2009-03-19 08:40:01Z minoru $
 * @version $Name:$
 *
 * @brief This file contains the implementation of modules which are
 * unit test for H8SDK.
 *
 * @author Kenji MINOURA / kenji@kandj.org
 *
 * Copyright (c) 2008 K&J Software Design, Ltd All rights reserved.
 *
 * @see <related_items>
 ***********************************************************************/
#include <h8sdk/ioctl.h>
#include <h8sdk/led.h>
#include <h8sdk/sci.h>

#ifdef TEST_STDC
#include <h8sdk/stdio.h>
#include <h8sdk/stdlib.h>
#include <h8sdk/string.h>
#endif /* TEST_STDC */

#ifdef TEST_ASSERT
#include <h8sdk/assert.h>
#endif /* TEST_ASSERT */

#ifdef TEST_LCD
#include <h8sdk/lcd.h>
#endif /* TEST_LCD */

#ifdef TEST_PUSH_SWITCH
#include <h8sdk/push_switch.h>
#endif /* TEST_PUSH_SWITCH */

#ifdef TEST_ADC
#include <h8sdk/adc.h>
#endif /* TEST_ADC */

#ifdef TEST_PS2
#include <h8sdk/ps2.h>
#include <h8sdk/kbd_jp106.h>
#endif /* TEST_PS2 */

#ifdef TEST_SOUND
#include <h8sdk/sound.h>
#endif /* TEST_SOUND */

#if defined(TEST_SOUND) || defined(TEST_MUSIC)
#include <h8sdk/envelope.h>
#endif

#ifdef TEST_MUSIC
#include <h8sdk/music.h>
#endif /* TEST_MUSIC */

#ifdef TEST_SSRP
#include <h8sdk/ssrp.h>
#include <h8sdk/ssrp_skel.h>
#endif /* TEST_SSRP */

#include "test.h"


int UTEST_run_count = 0;

#ifdef TEST_MUSIC
#define TS_BAR_LEN MUSIC_L0

static const MUSIC_Note ts_notes_a[] = {
    { { SOUND_E2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      0, MUSIC_L4 },
    { { SOUND_E2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      MUSIC_L4, MUSIC_L8 },
    { { SOUND_F2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      MUSIC_L4 + MUSIC_L8, MUSIC_L8 },
    { { SOUND_G2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      MUSIC_L2, MUSIC_L4 },
    { { SOUND_C2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      MUSIC_L2 + MUSIC_L4, MUSIC_L4 },
                                                
    { { SOUND_A2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      TS_BAR_LEN, MUSIC_L4 },
    { { SOUND_G2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      TS_BAR_LEN + MUSIC_L4, MUSIC_L8 },
    { { SOUND_F2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      TS_BAR_LEN + MUSIC_L4 + MUSIC_L8, MUSIC_L8 },
    { { SOUND_G2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      TS_BAR_LEN + MUSIC_L2, MUSIC_L4 },
    { { SOUND_C2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      TS_BAR_LEN + MUSIC_L2 + MUSIC_L4, MUSIC_L4 },
                                                
    { { SOUND_F2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 2), MUSIC_L4 },
    { { SOUND_E2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 2) + MUSIC_L4, MUSIC_L8 },
    { { SOUND_D2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 2) + MUSIC_L4 + MUSIC_L8, MUSIC_L8 },
    { { SOUND_E2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 2) + MUSIC_L2, MUSIC_L4 },
    { { SOUND_C2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 2) + MUSIC_L2 + MUSIC_L4, MUSIC_L4 },
                                                
    { { SOUND_A1, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 3), MUSIC_L8 },
    { { SOUND_C2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 3) + MUSIC_L8, MUSIC_L8 },
    { { SOUND_H1, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 3) + MUSIC_L4, MUSIC_L8 },
    { { SOUND_D2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 3) + MUSIC_L4 + MUSIC_L8, MUSIC_L8 },
    { { SOUND_C2, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 3) + MUSIC_L2, MUSIC_L2 }
};

static const MUSIC_Note ts_notes_b[] = {
    { { SOUND_C1, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 0), MUSIC_L2 },
    { { SOUND_E1, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 0) + MUSIC_L2, MUSIC_L2 },
   
    { { SOUND_F1, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 1), MUSIC_L2 },
    { { SOUND_E1, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 1) + MUSIC_L2, MUSIC_L2 },

    { { SOUND_A1, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 2), MUSIC_L2 },
    { { SOUND_G1, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 2) + MUSIC_L2, MUSIC_L2 },

    { { SOUND_F0, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 3), MUSIC_L4 },
    { { SOUND_G0, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 3) + MUSIC_L4, MUSIC_L4 },
    { { SOUND_E1, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 3) + MUSIC_L2, MUSIC_L2 }
};

static const MUSIC_Note ts_notes_c[] = {
    { { SOUND_D1, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 2), MUSIC_L2 },
    { { SOUND_C1, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 2) + MUSIC_L2, MUSIC_L2 },
   
    { { SOUND_C1, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE },
      (TS_BAR_LEN * 3) + MUSIC_L2, MUSIC_L2 }
};

static const MUSIC_Part ts_parts[] = {
    { ts_notes_b, _sizeof_array(ts_notes_b) },
    { ts_notes_a, _sizeof_array(ts_notes_a) },
    { ts_notes_c, _sizeof_array(ts_notes_c) }
};
#endif /* TEST_MUSIC */


static char* test_sci()
{
    const char str[] = "ABCabc\r\n";
    unsigned char buf[5] = { 0 };

    SCI_init();
    UTEST_assert("test_sci: SMR != 0", _SCI3.SMR.BYTE == 0);
    UTEST_assert("test_sci: BRR != 0x20", _SCI3.BRR == 0x20);
    UTEST_assert("test_sci: PMR1 != 1", _IO.PMR1.BIT.TXD == 1);
    UTEST_assert("test_sci: SCR3 != 0x70", _SCI3.SCR3.BYTE == 0x70);

    UTEST_assert("test_sci: SCI_puts", SCI_puts(str) == (sizeof(str) - 1));
    UTEST_assert("test_sci: SCI_write(1)",
                 SCI_write((_UBYTE*)str, sizeof(str) - 1, _TRUE, -1) ==
                 (sizeof(str) - 1));

    SCI_puts("test_sci: Reading serial port... Press 'q' to quit.\r\n");
    while (buf[0] != 'q')
    {
        if (SCI_read(buf, 1, _FALSE, -1) == 1)
        {
            SCI_write(buf, 1, _FALSE, -1);
        }
    }
    SCI_puts("\r\n");

    _printf("test_sci: ALL OK.\r\n");
    return 0;
}

static char* test_ioctl()
{
    unsigned char val;
    int i;

    IOCTL_init();
    for (i = 0; i < IOCTL_NUM_OF_REG; i++)
    {
        val = IOCTL_get(i);
        UTEST_assert("IOCTL_get", val == 0);

        IOCTL_set(i, 0xf0, 0xaa);
        UTEST_assert("IOCTL_set(a)", IOCTL_get(i) == 0xa0);
        IOCTL_set(i, 0xff, 0xaa);
        UTEST_assert("IOCTL_set(b)", IOCTL_get(i) == 0xaa);
        IOCTL_set(i, 0xff, val);
    }

    return 0;
}

static char* test_led()
{
    LED_INIT;
    UTEST_assert("test_led: LED_INIT", (_IO.PDR8.BYTE & 0x06) == 0x06);

    LED_ON(LED_D5);
    UTEST_assert("test_led: LED_ON(1)", (_IO.PDR8.BYTE & 0x06) == 0x04);
    LED_ON(LED_D6);
    UTEST_assert("test_led: LED_ON(2)", (_IO.PDR8.BYTE & 0x06) == 0x00);

    LED_OFF(LED_D5);
    UTEST_assert("test_led: LED_OFF(1)", (_IO.PDR8.BYTE & 0x06) == 0x02);
    LED_OFF(LED_D6);
    UTEST_assert("test_led: LED_OFF(2)", (_IO.PDR8.BYTE & 0x06) == 0x06);

    LED_TURN(LED_D5);
    UTEST_assert("test_led: LED_TURN(1)", (_IO.PDR8.BYTE & 0x06) == 0x04);
    LED_TURN(LED_D6);
    UTEST_assert("test_led: LED_TURN(2)", (_IO.PDR8.BYTE & 0x06) == 0x00);

    return 0;
}

#ifdef TEST_STDC
static char* test_stdio()
{
    const char* str = "ABCabc";
    const int i = -127;

    _printf("test_stdio:\r\n");
    _printf("test_stdio: %s\r\n", str);
    _printf("test_stdio: %s %d\r\n", str, i);
    _printf("test_stdio: %s %d %u\r\n", str, i, i);
    _printf("test_stdio: %s %d %u %x\r\n", str, i, i, i);
    _printf("test_stdio: %s %d %u %x %%\r\n", str, i, i, i);

    _printf("test_stdio: ALL OK.\r\n");
    return 0;
}

static char* test_stdlib()
{
    const unsigned char ary[4] = { 0x01, 0x01, 0x01, 0x01 };
    char str[5] = { '\0' };
    int num = 0;
    long rand_val = 0;

    _printf("test_stdlib: _msleep(1000) start\r\n");
    _msleep(1000);
    _printf("test_stdlib: _msleep(1000) end\r\n");

    UTEST_assert("test_stdlib: _next_ring(1)", _next_ring(0, 1) == 1);
    UTEST_assert("test_stdlib: _next_ring(2)", _next_ring(0, 0) == 0);

    UTEST_assert("test_stdlib: _prev_ring(1)", _prev_ring(0, 1) == 1);
    UTEST_assert("test_stdlib: _prev_ring(2)", _prev_ring(0, 0) == 0);

    UTEST_assert("test_stdlib: _hash(1)", _hash(0, 5) == 0);
    UTEST_assert("test_stdlib: _hash(2)", _hash(1, 5) == 1);
    UTEST_assert("test_stdlib: _hash(3)", _hash(2, 5) == 2);
    UTEST_assert("test_stdlib: _hash(4)", _hash(3, 5) == 3);
    UTEST_assert("test_stdlib: _hash(5)", _hash(4, 5) == 4);

    UTEST_assert("test_stdlib: _check_sum(1)",
                 _check_sum(ary, sizeof(ary) / sizeof(_UWORD)) == 0x0202U);

    num = _itoa(10, 10, str, _sizeof_array(str));
    UTEST_assert("test_stdlib: _itoa(1)", num == 2);
    str[num] = '\0';
    UTEST_assert("test_stdlib: _itoa(2)", str[0] == 0x31);
    UTEST_assert("test_stdlib: _itoa(3)", str[1] == 0x30);

    num = _itoa(10, 16, str, _sizeof_array(str));
    UTEST_assert("test_stdlib: _itoa(4)", num == 1);
    str[num] = '\0';
    UTEST_assert("test_stdlib: _itoa(5)", str[0] == 0x41);

    num = _itoa(10, 8, str, _sizeof_array(str));
    UTEST_assert("test_stdlib: _itoa(6)", num == 2);
    str[num] = '\0';
    UTEST_assert("test_stdlib: _itoa(7)", str[0] == 0x31);
    UTEST_assert("test_stdlib: _itoa(8)", str[1] == 0x32);

    rand_val = _rand();
    _srand(rand_val);
    UTEST_assert("test_stdlib: _rand, _srand(1)", _rand() != rand_val);

    _printf("test_stdlib: ALL OK.\r\n");
    return 0;
}

static char* test_string()
{
    unsigned char src[32];
    unsigned char dst[32];
    int i;

    UTEST_assert("test_string: _strlen(1)", _strlen("") == 0);
    UTEST_assert("test_string: _strlen(2)", _strlen("aaa") == 3);

    UTEST_assert("test_string: _memset(1)", 
                 _memset(src, 'a', sizeof(src)) == src);
    for (i = 0; i < sizeof(src); i++)
    {
        UTEST_assert("test_string: _memset(2)", src[i] == 'a');
    }

    UTEST_assert("test_string: _memcpy(1)",
                 _memcpy(dst, src, sizeof(src)) == dst);
    for (i = 0; i < sizeof(dst); i++)
    {
        UTEST_assert("test_string: _memcpy(2)", dst[i] == 'a');
    }

    _printf("test_string: ALL OK.\r\n");
    return 0;
}
#endif /* TEST_STDC */

#ifdef TEST_ASSERT
static char* test_assert()
{
    _assert(_TRUE);
    _assert(_FALSE);

    return 0;
}
#endif /* TEST_ASSERT */

#ifdef TEST_LCD
static char* test_lcd()
{
    int i;
    unsigned char buf[LCD_MAX_COLS * LCD_MAX_ROWS];
    int x, y;
    unsigned char ch[LCD_CG_ROWS] = { 0 };

    LCD_init();
    UTEST_assert("test_lcd: LCD_init(1)",
                 LCD_read(buf, sizeof(buf)) == sizeof(buf));
    for (i = 0; i < sizeof(buf); i++)
    {
        UTEST_assert("test_lcd: LCD_init(2)", buf[i] == ' ');
    }

    LCD_setCursor(0, 0);
    LCD_getCursor(&x, &y);
    UTEST_assert("test_lcd: LCD_(set|get)Cursor(1)", (x == 0) && (y == 0));
    LCD_setCursor(LCD_MAX_COLS, LCD_MAX_ROWS);
    LCD_getCursor(&x, &y);
    UTEST_assert("test_lcd: LCD_(set|get)Cursor(2)", (x == 0) && (y == 0));

    LCD_setCursor(0, 0);
    LCD_puts("aaa\n");
    LCD_getCursor(&x, &y);
    UTEST_assert("test_lcd: LCD_(set|get)Cursor(3)", (x == 0) && (y == 1));

    LCD_setCursor(0, 0);
    UTEST_assert("test_lcd: LCD_puts(1)", LCD_read(buf, 3) == 3);
    UTEST_assert("test_lcd: LCD_puts(2)",
                 (buf[0] == 'a') && (buf[1] == 'a') && (buf[2] == 'a'));
    
    LCD_setCursor(0, 0);
    _memset(buf, 'a', sizeof(buf));
    UTEST_assert("test_lcd: LCD_write(1)",
                 LCD_write(buf, sizeof(buf)) == sizeof(buf));

    LCD_setCursor(0, 0);
    _memset(buf, 0, sizeof(buf));
    UTEST_assert("test_lcd: LCD_read(1)",
                 LCD_read(buf, sizeof(buf)) == sizeof(buf));
    for (i = 0; i < sizeof(buf); i++)
    {
        UTEST_assert("test_lcd: LCD_read(2)", buf[i] == 'a');
    }

    for (i = 0; i < LCD_CG_MAXCHAR; i++)
    {
        LCD_setChar(i, ch);
        buf[i] = i;
        ch[0]++;
    }

    LCD_setCursor(0, 0);
    UTEST_assert("test_lcd: LCD_write(1)",
                 LCD_write(buf, LCD_CG_MAXCHAR) == LCD_CG_MAXCHAR);

    _printf("test_lcd: ALL OK.\r\n");
    return 0;
}
#endif /* TEST_LCD */

#ifdef TEST_PUSH_SWITCH
static char* test_push_switch()
{
    int i;

    PSW_init(_FALSE);

    _printf("test_push_switch: Please push S1\r\n");
    while (!PSW_snapShot(PSW_SW1));
    UTEST_assert("test_push_switch: PSW_oneShot(1)", PSW_oneShot(PSW_SW1));
    UTEST_assert("test_push_switch: PSW_oneShot(2)", !PSW_oneShot(PSW_SW1));
    UTEST_assert("test_push_switch: PSW_get(1)", PSW_get(PSW_SW1));
    for (i = 1; i < PSW_BORDER; i++)
    {
        UTEST_assert("test_push_switch: PSW_get(2)", !PSW_get(PSW_SW1));
    }
    UTEST_assert("test_push_switch: PSW_get(3)", PSW_get(PSW_SW1));
    _printf("test_push_switch: Please release S1\r\n");
    while (PSW_snapShot(PSW_SW1));
    UTEST_assert("test_push_switch: PSW_get(4)", !PSW_get(PSW_SW1));
    UTEST_assert("test_push_switch: PSW_oneShot(3)", !PSW_oneShot(PSW_SW1));

    _printf("test_push_switch: Please push S2\r\n");
    while (!PSW_snapShot(PSW_SW2));
    UTEST_assert("test_push_switch: PSW_oneShot(4)", PSW_oneShot(PSW_SW2));
    UTEST_assert("test_push_switch: PSW_oneShot(5)", !PSW_oneShot(PSW_SW2));
    UTEST_assert("test_push_switch: PSW_get(5)", PSW_get(PSW_SW2));
    for (i = 1; i < PSW_BORDER; i++)
    {
        UTEST_assert("test_push_switch: PSW_get(6)", !PSW_get(PSW_SW2));
    }
    UTEST_assert("test_push_switch: PSW_get(7)", PSW_get(PSW_SW2));
    _printf("test_push_switch: Please release S1\r\n");
    while (PSW_snapShot(PSW_SW2));
    UTEST_assert("test_push_switch: PSW_get(8)", !PSW_get(PSW_SW2));
    UTEST_assert("test_push_switch: PSW_oneShot(6)", !PSW_oneShot(PSW_SW2));

    _printf("test_push_switch: ALL OK.\r\n");
    return 0;
}
#endif /* TEST_PUSH_SWITCH */

#ifdef TEST_ADC
static char* test_adc()
{
    unsigned char buf = 0;
    long val = -1;

    ADC_init(ADC_NORMAL, _FALSE);

    ADC_enable(ADC_AN0);

    _printf("test_adc: Please set RV3 to max left.\r\n");
    _printf("test_adc: Press 'q' to ready.\r\n");
    do
    {
        SCI_read(&buf, 1, _FALSE, -1);
    }
    while (buf != 'q');
    buf = 0;

    ADC_start();
    do
    {
        val = ADC_get(ADC_AN0, _TRUE);
    }
    while (val < 0);

    UTEST_assert("test_adc: ADC_get(1)", val == 0);
    UTEST_assert("test_adc: ADC_get(2)", ADC_get(ADC_AN0, _TRUE) < 0);

    ADC_enable(ADC_AN1);

    _printf("test_adc: Please set RV2 to max left.\r\n");
    _printf("test_adc: Press 'q' to ready.\r\n");
    do
    {
        SCI_read(&buf, 1, _FALSE, -1);
    }
    while (buf != 'q');
    buf = 0;

    ADC_start();
    do
    {
        val = ADC_get(ADC_AN1, _TRUE);
    }
    while (val < 0);

    UTEST_assert("test_adc: ADC_get(3)", val == 0);
    UTEST_assert("test_adc: ADC_get(4)", ADC_get(ADC_AN1, _TRUE) < 0);

    ADC_disable(ADC_AN0);
    ADC_disable(ADC_AN1);
    UTEST_assert("test_adc: ADC_get(5)", ADC_get(ADC_AN0, _TRUE) < 0);
    UTEST_assert("test_adc: ADC_get(6)", ADC_get(ADC_AN1, _TRUE) < 0);

    ADC_init(ADC_SCAN, _FALSE);
    ADC_enable(ADC_AN1);
    ADC_start();

    _printf("test_adc: Please set RV3 to max right.\r\n");
    _printf("test_adc: Press 'q' to ready.\r\n");
    do
    {
        SCI_read(&buf, 1, _FALSE, -1);
    }
    while (buf != 'q');
    buf = 0;

    do
    {
        val = ADC_get(ADC_AN0, _FALSE);
    }
    while (val < 0);
    UTEST_assert("test_adc: ADC_get(7)", val == ((1U << 9) - 1));

    _printf("test_adc: Please set RV2 to max right.\r\n");
    _printf("test_adc: Press 'q' to ready.\r\n");
    do
    {
        SCI_read(&buf, 1, _FALSE, -1);
    }
    while (buf != 'q');
    buf = 0;

    do
    {
        val = ADC_get(ADC_AN1, _TRUE);
    }
    while (val < 0);
    UTEST_assert("test_adc: ADC_get(8)", val == ((1U << 9) - 1));

    ADC_stop();
    UTEST_assert("test_adc: ADC_get(9)", ADC_get(ADC_AN0, _TRUE) < 0);
    UTEST_assert("test_adc: ADC_get(10)", ADC_get(ADC_AN1, _TRUE) < 0);

    ADC_disable(ADC_AN1);

    _printf("test_adc: ALL OK.\r\n");
    return 0;
}
#endif /* TEST_ADC */

#ifdef TEST_PS2
static char* test_ps2()
{
    unsigned char buf[3];

    PS2_init();

    _printf("test_ps2: One shot PS/2 keybord.\r\n");
    UTEST_assert("test_ps2: PS2_read(1)",
                 PS2_read(buf, sizeof(buf), _TRUE, -1) == sizeof(buf));
    _printf("test_ps2: %x %x %x\r\n", buf[0], buf[1], buf[2]);

    _printf("test_ps2: Press PS/2 keybord... 'q' to quit.\r\n");
    while (buf[0] != KBD_JP106_Q)
    {
        if (PS2_read(buf, 1, _FALSE, -1) == 1)
        {
            _printf("%x ", buf[0]);
        }
    }
    _printf("\r\n");

    _printf("test_ps2: ALL OK.\r\n");
    return 0;
}
#endif /* TEST_PS2 */

#ifdef TEST_SOUND
static char* test_sound()
{
    SOUND_Tone tone = { SOUND_C0, &ENVELOPE_harp, NULL, _FALSE };

    SOUND_init();

    UTEST_assert("test_sound: SOUND_init", SOUND_getState() == SOUND_ST_STOP);
    
    _printf("test_sound: Pronounce C0 no reverb and no loop. \r\n");
    SOUND_setTone(0, &tone);
    UTEST_assert("test_sound: SOUND_play", SOUND_play() == _TRUE);
    _msleep(500);
    _printf("test_sound: Stop. \r\n");
    SOUND_removeTone(0);
    UTEST_assert("test_sound: SOUND_stop", SOUND_stop() == _TRUE);
    _msleep(500);
    
    _printf("test_sound: Pronounce C0 reverb on and no loop. \r\n");
    tone.reverb = &ENVELOPE_harp_reverb;
    UTEST_assert("test_sound: SOUND_play", SOUND_play() == _TRUE);
    SOUND_setTone(0, &tone);
    _msleep(1000);
    _printf("test_sound: Stop. \r\n");
    UTEST_assert("test_sound: SOUND_stop", SOUND_stop() == _TRUE);
    _msleep(100);

    _printf("test_sound: Pronounce C0 reverb on and loop on. \r\n");
    tone.loop = _TRUE;
    SOUND_setTone(0, &tone);
    UTEST_assert("test_sound: SOUND_play", SOUND_play() == _TRUE);
    _msleep(500);
    _printf("test_sound: Volume to 0. \r\n");
    SOUND_setVolume(0);
    _msleep(500);
    _printf("test_sound: Volume to max. \r\n");
    SOUND_setVolume(SOUND_MAX_VOLUME);
    _msleep(500);
    _printf("test_sound: Volume to default. \r\n");
    SOUND_setVolume(128);
    _msleep(500);
    _printf("test_sound: Stop. \r\n");
    SOUND_removeTone(0);
    _msleep(100);

    _printf("test_sound: Reverse C0 reverb on and loop on. \r\n");
    UTEST_assert("test_sound: SOUND_reverse", SOUND_reverse() == _TRUE);
    SOUND_setTone(0, &tone);
    _msleep(1000);
    _printf("test_sound: Stop. \r\n");
    SOUND_removeTone(0);
    _msleep(100);

    _printf("test_sound: Pronounce chord (C0, D0) \r\n");
    UTEST_assert("test_sound: SOUND_play", SOUND_play() == _TRUE);
    tone.loop = _FALSE;
    SOUND_setTone(0, &tone);
    tone.freq = SOUND_D0;
    SOUND_setTone(1, &tone);
    _msleep(1000);
    _printf("test_sound: Stop. \r\n");
    SOUND_removeTone(0);
    SOUND_removeTone(1);
    UTEST_assert("test_sound: SOUND_stop", SOUND_stop() == _TRUE);
    _msleep(100);

    _printf("test_sound: Pronounce chord (C0, D0, E0) \r\n");
    tone.freq = SOUND_C0;
    SOUND_setTone(0, &tone);
    tone.freq = SOUND_D0;
    SOUND_setTone(1, &tone);
    tone.freq = SOUND_E0;
    SOUND_setTone(2, &tone);
    UTEST_assert("test_sound: SOUND_play", SOUND_play() == _TRUE);
    _msleep(1000);
    _printf("test_sound: Stop. \r\n");
    SOUND_stop();
    _msleep(100);

    _printf("test_sound: Reverse chord (C0, D0, E0)\r\n");
    tone.freq = SOUND_C0;
    SOUND_setTone(0, &tone);
    tone.freq = SOUND_D0;
    SOUND_setTone(1, &tone);
    tone.freq = SOUND_E0;
    SOUND_setTone(2, &tone);
    UTEST_assert("test_sound: SOUND_reverse", SOUND_reverse() == _TRUE);
    _msleep(1000);
    _printf("test_sound: Stop. \r\n");
    UTEST_assert("test_sound: SOUND_stop", SOUND_stop() == _TRUE);
    _msleep(100);

    SOUND_removeTone(0);
    SOUND_removeTone(1);
    SOUND_removeTone(2);

    _printf("test_sound: ALL OK.\r\n");
    return 0;
}
#endif /* TEST_SOUND */

#ifdef TEST_MUSIC
static char* test_music()
{
    SOUND_Tone tone = {
        SOUND_NA, &ENVELOPE_harp, &ENVELOPE_harp_reverb, _FALSE
    };
    MUSIC_Score score = { ts_parts, 0 };
    MUSIC_RecordReqId rec_id[3];

    MUSIC_init();
    SOUND_setVolume(16);
    UTEST_assert("test_music: MUSIC_init", MUSIC_getState() == MUSIC_ST_STOP);

    _printf("test_music: Playing single part score. \r\n");
    score.size = 1;
    MUSIC_setScore(&score);
    UTEST_assert("test_music: MUSIC_getScore", MUSIC_getScore() == &score);

    UTEST_assert("test_music: MUSIC_play(1)", MUSIC_play() == _TRUE);

    while (MUSIC_getState() != MUSIC_ST_STOP)
    {
        _msleep(500);
    }

    UTEST_assert("test_music: MUSIC_play(2)",
                 MUSIC_getState() == MUSIC_ST_STOP);
    _printf("test_music: Stop. \r\n");

    _printf("test_music: Playing multi part score. \r\n");
    score.size = 3;
    MUSIC_setScore(&score);
    UTEST_assert("test_music: MUSIC_play(1)", MUSIC_play() == _TRUE);

    while (MUSIC_getState() != MUSIC_ST_STOP)
    {
        _msleep(500);
    }

    UTEST_assert("test_music: MUSIC_play(2)",
                 MUSIC_getState() == MUSIC_ST_STOP);
    _printf("test_music: Stop. \r\n");

    _printf("test_music: Reverse. \r\n");
    score.size = 3;
    MUSIC_setScore(&score);
    UTEST_assert("test_music: MUSIC_reverse(1)", MUSIC_reverse() == _TRUE);

    while (MUSIC_getState() != MUSIC_ST_STOP)
    {
        _msleep(500);
    }

    UTEST_assert("test_music: MUSIC_reverse(2)",
                 MUSIC_getState() == MUSIC_ST_STOP);
    _printf("test_music: Stop. \r\n");

    _printf("test_music: Recording start. \r\n");
    UTEST_assert("test_music: MUSIC_record", MUSIC_record() == _TRUE);

    _printf("test_music: Record C0... \r\n");
    tone.freq = SOUND_C0;
    rec_id[0] = MUSIC_recStart(&tone);
    UTEST_assert("test_music: MUSIC_recStart",
                 rec_id[0] != MUSIC_RECREQID_INVALID);
    _msleep(10);
    UTEST_assert("test_music: MUSIC_recStop",
                 MUSIC_recStop(rec_id[0]) != NULL);
    _printf("test_music: Stop C0. rec_id = %d\r\n", rec_id[0]);

    _printf("test_music: Record D0... \r\n");
    tone.freq = SOUND_D0;
    rec_id[0] = MUSIC_recStart(&tone);
    UTEST_assert("test_music: MUSIC_recStart",
                 rec_id[0] != MUSIC_RECREQID_INVALID);
    _msleep(10);
    UTEST_assert("test_music: MUSIC_recStop",
                 MUSIC_recStop(rec_id[0]) != NULL);
    _printf("test_music: Stop D0. rec_id = %d\r\n", rec_id[0]);

    _printf("test_music: Record E0... \r\n");
    tone.freq = SOUND_E0;
    rec_id[0] = MUSIC_recStart(&tone);
    UTEST_assert("test_music: MUSIC_recStart",
                 rec_id[0] != MUSIC_RECREQID_INVALID);
    _msleep(10);
    UTEST_assert("test_music: MUSIC_recStop",
                 MUSIC_recStop(rec_id[0]) != NULL);
    _printf("test_music: Stop E0. rec_id = %d\r\n", rec_id[0]);

    _printf("test_music: Record chord (C0, D0, E0)... \r\n");
    tone.freq = SOUND_C0;
    rec_id[0] = MUSIC_recStart(&tone);
    UTEST_assert("test_music: MUSIC_recStart",
                 rec_id[0] != MUSIC_RECREQID_INVALID);
    tone.freq = SOUND_D0;
    rec_id[1] = MUSIC_recStart(&tone);
    UTEST_assert("test_music: MUSIC_recStart",
                 rec_id[1] != MUSIC_RECREQID_INVALID);
    tone.freq = SOUND_E0;
    rec_id[2] = MUSIC_recStart(&tone);
    UTEST_assert("test_music: MUSIC_recStart",
                 rec_id[2] != MUSIC_RECREQID_INVALID);
    _msleep(10);
    UTEST_assert("test_music: MUSIC_recStop",
                 MUSIC_recStop(rec_id[2]) != NULL);
    UTEST_assert("test_music: MUSIC_recStop",
                 MUSIC_recStop(rec_id[1]) != NULL);
    UTEST_assert("test_music: MUSIC_recStop",
                 MUSIC_recStop(rec_id[0]) != NULL);
    _printf("test_music: Stop (C0, D0, E0). rec_id = %d %d %d\r\n",
            rec_id[0], rec_id[1], rec_id[2]);

    _printf("test_music: Stop recording. play start. \r\n");
    UTEST_assert("test_music: MUSIC_play", MUSIC_play() == _TRUE);
    while (MUSIC_getState() != MUSIC_ST_STOP)
    {
        _msleep(500);
    }

    _printf("test_music: Set loop. once more. \r\n");
    MUSIC_setLoop(_TRUE);
    UTEST_assert("test_music: MUSIC_play", MUSIC_play() == _TRUE);
    _msleep(1000);
    _printf("test_music: Pause. \r\n");
    UTEST_assert("test_music: MUSIC_pause", MUSIC_pause() == _TRUE);
    _msleep(500);
    _printf("test_music: Play. \r\n");
    UTEST_assert("test_music: MUSIC_play", MUSIC_play() == _TRUE);
    _msleep(1000);
    _printf("test_music: Reverse. \r\n");
    UTEST_assert("test_music: MUSIC_reverse", MUSIC_reverse() == _TRUE);
    _msleep(1000);

    _printf("test_music: Stop. \r\n");
    UTEST_assert("test_music: MUSIC_stop", MUSIC_stop() == _TRUE);

    _printf("test_music: ALL OK.\r\n");
    return 0;
}
#endif /* TEST_MUSIC */

#ifdef TEST_SSRP
static char* test_ssrp()
{
    const SSRP_Address myaddr = 0x01;
    SSRP_Header header;
    _UBYTE buf[5] = { 0 };
    _UWORD cnt = 0x10;
    SSRP_Header* hp;
    _UBYTE* bp;

    SSRP_init(myaddr);
    UTEST_assert("test_ssrp: SSRP_init", (SSRP_my_addr[0] == 0x31));

    UTEST_assert("test_ssrp: SSRP_getPear(1)",
                 SSRP_getPear(SSRP_CON_FRONT) == SSRP_ADDR_INVALID);
    UTEST_assert("test_ssrp: SSRP_getPear(2)",
                 SSRP_getPear(SSRP_CON_BACK) == SSRP_ADDR_INVALID);
    UTEST_assert("test_ssrp: SSRP_ready(1)", SSRP_ready() == _FALSE);
    UTEST_assert("test_ssrp: SSRP_getTotalPear(1)", SSRP_getTotalPear() == 0);

    SSRP_start();
    UTEST_assert("test_ssrp: SSRP_getTotalPear(2)", SSRP_getTotalPear() == 1);

    while (cnt--)
    {
        SSRP_exec();
    }

    UTEST_assert("test_ssrp: SSRP_ready(2)", SSRP_ready() == _TRUE);
    UTEST_assert("test_ssrp: SSRP_getPear(3)",
                 SSRP_getPear(SSRP_CON_FRONT) == SSRP_SKEL_LOOPBACK_ADDR);
    UTEST_assert("test_ssrp: SSRP_getPear(4)",
                 SSRP_getPear(SSRP_CON_BACK) == SSRP_SKEL_LOOPBACK_ADDR);
    UTEST_assert("test_ssrp: SSRP_getTotalPear(3)", SSRP_getTotalPear() == 2);

    UTEST_assert("test_ssrp: SSRP_sendto",
                 SSRP_sendto(SSRP_ADDR_BROADCAST, SSRP_CMD_EX, SSRP_FLG_EVT,
                             buf, sizeof(buf), NULL, _TRUE) == sizeof(buf));

    header.from = myaddr;
    header.to = SSRP_ADDR_BROADCAST;
    header.command = SSRP_CMD_EX;
    header.flag = SSRP_FLG_EVT;
    header.data_length = sizeof(buf);

    UTEST_assert("test_ssrp: SSRP_send",
                 SSRP_send(&header, buf, sizeof(buf), _TRUE) == sizeof(buf));

    SSRP_exec();
    UTEST_assert("test_ssrp: SSRP_recvfrom(1)", SSRP_recvfrom(&hp, &bp) >= 0);
    UTEST_assert("test_ssrp: SSRP_recvfrom(2)", 
                 (hp->to == myaddr) || (hp->to == SSRP_ADDR_BROADCAST));
    UTEST_assert("test_ssrp: SSRP_recvfrom(3)",
                 hp->from == SSRP_SKEL_LOOPBACK_ADDR);

    SSRP_end();

    UTEST_assert("test_ssrp: SSRP_getPear(5)",
                 SSRP_getPear(SSRP_CON_FRONT) == SSRP_ADDR_INVALID);
    UTEST_assert("test_ssrp: SSRP_getPear(6)",
                 SSRP_getPear(SSRP_CON_BACK) == SSRP_ADDR_INVALID);
    UTEST_assert("test_ssrp: SSRP_ready(3)", SSRP_ready() == _FALSE);
    UTEST_assert("test_ssrp: SSRP_getTotalPear(4)", SSRP_getTotalPear() == 0);

    _printf("test_ssrp: ALL OK.\r\n");
    return 0;
}
#endif /* TEST_SSRP */

static char* test_run(const UTEST_Func* test_list, _UWORD num)
{
    int i;

    for (i = 0; i < num; i++)
    {
        UTEST_run(test_list[i]);
    }
    return 0;
}

void main(void)
{
    char* result = 0;
    UTEST_Func f;

    result = test_run(test_basic_drivers_, _sizeof_array(test_basic_drivers_));
    if (result != 0)
    {
        while (_TRUE);
    }

    result = test_run(test_drivers_, _sizeof_array(test_drivers_));
    if (result != 0)
    {
        TEST_FAILURE(result);
        goto func_END;
    }

    result = test_run(test_modules_, _sizeof_array(test_modules_));
    if (result != 0)
    {
        TEST_FAILURE(result);
        goto func_END;
    }

    _printf("ALL TESTS PASSED\r\n");

func_END:
    _printf("Tests run: %d\r\n", UTEST_run_count);

    while (_TRUE);
}
