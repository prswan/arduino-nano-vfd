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
#include "SamsungBDP1590Layout.h"


static const UINT8 s_manufacturer[] PROGMEM = "SAMSUNG";
static const UINT8 s_model[]        PROGMEM = "BD-P1590";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
    DriveTypePT6315,
};

//
// 6x 14-segment display.
//
static const Region s_region[] PROGMEM =
{
    // type,          subType,                 id, len
    {RegionTypeChar,  RegionSubTypeChar14Seg,   0,   6}
};

static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
    {SymDiscIn,           0,    1,    2}, // row 1
    {SymText_BD,          0,    1,    1},
    {SymText_DVD,         0,    2,    1},
    {SymText_CD,          0,    3,    1},
    {SymText_USB,         0,    4,    1},
    {SymText_HDMI,        0,    5,    1},
    {SymText_HD,          0,    6,    1},
    {SymText_24F,         0,    7,    1},

    {SymColon,            0,    3,    2}, // row 2
    {SymColon,            1,    5,    2},
};

//
// 6x 14-segment display with centre dot and four corner dots (to figure that out later).
//
static const SegmentGroup14Seg s_segmentGroup14Seg[] PROGMEM =
{
// pinG, { a   b   c   d   e   f  g1  g2   h   i   j   k   l   m  gc  ac  dc}}
    { 2, { 4,  9, 17, 19, 13,  5, 10, 12,  6,  7,  8, 14, 15, 16, 11,  3, 18}},
    { 3, { 4,  9, 17, 19, 13,  5, 10, 12,  6,  7,  8, 14, 15, 16, 11,  3, 18}},
    { 4, { 4,  9, 17, 19, 13,  5, 10, 12,  6,  7,  8, 14, 15, 16, 11,  3, 18}},
    { 5, { 4,  9, 17, 19, 13,  5, 10, 12,  6,  7,  8, 14, 15, 16, 11,  3, 18}},
    { 6, { 4,  9, 17, 19, 13,  5, 10, 12,  6,  7,  8, 14, 15, 16, 11,  3, 18}},
    { 7, { 4,  9, 17, 19, 13,  5, 10, 12,  6,  7,  8, 14, 15, 16, 11,  3, 18}},
};

void SamsungBDP1590Layout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void SamsungBDP1590Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool SamsungBDP1590Layout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool SamsungBDP1590Layout::getSegmentGroup14Seg(
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
};

/*
Symbols

0101 - BD
0201 - DVD
0301 - CD
0401 - USB
0501 - HDMI
0601 - HD
0701 - 24F

0102 - spinning disc symbol
0202
0302 - colon between col 1 & 2
0402
0502 - colon between col 3 & 4
0602
0702

0203-0703 - top R & L dots
0218-0718 - bottom R & L dots
 - Manual examples of the extra corner dots
   A - bottom
   L - bottom
   V - top
   Y - top
 - will have to somewhat guess the rest.

The weird dot matrix area TBD. The user manual doesn't document anything in this area.
A walk through them has various dot groups. I *think* it's possible to make a stop square
and play triangle?
*/