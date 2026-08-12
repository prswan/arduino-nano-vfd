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
#include "KenwoodKRV77REQLayout.h"


// EQ Display, see KenwoodKRV77RLayout for the overall information.


static const UINT8 s_manufacturer[] PROGMEM = "KENWOOD";
static const UINT8 s_model[]        PROGMEM = "KR-V77R EQ";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
};

//
// Just the EQ bars & symbols.
//
static const Region s_region[] PROGMEM =
{
    // type,                subType,                id, len
    {RegionTypeBar ,        0,                       0,   7},
};

// TODO: May be better as part of bar scale. M-A => M-E as a numberList?
static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
    {SymDotBar,           0,    8,   14}, // and '60'
    {SymDotBar,           1,    2,   14}, // and '15K'
    {SymText_PGM,         0,    1,    4},
    {SymText_SET,         0,    1,    3},
    {SymText_M_A,         0,    1,   10},
    {SymText_M_B,         0,    1,    9},
    {SymText_M_C,         0,    1,    8},
    {SymText_M_D,         0,    1,    7},
    {SymText_M_E,         0,    1,    6},

    {SymText_150,         0,    7,   14}, // bottom row
    {SymText_400,         0,    6,   14},
    {SymText_1K,          0,    5,   14},
    {SymText_2_4K,        0,    4,   14},
    {SymText_6K,          0,    3,   14},
    {SymText_MEMO,        0,    1,   11}, 
};

//
// 7x 13-segment vertical bar
//
// TODO: Are there any bar displays that would have different horz/vert/rev/seg1sym per bar in same region?
//       If no, then the attributes can be per bar region to save space/dupe.
//
static const SegmentGroupBar s_segmentGroupBar0[] PROGMEM =
{
//    horz., vert.,   reverse, seg1Symbol, pinG, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13}}
    { false, true,    false,   false,         8, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13}},
    { false, true,    false,   false,         7, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13}},
    { false, true,    false,   false,         6, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13}},
    { false, true,    false,   false,         5, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13}},
    { false, true,    false,   false,         4, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13}},
    { false, true,    false,   false,         3, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13}},
    { false, true,    false,   false,         2, { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13}},
};


void KenwoodKRV77REQLayout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void KenwoodKRV77REQLayout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool KenwoodKRV77REQLayout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool KenwoodKRV77REQLayout::getSegmentGroupBar(
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

        default:
        {
            return false;
        }
    }

    return true;
};
