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
#include "SonyDVPNS725PLayout.h"


static const UINT8 s_manufacturer[] PROGMEM = "SONY";
static const UINT8 s_model[]        PROGMEM = "DVP-NS725P";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
    DriveTypeSN75518,
};

//
// 7x 14-segment display with centre dot.
//
static const Region s_region[] PROGMEM =
{
    // type,          subType,                 id, len
    {RegionTypeChar,  RegionSubTypeChar14Seg,   0,   7}
};

static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
    {SymText_DVD,         0,    2,    4}, // row 1
    {SymPlayForward,      0,    1,   23},
    {SymPause,            0,    1,    4},
    {SymText_TRK,         0,    7,    4},

    {SymText_V,           0,    2,   21}, // row 2
    {SymText_CD,          0,    2,   22},
    {SymRepeat,           0,    1,   21},
    {SymText_1,           0,    1,   22},
    {SymMovieCamera,      0,    7,   22},

    {SymColon,            0,    5,    4},
    {SymColon,            1,    3,    4},

    {SymDolbyDoubleD_D,   0,    2,   20}, // row 3
    {SymText_MP3,         0,    1,   20},
    {SymText_dts,         0,    7,   20},

    {SymDecimalPoint,     0,    7,   23},
    {SymDecimalPoint,     1,    6,   23},
    {SymDecimalPoint,     2,    5,   23},
    {SymDecimalPoint,     3,    4,   23},
    {SymDecimalPoint,     4,    3,   23},
    {SymDecimalPoint,     5,    2,   23},
};

//
// 7x 14-segment display with centre dot.
// These were documented in the service manual.
//
static const SegmentGroup14Seg s_segmentGroup14Seg[] PROGMEM =
{
// pinG, { a   b   c   d   e   f  g1  g2   h   i   j   k   l   m  gc}}
    { 7, { 5,  9, 18, 19, 14, 10, 13, 11,  6,  7,  8, 17, 16, 15, 12}},
    { 6, { 5,  9, 18, 19, 14, 10, 13, 11,  6,  7,  8, 17, 16, 15, 12}},
    { 5, { 5,  9, 18, 19, 14, 10, 13, 11,  6,  7,  8, 17, 16, 15, 12}},
    { 4, { 5,  9, 18, 19, 14, 10, 13, 11,  6,  7,  8, 17, 16, 15, 12}},
    { 3, { 5,  9, 18, 19, 14, 10, 13, 11,  6,  7,  8, 17, 16, 15, 12}},
    { 2, { 5,  9, 18, 19, 14, 10, 13, 11,  6,  7,  8, 17, 16, 15, 12}},
    { 1, { 5,  9, 18, 19, 14, 10, 13, 11,  6,  7,  8, 17, 16, 15, 12}},
};

void SonyDVPNS725PLayout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void SonyDVPNS725PLayout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool SonyDVPNS725PLayout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool SonyDVPNS725PLayout::getSegmentGroup14Seg(
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
