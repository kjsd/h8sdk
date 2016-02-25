/**
 * @file envelope.c
 *
 * @brief This header file declares the definitions that are Sound Envelope
 * Data.
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
#include "stddef.h"
#include "../include/h8sdk/envelope.h"


static const _UBYTE dataNA_[] = { 0 };

static const _UBYTE dataPiano_[] = {
    12,22,30,41,51,60,67,77,85,94,
    102,109,114,123,129,134,144,151,158,162,
    171,175,179,184,190,195,199,203,208,211,
    217,220,225,229,232,236,240,243,247,250,
    253,255,252,248,245,241,238,235,230,228,
    223,221,218,215,212,210,208,205,203,202,
    199,197,195,193,191,188,187,185,184,182,
    180,178,177,175,174,173,171,169,168,167,
    165,164,162,161,160,159,158,156,156,154,
    153,152,151,150,149,149,148,147,146,145,
    145,144,143,143,142,141,140,140,138,138,
    138,137,136,136,135,134,134,133,133,132,
    132,132,131,131,130,130,130,129,129,129,
    128,128,127,127,127,127,126,126,126,125,
    125,125,125,124,124,123,123,123,123,123,
    122,121,121,121,121,121,121,121,121,121,
    121,119,119,119,119,119,119,119,119,119,
    119,119,119,119,119,119,117,117,117,117,
    117,117,117,117,117,117,117,117,116,116,
    116,116
};
static const _UBYTE dataPianoReverb_[] = {
    109,103,98,93,87,84,79,75,71,68,
    63,61,57,54,52,49,47,45,43,40,
    38,36,35,33,31,30,29,26,26,25,
    24,23,22,20,20,18,18,17,16,15,
    15,14,14,13,12,12,11,10,10,10,
    10,8,8,8,8,8,8,7,6,6,
    6,5,5,6,5,5,4,4,4,4,
    3,3,3,3,3,3,3,2,2,2,
    2,2,2,2,2,1,1,1,1,1,
    1,1,1,1,1,0
};

static const _UBYTE dataFlute_[] = {
    0,0,0,0,0,0,0,14,17,17,
    17,18,28,47,46,64,75,76,75,86,
    87,89,98,97,108,112,119,132,133,134,
    133,133,133,133,135,134,133,123,121,121,
    121,121,121,121,121,121,121,122,122,132,
    133,133,133,133,143,145,146,145,145,145,
    145,145,145,145,145,143,134,133,133,133,
    133,133,133,133,133,133,133,133,135,145,
    154,155,143,144,145,146,156,147,145,143,
    145,145,145,145,145,145,145,145,145,145,
    145,145,146,146,157,156,158,157,157,157,
    157,157,156,157,156,154,138,135,133,133,
    144,143,145,145,145,145,144,146,153,157,
    168,178,181,181,189,193,193,202,203,193,
    190,181,180,181,178,174,169,158,156,150,
    146,144,145,145,145,145,146,146,155,154,
    146,144,144,147,156,155,157,157,157,157,
    157,157,157,157,157,157,160,167,168,175,
    181,182,189,190,190,182,181,179,179,179,
    172,167,159,153,146,143,141,133,133,133,
    133,133,134,138,143,145,143,150,156,156,
    162,167,169,171,178,181,181,179,179,179,
    177,170,167,168,166,159,158,157,157,167,
    167,169,167,158,158,156,158,164,168,169,
    161,157,157,157,154,146,146,143,145,143,
    145,153,157,166,168,175,181,190,194,202,
    204,202,203,204,204,212,214,205,202,202,
    194,181,179,168,157,150,144,144,143,146,
    155,150,144,145,143,154,155,158,155,156,
    155,158,158,168,179,170,168,168,168,168,
    168,168,168,168,169,169,169,181,189,191,
    181,179,181,181,191,191,190,181,170,168,
    168,169,159,157,146,144,145,145,145,145,
    145,146,144,144,156,156,157,167,177,181,
    191,192,208,208,226,226,225,215,205,202,
    190,181,180,178,169,169,167,157,157,156,
    145,145,145,145,145,145,145,145,145,157,
    156,146,144,143,144,157,157,157,157,157,
    157,157,157,157
};
static const _UBYTE dataFluteReverb_[] = {
    155,156,155,158,158,168,179,170,168,168,
    168,168,168,168,168,168,169,169,169,181,
    189,191,181,179,181,181,191,191,190,181,
    170,168,168,169,159,157,146,144,145,145,
    145,145,145,146,144,144,156,156,157,167,
    177,181,191,192,208,208,226,226,225,215,
    205,202,190,181,180,178,169,169,167,157,
    157,156,145,145,145,145,145,145,145,145,
    145,157,156,146,144,143,144,157,157,157,
    157,157,157,157,157,157
};

static const _UBYTE dataDrum_[] = {
    104,104,104,203,203,203,162,162,162,122,
    122,122,87,87,75,75,75,58,58,58,
    29,29,29,40,40,40,40,40,17,17,
    17,17,17,17,17,17,17,17,17,17,
    17,17,17,17,17,5,5,5,
};

static const _UBYTE dataTrumpet_[] = {
    11,11,81,145,145,186,238,238,238,226,
    226,226,226,226,226,226,226,226,226,226,
    226,226,226,238,238,238,226,215,215,215,
    215,215,203,203,203,203,203,203,203,203,
    203,203,203,215,215,203,203,203,203,203,
    203,203,203,203,203,203,203,203,203,203,
    203,203,203,203,203,203,203,203,203,203,
    203,203,203,203,203,203,203,203,203,203,
    215,215,215,203,203,203,203,203,203,215,
    203,203,203,203,203,203,203,203,203,203,
    203,203,203,203,203,215,203,203,203,203,
    203,203,203,203,203,203,203,203,191,191,
    191,191,203,203,203,203,203,203,203,203,
    203,203,191,191,191,191,191,191,191,203,
    191,191,191,191,191,191,191,191,191,203,
    203,203,203,203,203,203,203,203,203,203,
    203,203,203,191,191,191,191,191,191,191,
    191,191,191,191,191,203,203,203,203,203,
    203,203,203,203,203,203,203,203,203,203,
    203,203,191,191,191,191,191,191,191,191,
    191,191,191,191,191,191,203,203,203,191,
    191,191,191,191,191,191,203,203,203,203,
    203,203,203,191,191,191,191,191,191,191,
    191,191,191,191,191,191,191,191,191,191,
    191,191,191,191,203,203,203,203,191,191,
    191,191,203,203,203,203,203,203,203,203,
    203,191,191,191,191,191,191,191,203,203,
    203,203,203,203,203,203,203,203,203,203,
    203,203,203,203,203,191,191,191,191,191,
    191,191,191,191,191,191,191,191,191,191,
    191,191,191,191,191,191,191,191,191,191,
    191,191,191,191,191,203,203,203,203,203,
    203,203,203,203,203,203,203,203,203,203,
    203,203,203,203,203,203,203,203,203,203,
    203,203,203,203,203,203,203,215,203,203,
    203,203,191,191,191,191,191,191,191,191,
    191,191,191,191,191,191,191,191,203,203,
    203,203,203,203,191,191,191,191,191,191,
    191,191,191,191
};
static const _UBYTE dataTrumpetReverb_[] = {
    191,191,191,191,191,191,191,191,191,191,
    191,191,191,191,191,191,191,191,191,191,
    191,191,191,191,191,203,203,203,203,203,
    203,203,203,203,203,203,203,203,203,203,
    203,203,203,203,203,203,203,203,203,203,
    203,203,203,203,203,203,203,215,203,203,
    203,203,191,191,191,191,191,191,191,191,
    191,191,191,191,191,191,191,191,203,203,
    203,203,203,203,191,191,191,191,191,191,
    191,191,191,191,191
};

static const _UBYTE dataHarp_[] = {
    6, 22, 37, 68, 100, 116, 147, 163, 194, 225,
    234, 255
};
static const _UBYTE dataHarpReverb_[] = {
    255,249,240,237,233,228,224,224,219,215,210,206,202,198,195,190,187,183,
    180,176,176,173,171,167,164,161,159,156,153,150,148,146,143,143,141,139,
    137,135,133,132,129,128,126,124,124,121,121,119,118,116,115,114,112,110,
    109,109,107,106,105,105,103,102,101,100,99,98,97,95,95,94,93,92,92,91,91,
    89,89,88,87,86,86,84,84,83,82,82,82,81,80,79,79,78,77,76,76,75,74,75,75,
    74,73,73,72,72,71,70,69,68,69,67,68,68,68,67,66,66,65,65,65,64,63,63,63,
    62,62,62,61,61,60,60,60,60,59,59,58,57,56,56,57,56,56,55,55,55,54,54,53,
    54,53,53,53,53,52,52,52,51,51,51,50,50,50,49,49,49,49,49,49,48,48,48,47,
    47,46,47,46,46,46,45,46,45,45,45,45,44,44,44,44,43,43,43,43,43,42,43,41,
    41,41,41,41,40,41,40,40,40,40,40,39,39,39,39,38,39,38,38,38,38,38,38,37,
    37,37,37,37,36,36,36,36,36,36,36,35,35,35,35,35,35,34,35,34,34,34,34,34,
    33,33,33,33,33,33,32,32,33,32,32,32,32,32,31,32,31,31,31,31,31,31,31,30,
    30,30,30,30,30,29,30,30,29,30,29,29,29,29,29,29,28,28,28,28,28,27,28,27,
    27,27,27,27,27,27,27,26,26,26,26,26,26,26,26,26,25,26,26,25,25,25,25,25,
    25,24,24,25,25,24,24,24,24,24,24,24,23,24,23,23,23,23,23,23,23,23,23,23,
    23,23,22,23,22,22,22,22,22,22,22,22,22,22,21,22,22,21,21,21,21,21,21,21,
    20,20,21,21,20,21,20,20,20,20,20,20,20,20,20,19,19,19,19,19,19,19,19,19,
    19,19,19,18,18,18,19,19,19,18,18,18,18,18,18,18,18,18,17,17,17,18,17,17,
    17,18,17,17,17,17,17,17,17,17,16,16,16,16,16,17,17,16,17,16,16,16,16,16,
    16,16,16,16,15,15,15,15,16,15,16,15,15,15,15,15,15,15,15,15,15,14,15,14,
    15,14,15,14,14,14,13,14,13,14,13,14,13,13,13,13,13,13,13,13,13,13,13,13,
    13,13,13,13,13,13,13,13,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,
    12,12,12,12,11,11,11,11,11,11,11,11,11,11,11,11,10,10,11,10,11,11,10,11,
    11,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,
    9,9,9,9,9,9,9,9,9,9,9,9,9,8,8,9,9,9,9,9,9,9,8,8,8,8,8,8,8,8,8,8,8,8,8,7,
    8,8,8,8,8,7,8,8,7,8,7,7,7,7,7,7,7,7,7,7,7,7,7,6,6,6,6,6,6,6,6,6,6,7,6,6,
    6,6,6,6,6,6,6,6,6,6,6,6,5,6,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
    4,4,5,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,
    3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,3,2,2,2,2,2,2,2,2,2,3,2,2,2,2,2,2,
    2,2,2,2,2,2,2,2,1,2,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

const SOUND_Envelope ENVELOPE_na = {
    dataNA_, _sizeof_array(dataNA_)
};
const SOUND_Envelope ENVELOPE_piano = {
    dataPiano_, _sizeof_array(dataPiano_)
};
const SOUND_Envelope ENVELOPE_piano_reverb = {
    dataPianoReverb_, _sizeof_array(dataPianoReverb_)
};
const SOUND_Envelope ENVELOPE_flute = {
    dataFlute_, _sizeof_array(dataFlute_)
};
const SOUND_Envelope ENVELOPE_flute_reverb = {
    dataFluteReverb_, _sizeof_array(dataFluteReverb_)
};
const SOUND_Envelope ENVELOPE_drum = {
    dataDrum_, _sizeof_array(dataDrum_)
};
const SOUND_Envelope ENVELOPE_trumpet = {
    dataTrumpet_, _sizeof_array(dataTrumpet_)
};
const SOUND_Envelope ENVELOPE_trumpet_reverb = {
    dataTrumpetReverb_, _sizeof_array(dataTrumpetReverb_)
};
const SOUND_Envelope ENVELOPE_harp = {
    dataHarp_, _sizeof_array(dataHarp_)
};
const SOUND_Envelope ENVELOPE_harp_reverb = {
    dataHarpReverb_, _sizeof_array(dataHarpReverb_)
};
