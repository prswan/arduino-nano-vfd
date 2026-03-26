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
};

//
// 6x 14-segment display.
//
static const Region s_region[] PROGMEM =
{
    // type,           subType,                 id, len
    {RegionTypeCustom, 0,                        0,   2},
    {RegionTypeChar,   RegionSubTypeChar14Seg,   0,   6}
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

//
// There is a wierd dot matrix region before the 14 segment characters.
// The manual doesn't show it used and the dot groupings are very odd.
// See: "Samsung BD-P1590 Dot Matrix Area Layout Map.pdf"
//
// Visually, it looks like it's two "characters" and it's possible to
// construct something from them.
//
static const SegmentGroupGraphicSymbol s_segmentGroupGraphicSymbol[] PROGMEM =
{
// pinG, { pinS }}
    { 1, { 3,  4,  5,  6,  7,  8,  9, 10}},
    { 1, {11, 12, 13, 14, 15, 16, 17, 18}},
};

static const DisplayGroupGraphicSymbol s_displayGroupGraphicSymbol[] PROGMEM =
{
    // Segment Group 0
    // sym,          instance, segGroupIndex, { 3,  4,  5,  6,  7,  8,  9, 10}
    {SymPause,              0,             0, { 1,  0,  0,  0,  0,  1,  1,  1}},
    {SymBarBottom,          0,             0, { 0,  0,  0,  0,  1,  1,  0,  0}},
    {SymSquare,             0,             0, { 1,  1,  1,  0,  1,  1,  1,  1}},

    // Segment Group 1
    // sym,          instance, segGroupIndex, {11, 12, 13, 14, 15, 16, 17, 18}
    {SymArrowHeadForwardLight,  0,             1, { 0,  1,  0,  0,  1,  1,  0,  0}},
    {SymArrowHeadForward,       0,             1, { 0,  0,  0,  0,  0,  1,  1,  1}},
    {SymArrowHeadForwardBold,   0,             1, { 0,  0,  0,  0,  1,  1,  1,  1}},
    {SymArrowHeadForwardBold,   1,             1, { 1,  1,  1,  0,  1,  1,  0,  0}},
    {SymChevron,                0,             1, { 1,  1,  1,  0,  1,  1,  1,  1}},
    {SymText_8,                 0,             1, { 0,  0,  1,  0,  0,  0,  0,  1}},
    {SymText_B,                 0,             1, { 0,  1,  1,  0,  0,  0,  0,  1}},
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

bool SamsungBDP1590Layout::getSegmentGroupGraphicSymbol(
    const SegmentGroupGraphicSymbol **p_segmentGroup,
    UINT8 *numSegmentGroupEntries,
    const DisplayGroupGraphicSymbol **p_displayGroup,
    UINT8 *numDisplayGroupEntries)
{

    *p_segmentGroup = s_segmentGroupGraphicSymbol;
    *numSegmentGroupEntries = ARRAYSIZE(s_segmentGroupGraphicSymbol);

    *p_displayGroup = s_displayGroupGraphicSymbol;
    *numDisplayGroupEntries = ARRAYSIZE(s_displayGroupGraphicSymbol);

    return true;
};
