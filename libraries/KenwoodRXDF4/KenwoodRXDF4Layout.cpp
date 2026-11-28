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
#include "KenwoodRXDF4Layout.h"

static const UINT8 s_manufacturer[] PROGMEM = "KENWOOD";
static const UINT8 s_model[]        PROGMEM = "RXD-F4";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
};

//
// The display layout follows the service-manual display drawing and electrode maps.
//
static const Region s_region[] PROGMEM =
{
    // type,                subType,                id, len
    {RegionTypeBar,         0,                       0,   7},
    {RegionTypeBar,         0,                       1,   1},
    {RegionTypeNumberList,  0,                       0,   1},
    {RegionTypeNumberList,  0,                       1,   1},
    {RegionTypeChar,        RegionSubTypeChar14Seg,  0,   6},
    {RegionTypeChar,        RegionSubTypeChar7Seg,   1,   4}
};

//
// Number list region 0 is enclosed in circles with down arrows above the numbers.
// TODO: Number-list highlight support is missing. Add the circle and down-arrow
//       highlights as symbol instances 0, 1, and 2.
//
// The symbol table is in approximate row order, left to right and top to bottom.
static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,                 instance, pinG, pinS
    {SymText_PRESENCE,      0,        1,    34}, // row 1
    {SymText_NB,            0,        2,    34},
    {SymText_DISC_ALL,      0,        3,    34},
    {SymArrowHeadDown,      0,        4,    35},
    {SymCircle,             0,        4,    36},
    {SymArrowHeadDown,      1,        5,    35},
    {SymCircle,             1,        5,    36},
    {SymArrowHeadDown,      2,        6,    34},
    {SymCircle,             2,        6,    37},
    {SymBox,                0,        6,    36},
    {SymBox,                1,        6,    34},
    {SymText_A,             0,        6,    35},
    {SymText_B,             0,        6,    35},
    {SymText_LLC,           0,        7,    36},

    {SymText_SURROUND,      0,        1,    35}, // row 2
    {SymArrowHeadForward,   0,        2,    35},
    {SymPause,              0,        2,    36},
    {SymText_REPEAT,        0,        3,    32},
    {SymText_MEMO,          0,        4,    30},
    {SymText_TUNED,         0,        5,    40},
    {SymArrowHeadReverse,   0,        6,    37},
    {SymArrowHeadForward,   1,        6,    38},
    {SymArrowHeadReverse,   1,        6,    39},
    {SymArrowHeadForward,   2,        6,    40},
    {SymText_ECHO,          0,        7,    37},

    {SymText_3_STEREO,      0,        1,    36}, // row 3
    {SymText_PGM,           0,        2,    38},
    {SymText_RND,           0,        3,    24},
    {SymText_AUTO,          0,        4,    29},
    {SymText_ST,            0,        5,    32},
    {SymText_PROGRAM,       0,        6,    31},
    {SymRepeat,             0,        6,    29},
    {SymCircle,             3,        6,    31},
    {SymVerticalLine,       0,        6,    30},
    {SymVerticalLine,       1,        6,    32},
    {SymArrowHeadReverse,   2,        6,    33},
    {SymText_EQ_ON,         0,        2,    39}, // row 4
    {SymText_MUTING,        0,        3,    23},
    {SymText_SLEEP,         0,        6,    33},
    {SymText_DOLBY_NR,      0,        7,    40},
    {SymText_B,             1,        7,    31},
    {SymText_C,             0,        7,    30},

    {SymText_OTE,           0,        2,    37}, // row 5
    {SymText_EDIT,          0,        2,    40},
    {SymText_VOL,           0,        3,    13},
    {SymText_1,             0,        5,    30},
    {SymText_2,             0,        5,    29},
    {SymText_1,             1,        6,    30},
    {SymText_2,             1,        6,    29},
    {SymText_AM,            0,        7,    23},
    {SymText_PM,            0,        7,    21},
    {SymText_SINGLE,        0,        7,    20},
    {SymText_TOTAL,         0,        8,    19},
    {SymColon,              0,        7,     2},

    {SymDotBar,             0,        3,     1}, // volume scale
    {SymText_1,             1,        7,    20}, // leading "1" indicators
    {SymText_1,             2,        8,    19},
    {SymText_ms,            0,        8,     4},
    {SymText_dB,            0,        8,     3},
    {SymText_KHz,           0,        8,     2},
    {SymText_MHz,           0,        8,     1}
};

//
// Seven 11-segment vertical bars. The three electrode groups in the manual's
// bar chart are shared between grids 1 and 2; grid 3 also has the remaining bar.
//
static const SegmentGroupBar s_segmentGroupBar0[] PROGMEM =
{
//    horz., vert., reverse, seg1Symbol, pinG, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11}
    { false, true,  false,   false,        1, { 3,  6,  9, 12, 15, 18, 21, 24, 27, 30, 33}},
    { false, true,  false,   false,        1, { 2,  5,  8, 11, 14, 17, 20, 23, 26, 29, 32}},
    { false, true,  false,   false,        1, { 1,  4,  7, 10, 13, 16, 19, 22, 25, 28, 31}},
    { false, true,  false,   false,        2, { 3,  6,  9, 12, 15, 18, 21, 24, 27, 30, 33}},
    { false, true,  false,   false,        2, { 2,  5,  8, 11, 14, 17, 20, 23, 26, 29, 32}},
    { false, true,  false,   false,        2, { 1,  4,  7, 10, 13, 16, 19, 22, 25, 28, 31}},
    { false, true,  false,   false,        3, { 3,  6,  9, 12, 15, 18, 21, 24, 27, 30, 33}}
};

