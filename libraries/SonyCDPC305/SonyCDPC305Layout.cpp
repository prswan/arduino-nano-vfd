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
#include "SonyCDPC305Layout.h"

/*
Data
----
I can't remember why there were no live measurements, possibly the player died on the bench.
From the service manual:
 - VFIL: 3.9 VAC
 - Vbb: -32  VDC

Onkyo HT-R340 NPT-1516D Transformer
-----------------------------------
 - VFIL @ Controller PCB Input  : 5.45
 - VFIL @ Controller PL5 2x 2R2 : 3.80
 - VFIL @ VFD            2x 1R  : 3.25

 Display seems a little on the dim side.
*/

static const UINT8 s_manufacturer[] PROGMEM = "SONY";
static const UINT8 s_model[]        PROGMEM = "CDP-C305";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
};

//
// 2x 7-segment displays.
// The last digit has a couple of extra segments, ignored for now.
//
static const Region s_region[] PROGMEM =
{
    // type,                subType,                id, len
    {RegionTypeNumberList,  0,                       0,   1},
    {RegionTypeChar,        RegionSubTypeChar7Seg,   0,   2},
    {RegionTypeChar,        RegionSubTypeChar7Seg,   1,   4}
};

static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
//  {SymText_ALL,         0,    6,    9}, // Also activates trailing "S" after DISC, ignored
    {SymText_1,           0,    6,   10},
    {SymText_DISC,        0,    6,    8},
    {SymText_FADE,        0,    5,   11},
    {SymText_SHUFFLE,     0,    4,   11},
    {SymText_PGM,         0,    3,   11},
    {SymText_REPEAT,      0,    1,   11},
    {SymPlayForward,      0,    6,   12},
    {SymPause,            0,    6,   11},
    {SymMinus,            0,    4,   12},
    {SymDecimalPoint,     0,    3,   12},
};

//
// TODO: There are highlight circles around the numbers not expressed in this struct
//       Idea: Value, pinS_Value, pinS_Highlight ?
//
static const SegmentGroupNumberList s_segmentGroupNumberList[] PROGMEM =
{
    { // numListLen, numCols, numRows, topToBottom
                  5,       5,       1,       false,
        {
            // [] {pinG,{value,pinS},{value,pinS},...}
            { 5, {{ 1, 9}}},  // grid[0]
            { 4, {{ 2, 9}}},  // grid[1]
            { 3, {{ 3, 9}}},  // grid[2]
            { 2, {{ 4, 9}}},  // grid[3]
            { 1, {{ 5, 9}}},  // grid[4]
        }
    }
};

//
// 2x 7-segment display.
// These were documented in the service manual.
//
static const SegmentGroup7Seg s_segmentGroup7Seg0[] PROGMEM =
{
// pinG, { a   b   c   d   e   f   g}}
    { 6, { 1,  2,  3,  4,  5,  6,  7}},
    { 5, { 1,  2,  3,  4,  5,  6,  7}},
};

//
// 4x 7-segment display.
// These were documented in the service manual.
//
static const SegmentGroup7Seg s_segmentGroup7Seg1[] PROGMEM =
{
// pinG, { a   b   c   d   e   f   g}}
    { 4, { 1,  2,  3,  4,  5,  6,  7}},
    { 3, { 1,  2,  3,  4,  5,  6,  7}},
    { 2, { 1,  2,  3,  4,  5,  6,  7}},
    { 1, { 1,  2,  3,  4,  5,  6,  7}},
};

void SonyCDPC305Layout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void SonyCDPC305Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool SonyCDPC305Layout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool SonyCDPC305Layout::getSegmentGroup7Seg(
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
};

bool SonyCDPC305Layout::getSegmentGroupNumberList(
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

/*
Layout Finder Notes
-------------------
0109 - 5
0110 - 5 circle
0111 - REPEAT
0112 - region 1 4th digit the two extra middle segments "<", can ignore

0109 - 4
0110 - 4 circle

0311 - PGM
0312 - r1 DP between 2 & 3rd digit

0411 - SHUFFLE
0412 - "-" before r1 2st digit

0511 - FADE

0608 - DISC
0609 - ALL + the S on the end of DISC, may ignore this one.
0610 - 1 before DISC
0611 - pause symbol
0612 - play symbol
*/
