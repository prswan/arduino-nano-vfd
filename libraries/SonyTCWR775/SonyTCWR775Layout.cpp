//
// Copyright (c) 2025, Paul R. Swan
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
#include "SonyTCWR775Layout.h"


static const UINT8 s_manufacturer[] PROGMEM = "SONY";
static const UINT8 s_model[]        PROGMEM = "TC-WR775";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
    DriveTypeSN75518,
};

//
// 8x 7-segment displays in two groups of 4
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
    // sym,        instance, pinG, pinS
    {SymText_DOLBY_NR,    0,    6,    1},
    {SymText_B,           0,    6,    2},
    {SymText_C,           0,    6,    6},
    {SymText_MEMORY,      0,    6,    7},

    {Sym7SegMinus,        0,    5,    8},
    {Sym7SegDecimalPoint, 0,    5,   16},
    {SymText_A_plus_B,    0,    4,   16},
    {SymText_HIGH,        0,    4,   17},
    {SymText_NORM,        0,    4,   18},
    {Sym7SegMinus,        1,    3,    8},
    {Sym7SegDecimalPoint, 1,    3,   16},

    {SymText_DOLBY_NR,    1,    1,    1},
    {SymText_B,           1,    1,    2},
    {SymText_C,           1,    1,    6},
    {SymText_MEMORY,      1,    1,    7},

    {SymPlayReverse,      0,    6,    3},
    {SymPlayForward,      0,    6,    5},
    {SymText_PLAY,        0,    6,    4},
    {SymPause,            0,    6,    8},
    {SymText_REC,         0,    6,    9},

    {SymTextBox_FADE,     0,    6,   10},
    {SymArrowForward,     0,    6,   14},
    {SymArrowReverse,     0,    6,   11},
    {SymText_AUTO_PAUSE,  0,    6,   13},
    {SymText_BLANK_SKIP,  0,    6,   12},

    {SymDotBar123,        0,    8,   18},
    {SymDotBar4,          0,    8,   17},

    {SymPlayReverse,      1,    1,    3},
    {SymPlayForward,      1,    1,    5},
    {SymText_PLAY,        1,    1,    4},
    {SymPause,            1,    1,    8},
    {SymText_REC,         1,    1,    9},

};

//
// 8x 7-segment displays in two groups of 4
// These were documented in the service manual.
//
static const SegmentGroup7Seg s_segmentGroup7Seg0[] PROGMEM =
{
// pinG, { a   b   c   d   e   f   g}}
    { 5, { 1,  2,  3,  4,  5,  6,  7}},
    { 5, { 9, 10, 11, 12, 13, 14, 15}},
    { 4, { 1,  2,  3,  4,  5,  6,  7}},
    { 4, { 9, 10, 11, 12, 13, 14, 15}},
};

static const SegmentGroup7Seg s_segmentGroup7Seg1[] PROGMEM =
{
// pinG, { a   b   c   d   e   f   g}}
    { 3, { 1,  2,  3,  4,  5,  6,  7}},
    { 3, { 9, 10, 11, 12, 13, 14, 15}},
    { 2, { 1,  2,  3,  4,  5,  6,  7}},
    { 2, { 9, 10, 11, 12, 13, 14, 15}},
};

//
// 2x 16-segment bar with segment 1's also lighting the R/L top scale and bottom double D.
//
static const SegmentGroupBar s_segmentGroupBar[] PROGMEM =
{
// vertical, reverse, seg1Symbol, pinG, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16}}
    { false,   false,       true,    7, { 1,  2,  6,  7,  3,  5,  4,  8,  9, 10, 14, 15, 11, 13, 12, 16}},
    { false,   false,       true,    8, { 1,  2,  6,  7,  3,  5,  4,  8,  9, 10, 14, 15, 11, 13, 12, 16}},
};

void SonyTCWR775Layout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void SonyTCWR775Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool SonyTCWR775Layout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool SonyTCWR775Layout::getSegmentGroup7Seg(
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

bool SonyTCWR775Layout::getSegmentGroupBar(
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