//
// The volume graph has nine segments and rises diagonally from left to right.
//
static const SegmentGroupBar s_segmentGroupBar1[] PROGMEM =
{
//    horz., vert., reverse, seg1Symbol, pinG, { 1,  2,  3,  4,  5,  6,  7,  8,  9}
    { true,  true,  false,   false,        3, {14, 15, 16, 17, 18, 19, 20, 21, 22}}
};

//
// The three circled preset values are on grids 4, 5, and 6.
//
static const SegmentGroupNumberList s_segmentGroupNumberList0[] PROGMEM =
{
    { // numListLen, numCols, numRows, topToBottom
                  3,       3,       1,       false,
        {
            // [] {pinG,{value,pinS},...}
            { 4, {{1,39}}},
            { 5, {{2,38}}},
            { 6, {{3,38}}}
        }
    }
};

//
// The 1-20 number list is laid out in rows, increasing from left to right.
//
static const SegmentGroupNumberList s_segmentGroupNumberList1[] PROGMEM =
{
    { // numListLen, numCols, numRows, topToBottom
                 20,       5,       4,       false,
        {
            // [] {pinG,{value,pinS},...}
            { 8, {{ 1,34},{ 2,35},{ 3,36},{ 4,27},{ 5,23},
                  { 6,37},{ 7,38},{ 8,39},{ 9,26},{10,22},
                  {11,40},{12,33},{13,32},{14,25},{15,21},
                  {16,31},{17,30},{18,28},{19,24},{20,20}}}
        }
    }
};

//
// Six 14-segment characters arranged as pairs on grids 4, 5, and 6.
// The service manual uses different labels for the interior segments:
// g/m are the split centre bar; h/i/k/n/p/r map to Wiki h/i/j/k/l/m.
//
static const SegmentGroup14Seg s_segmentGroup14Seg0[] PROGMEM =
{
// pinG, { a,  b,  c,  d,  e,  f, g1, g2,  h,  i,  j,  k,  l,  m}
    { 4, {14,  9,  2,  1,  6, 13,  8,  7, 12, 10, 11,  4,  3,  5}},
    { 4, {28, 23, 16, 15, 20, 27, 22, 21, 26, 24, 25, 18, 17, 19}},
    { 5, {14,  9,  2,  1,  6, 13,  8,  7, 12, 10, 11,  4,  3,  5}},
    { 5, {28, 23, 16, 15, 20, 27, 22, 21, 26, 24, 25, 18, 17, 19}},
    { 6, {14,  9,  2,  1,  6, 13,  8,  7, 12, 10, 11,  4,  3,  5}},
    { 6, {28, 23, 16, 15, 20, 27, 22, 21, 26, 24, 25, 18, 17, 19}}
};

//
// Four 7-segment characters arranged as pairs on grids 7 and 8.
//
static const SegmentGroup7Seg s_segmentGroup7Seg1[] PROGMEM =
{
// pinG, { a,  b,  c,  d,  e,  f,  g}
    { 7, {11, 10,  6,  5,  7,  9,  8}},
    { 7, {18, 17, 13, 12, 14, 16, 15}},
    { 8, {11, 10,  6,  5,  7,  9,  8}},
    { 8, {18, 17, 13, 12, 14, 16, 15}}
};

void KenwoodRXDF4Layout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void KenwoodRXDF4Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool KenwoodRXDF4Layout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool KenwoodRXDF4Layout::getSegmentGroup7Seg(
    UINT8 regionId,
    const SegmentGroup7Seg **p_segGroup,
    UINT8 *numEntries)
{
    if (regionId != 1)
    {
        return false;
    }

    *p_segGroup = s_segmentGroup7Seg1;
    *numEntries = ARRAYSIZE(s_segmentGroup7Seg1);
    return true;
}

bool KenwoodRXDF4Layout::getSegmentGroup14Seg(
    UINT8 regionId,
    const SegmentGroup14Seg **p_segGroup,
    UINT8 *numEntries)
{
    if (regionId != 0)
    {
        return false;
    }

    *p_segGroup = s_segmentGroup14Seg0;
    *numEntries = ARRAYSIZE(s_segmentGroup14Seg0);
    return true;
}

bool KenwoodRXDF4Layout::getSegmentGroupBar(
    UINT8 regionId,
    const SegmentGroupBar **p_segGroup,
    UINT8 *numEntries)
{
    switch (regionId)
    {
        case 0:
        {
            *p_segGroup = s_segmentGroupBar0;
            *numEntries = ARRAYSIZE(s_segmentGroupBar0);
            break;
        }

        case 1:
        {
            *p_segGroup = s_segmentGroupBar1;
            *numEntries = ARRAYSIZE(s_segmentGroupBar1);
            break;
        }

        default:
        {
            return false;
        }
    }

    return true;
}

bool KenwoodRXDF4Layout::getSegmentGroupNumberList(
    UINT8 regionId,
    const SegmentGroupNumberList **p_segGroup,
    UINT8 *numEntries)
{
    switch (regionId)
    {
        case 0:
        {
            *p_segGroup = s_segmentGroupNumberList0;
            *numEntries = ARRAYSIZE(s_segmentGroupNumberList0);
            break;
        }

        case 1:
        {
            *p_segGroup = s_segmentGroupNumberList1;
            *numEntries = ARRAYSIZE(s_segmentGroupNumberList1);
            break;
        }

        default:
        {
            return false;
        }
    }

    return true;
}
