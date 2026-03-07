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

/* TODO

  * Definition & additon of the SegmentGroupBar
    - Like 7Seg, and array of instance definitions for row/col.
    - "Bar" class to activate them.
    - Needs a way to be indepedent of number of segments in the bar.
      - Ideas
        - As a bar, percentage of max.
        - Special effects
          - Night Rider "Kit" scan?
          - Single bar counter
          - "scale" bar 0  on or off.
*/

//
// 8x 7-segment displays in two groups of 4
// 2x 16-segement horizontal bar graphs.
//
static const Region s_region[] PROGMEM =
{
    // type,          subType,               id, len
    {RegionTypeChar,  RegionSubTypeChar7Seg,  0,  4},
    {RegionTypeChar,  RegionSubTypeChar7Seg,  1,  4},
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

/*

Layout Finder
0308 - col 4 "-"
0316 - col 5 DP
0508 - col 0 "-"
0516 - col 1 DP

Right side symbols
G1 S1 - "DOLBY NR" S_TEXT_DOLBY_NR
G1 S2 - white square 'B' S_SYMBOL_WHITE_SQUARE_B
G1 S3 - red left arrow S_SYMBOL_RED_LEFT_ARROW
G1 S4 - "PLAY" S_TEXT_PLAY
G1 S5 - red right arrow
G1 S6 - white square 'C' S_SYMBOL_WHITE_SQUARE_C
G1 S7 - "MEMORY"
G1 S8 - red pause symbol S_SYMBOL_RED_PAUSE
G1 S9 - red "REC"
G1 S10+ - n/a

Left side symbols
G6 S1 - "DOLBY NR"
G6 S2 - white square 'B'
G6 S3 - red left arrow
G6 S4 - "PLAY"
G6 S5 - red right arrow
G6 S6 - white square 'C'
G6 S7 - "MEMORY"
G6 S8 - red pause symbol
G6 S9 - red "REC"
G6 S10 - FADE and box
G6 S11 - red right arrow in fade box
G6 S12 - "BLANK SKIP"
G6 S13 - "AUTO PAUSE"
G6 S14 - red left arrow in fade box
G6 S15+ n/c

Top:
G7 S1 - Top bar L, bar 1 and top scale
G7 S2 - 2
G7 S3 - 5
G7 S4 - 7
G7 S5 - 6
G7 S6 - 3
G7 S7 - 4
G7 S8 - 8
G7 S9 - 9
G7 S10 - 10
G7 S11 - 13
G7 S12 - 15
G7 S13 - 14
G7 S14 - 11
G7 S15 - 12
G7 S16 - 16
G7 S17+

Bottom G8
G8 S1 - bottom bar R, bar 1, dolby double D symbol
G8 S2 - S16 same as above
G8 S17 - Red dot bar 4
G8 S18 - Red dot bar 1 thru 3
G8 S19+ n/c

*/
