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
#include "KenwoodKRV77RLayout.h"

/*
Data
----
This was a front panel purchase off eBay so no live data, however the service manual lists:
 - VFIL: 7.40 VAC
 - Vbb: -30.9 VDC

Onkyo HT-R340 NPT-1516D Transformer
-----------------------------------
 - VFIL @ Controller PCB Input  : 5.66 VAC
 - VFIL @ Controller PL7 2x 0   : 5.59 VAC
 - VFIL @ VFD            2x 1R  : 5.30 VAC
 Display looks borderline OK.
 Suspect with 4.25 VAC transformer it would be poor.

 */

static const UINT8 s_manufacturer[] PROGMEM = "KENWOOD";
static const UINT8 s_model[]        PROGMEM = "KR-V77R";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
};

//
// - Leading "1" digit ignored
// - Trailing small partial digit ignored
//
static const Region s_region[] PROGMEM =
{
    // type,                subType,                id, len
    {RegionTypeChar,        RegionSubTypeChar7Seg,   0,   3},
    {RegionTypeBar ,        0,                       0,   1},
    {RegionTypeBar ,        0,                       1,   1},
    {RegionTypeNumberList,  0,                       0,   1},
    {RegionTypeChar,        RegionSubTypeChar14Seg,  1,   5},
    {RegionTypeChar,        RegionSubTypeChar7Seg,   2,   2},
};

// TODO: Add the symbols for this display
//
// EQ & VIDEO MONITOR are tied.
// MHz & common section of "0" and "5" digit are tied.
//
static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
    {SymText_EQ_REC,           0,    9,   35}, // row 1
    {SymText_AUTO,             0,    9,   12},
    {SymText_STEREO,           0,    8,   10},
    {SymText_FM,               0,    6,    6},
    {SymText_MHz,              0,    3,    6},
    {SymText_VOLUME_LEVEL,     0,    2,   33},
    {SymText_REAR,             0,    1,   32},

    {SymText_DEFEAT,           0,    9,   13}, // row 2
    {SymText_DELAY,            0,    6,    5},
    {SymText_ms,               0,    3,    5},

    {SymText_EQ,               0,    9,   20}, // row 3
    {SymText_ON,               0,    9,   14},
    {SymText_MEMO,             0,    9,   36},
    {SymText_TUNED,            0,    8,   11},
    {SymText_AM,               0,    6,    4},
    {SymText_KHz,              0,    3,    4},
    {SymText_MUTING,           0,    2,   32},

    {SymText_AUDIO_INJECTION,  0,    9,   15}, // row 4
    {SymText_BAL,              0,    6,   36},

    {SymText_TAPE_2,           0,    9,   16}, // row 5
    {SymText_1_10,             0,    3,    3},

    {SymText_VIDEO_MONITOR,    0,    9,   20}, // row 6
    {SymText_11_20,            0,    3,    2},

    {SymDecimalPoint,          0,    4,   28}, // row 7
    {SymText_CH,               0,    3,    1}, // TBD
};

//
// Region 0
// 3 x 7-seg standard display
// - leading "1" and trailing small partial digit ignored
//
static const SegmentGroup7Seg s_segmentGroup7Seg0[] PROGMEM =
{
// pinG, { a   b   c   d   e   f  g }}
    { 5, {29, 30, 31, 32, 33, 34, 35}},
    { 4, {29, 30, 31, 32, 33, 34, 35}},
    { 3, {29, 30, 31, 32, 33, 34, 35}},
};

//
// 1x 11-segment 45 degree filled graph bar
//
static const SegmentGroupBar s_segmentGroupBar0[] PROGMEM =
{
//    horz., vert.,   reverse, seg1Symbol, pinG, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11}}
    { true,  true,    false,   false,         2, {21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}},
};

//
// 1x 11-segment vertical bar
//
static const SegmentGroupBar s_segmentGroupBar1[] PROGMEM =
{
//    horz., vert.,   reverse, seg1Symbol, pinG, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11}}
    { false, true,    false,   false,         1, {21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}},
};

//
// Region 1
// 5x 14-segment standard display.
// Digit 5:
// - Is missing segment "k", impacts: V,W,X,Z
// - Segments 'h','j' are linked as S7, impacts K,N,V,Z
// - Segment 'i' is S8
// - Segment 'l' is S9
// - Segment 'm' is S36
// - The split g1/g2 makes it also incompatible with the current 
//   7-seg implementation with a single 'g'. 
//   Digit 5 included here as an incomplete 14-seg for now.
// Digits 6 & 7 in the same row are pure 7-seg. 
//
static const SegmentGroup14Seg s_segmentGroup14Seg1[] PROGMEM =
{
// pinG, { a   b   c   d   e   f  g1  g2   h   i   j   k   l   m}}
    { 9, {21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 34, 33, 32}},
    { 8, {21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 34, 33, 32}},
    { 7, {21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 34, 33, 32}},
    { 6, {21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 34, 33, 32}},
    { 5, {21, 22, 23, 24, 25, 26, 27, 28,  7,  8,  7,  0,  9, 36}},
};

//
// Region 2
// 2 x 7-seg standard display
//
static const SegmentGroup7Seg s_segmentGroup7Seg2[] PROGMEM =
{
// pinG, { a   b   c   d   e   f  g }}
    { 4, {21, 22, 23, 24, 25, 26, 27}},
    { 3, {21, 22, 23, 24, 25, 26, 27}},
};

//
// There are numbers 1,2,3 that's useful to represent as a number list to allow
// this display to have a complete set of all elements for testing.
//
static const SegmentGroupNumberList s_segmentGroupNumberList[] PROGMEM =
{
    { // numListLen, numCols, numRows, topToBottom
                  3,       3,       1,       false,
        {
            // [] {pinG,{value,pinS},{value,pinS},...}
            { 9, {{ 1,17},{ 2,18},{ 3,19}}}  // grid[0]
        }
    }
};


void KenwoodKRV77RLayout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void KenwoodKRV77RLayout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool KenwoodKRV77RLayout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool KenwoodKRV77RLayout::getSegmentGroup7Seg(
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

        case 2:
        {
            *p_segGroup = s_segmentGroup7Seg2;
            *numEntries = ARRAYSIZE(s_segmentGroup7Seg2);
            break;
        }

        default:
        {
            return false;
        }
    }

    return true;
};

bool KenwoodKRV77RLayout::getSegmentGroup14Seg(
    UINT8 regionId,
    const SegmentGroup14Seg **p_segGroup,
    UINT8 *numEntries)
{
    if (regionId != 1)
    {
        return false;
    }

    *p_segGroup = s_segmentGroup14Seg1;
    *numEntries = ARRAYSIZE(s_segmentGroup14Seg1);

    return true;
}

bool KenwoodKRV77RLayout::getSegmentGroupBar(
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

bool KenwoodKRV77RLayout::getSegmentGroupNumberList(
    UINT8 regionId,
    const SegmentGroupNumberList **p_segGroup,
    UINT8 *numEntries)
{
    if (regionId != 0)
    {
        return false;
    }

    *p_segGroup = s_segmentGroupNumberList;
    *numEntries = ARRAYSIZE(s_segmentGroupNumberList);

    return true;
};
