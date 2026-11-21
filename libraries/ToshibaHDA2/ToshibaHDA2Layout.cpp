//
// Copyright (c) 2026, Paul R. Swan
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR
// TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
#include "ToshibaHDA2Layout.h"

/*
Data
----
Original player measurements:
 - VFIL: 3.96 VDC
 - Vbb: -27 VDC

Insignia NS-R2001 Transformer
-----------------------------
 - VFIL @ Controller PCB Input  : 4.00 VAC
 - VFIL @ Controller PL0 2x  0R : 3.82 VAC
 - VFIL @ VFD            2x  0R : 3.71 VAC
This transformer starts with 4.00VAC at the input but after the fuses,
PCB traces and a long 50cm cable to the VFD, the voltage drops to 3.71VAC at the VFD.
The display is dim and uneven, though the uneveness improved after warming up for a few minutes.
Cross checking with the photo taken whilst in the player, it was also dim and uneven.
It may benefit from a rejuve.
*/

static const UINT8 s_manufacturer[] PROGMEM = "TOSHIBA";
static const UINT8 s_model[]        PROGMEM = "HD-A2";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
};

//
// 13x 14-segment standard display.
// The manual didn't document the layout, reverse engineered using the LayoutFinder.
//
static const Region s_region[] PROGMEM =
{
    // type,          subType,                id, len
    {RegionTypeChar,  RegionSubTypeChar14Seg,  0,  13}
};

static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
    {SymPlayForward,      0,    1,   18}, // row 1
    {SymPause,            0,    1,   17},
    {SymText_HD,          0,    2,   18},
    {SymText_DVD,         0,    2,   17},
    {SymText_minus_A,     0,    2,   16},
    {SymText_ADV,         0,    4,   18},
    {SymText_SACD,        0,    5,   18},
    {SymText_S,           0,    6,   18},
    {SymText_V,           0,    6,   17},
    {SymText_CD,          0,    6,   16},
    {SymText_HDMI,        0,    8,   18},
    {SymText_REMAIN,      0,    9,   18},
    {SymText_2ch,         0,   10,   18},
    {SymText_MEMORY,      0,   12,   18},
    {SymText_A_minus,     0,   13,   18},
    {SymText_B,           0,   13,   17},

    {SymFastForward,      0,    1,   16}, // row 2
    {SymText_TITLE,       0,    2,   15},
    {SymText_GROUP,       0,    4,   17},
    {SymText_CHP,         0,    5,   17},
    {SymText_TRK,         0,    6,   15},
    {SymDolbyDoubleD_D,   0,    7,   17},
    {SymText_dts,         0,    8,   17},
    {SymText_TOTAL,       0,    9,   17},
    {SymText_MULTI,       0,   10,   17},
    {SymText_RANDOM,      0,   12,   17},
    {SymRepeat,           0,   13,   16},
    {SymMovieCamera,      0,   14,   18},

    {SymFastReverse,      0,    1,   15}, // row 3
    {SymText_480,         0,    1,   14},
    {SymText_i,           0,    1,   13},
    {SymText_p,           0,    1,   12},

    {SymText_576,         0,    1,   11}, //row 4
    {SymText_i,           1,    1,   10},
    {SymText_p,           1,    1,    9},
    {SymMinus,            0,    4,   15},
    {SymColon,            0,   10,   16},
    {SymColon,            1,   12,   16},

    {SymText_720p,        0,    1,    8}, // row 5+
    {SymText_1080,        0,    1,    7},
    {SymText_i,           2,    1,    6},
    {SymText_p,           2,    1,    5},
};

//
// 13x 14-segment standard display.
// The manual didn't document the layout, reverse engineered using the LayoutFinder.
//
static const SegmentGroup14Seg s_segmentGroup14Seg[] PROGMEM =
{
// pinG, { a   b   c   d   e   f  g1  g2   h   i   j   k   l   m}}
    { 2, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 3, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 4, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 5, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 6, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 7, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 8, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 9, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    {10, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    {11, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    {12, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    {13, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    {14, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
};

void ToshibaHDA2Layout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void ToshibaHDA2Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool ToshibaHDA2Layout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool ToshibaHDA2Layout::getSegmentGroup14Seg(
    UINT8 regionId,
    const SegmentGroup14Seg **p_segGroup,
    UINT8 *numEntries)
{
    if (regionId > 0)
    {
        return false;
    }

    *p_segGroup = s_segmentGroup14Seg;
    *numEntries = ARRAYSIZE(s_segmentGroup14Seg);

    return true;
}
