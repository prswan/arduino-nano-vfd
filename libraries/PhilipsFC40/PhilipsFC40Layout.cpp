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
#include "PhilipsFC40Layout.h"

/*
Data
----
This was a loose NOS VFD bought from Surplusgizmos, Hilsboro, OR. They had a box of them.
A little detective work found the simiilar Philips FC-60 for which a service manual exists
and finally the FC-40 that I wasn't able to find a servie manual for. The only VFD difference
seems to be that the FC-40 replaced "TAPE" and "SOURCE" indicators with play direction
indicators.

From the FC-60 service manual:
 - VFIL: 4.3 VAC
 - Vbb: +30  VDC

Onkyo HT-R340 NPT-1516D Transformer
-----------------------------------
 - VFIL @ Controller PCB Input  : 5.28 VAC
 - VFIL @ Controller PL5 2x 2R2 : 4.01 VAC
 - VFIL @ VFD            2x 2R2 : 3.37 VAC
 Display is very bright.
*/

static const UINT8 s_manufacturer[] PROGMEM = "PHILIPS";
static const UINT8 s_model[]        PROGMEM = "FC-40";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
};

//
// 2x 4-digit 7-segment displays in two groups
// 2x 16-segement horizontal bar graphs.
//
static const Region s_region[] PROGMEM =
{
    // type,          subType,               id, len
    {RegionTypeChar,  RegionSubTypeChar7Seg,  0,  4},
    {RegionTypeChar,  RegionSubTypeChar7Seg,  1,  4},
    {RegionTypeBar,   0,                      0,  2},
};


static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,            instance, pinG, pinS
    {SymText_REC,             0,    6,    1}, // row 1
    {SymPlayForward,          0,    3,    2},
    {SymText_HX_PRO,          0,    1,    6},
    {SymText_DOLBY_B,         0,    1,    7},
    {SymText_DOLBY_C,         0,    1,    8},
    {SymText_MPX_F,           0,    1,    9},
    {SymText_NORMAL,          0,    1,   10}, // Also lights the scale marker arrow
    {SymText_CrO2,            0,    1,   11}, // Also lights the scale marker arrow
    {SymText_METAL,           0,    1,   12}, // Also lights the scale marker arrow

    {SymPlayReverse,          0,    3,    3}, // row 2
    {SymText_L,               0,    1,    5}, // This should be part of the Bar handling

    {SymMinus,                0,    6,   21}, // row 3
    {SymText_BLANK_SKIP,      0,    3,    4},
    {SymText_R,               0,    2,    5}, // R and bottom white scale, this should be part of the Bar handling

    {SymDecimalPoint,         0,    5,   21}, // row 4
    {SymText_MEMO,            0,    3,   21},
    {SymText_dB,              0,    2,   13}, // dB and bottom red scale, this should be part of the Bar handling
};

//
// 4x 7-segment display
// These were documented in the service manual.
//
// TODO: There are some extra segments that allow for
//       specific words, e.g. PLAY, STOP, REW, REC etc.
//
// 0329 - region 0 col 4 "Y" segment
// 0429 - region 0 col 3 "W" segment
// 0529 - region 0 col 2 "T" segment
// 0629 - region 0 col 1 "R" segment
//
static const SegmentGroup7Seg s_segmentGroup7Seg0[] PROGMEM =
{
// pinG, { a   b   c   d   e   f   g}}
    { 6, {22, 23, 24, 25, 26, 27, 28}},
    { 5, {22, 23, 24, 25, 26, 27, 28}},
    { 4, {22, 23, 24, 25, 26, 27, 28}},
    { 3, {22, 23, 24, 25, 26, 27, 28}},
};

//
// 4x 7-segment display
// These were documented in the service manual.
//
static const SegmentGroup7Seg s_segmentGroup7Seg1[] PROGMEM =
{
// pinG, { a   b   c   d   e   f   g}}
    { 6, {14, 15, 16, 17, 18, 19, 20}},
    { 5, {14, 15, 16, 17, 18, 19, 20}},
    { 4, {14, 15, 16, 17, 18, 19, 20}},
    { 3, {14, 15, 16, 17, 18, 19, 20}},
};

//
// 2x 16-segment bar with separate scale segments
// These were documented in the service manual as "t1" to "t16" but 
// missing the translation to "a" - "p" actual segment pins.
// LayoutFinder to the recue! 
//
// TODO: 10 white plus 6 red, express that somehow?
//
static const SegmentGroupBar s_segmentGroupBar[] PROGMEM =
{
//    horz., vert.,   reverse, seg1Symbol, pinG, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16}}
    { true,  false,   false,   false,         1, {14, 25, 26, 29, 24, 28, 27, 23, 22, 21, 17, 18, 16, 20, 19, 15}},
    { true,  false,   false,   false,         2, {14, 25, 26, 29, 24, 28, 27, 23, 22, 21, 17, 18, 16, 20, 19, 15}},
};

void PhilipsFC40Layout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void PhilipsFC40Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool PhilipsFC40Layout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool PhilipsFC40Layout::getSegmentGroup7Seg(
    UINT8 regionId,
    const SegmentGroup7Seg **p_segGroup,
    UINT8 *numEntries)
{
    switch (regionId)
    {
        case 0:
        {
            *p_segGroup = s_segmentGroup7Seg0;
            *numEntries = ARRAYSIZE(s_segmentGroup7Seg0);
            break;
        }

        case 1:
        {
            *p_segGroup = s_segmentGroup7Seg1;
            *numEntries = ARRAYSIZE(s_segmentGroup7Seg1);
            break;
        }

        default:
        {
            return false;
        }
    }

    return true;
}

bool PhilipsFC40Layout::getSegmentGroupBar(
    UINT8 regionId,
    const SegmentGroupBar **p_segGroup,
    UINT8 *numEntries)
{
    if (regionId != 0)
    {
        return false;
    }

    *p_segGroup = s_segmentGroupBar;
    *numEntries = ARRAYSIZE(s_segmentGroupBar);

    return true;
}
