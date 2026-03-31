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
#include "PioneerDVR220Layout.h"

/*
Data
----
The original player powered on once and ran for a short while before it died.
Whilst it ran the display was dim. No voltage readings could be obtained.
When scrapped the power supply had several swollen capacitors.

Attached to the Controller PCB the display is dim and uneven with:
 - VFIL: 4.15 VAC
 - Vbb: -24.1 VDC
 2 x 2.2R Fil resistors yield VFIL at VFD of 3.80 VAC. 
 
 Physically, it's almost identical to the Panasonic DVD-RV32 
 measured in the player as FIL 3.86 VDC & Vbb -30.8 VDC.
*/

static const UINT8 s_manufacturer[] PROGMEM = "PIONEER";
static const UINT8 s_model[]        PROGMEM = "DVR-220";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
};

//
// 10x 14-segment display.
//
static const Region s_region[] PROGMEM =
{
    // type,           subType,                 id, len
    {RegionTypeChar,   RegionSubTypeChar14Seg,   0,  10}
};

static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
    {SymText_HDD,         0,   12,   10}, // row 1
    {SymArrowHeadReverse, 0,   12,    9},
    {SymArrowHeadForward, 0,   12,    8},
    {SymText_DVD,         0,   12,    7},
    {SymText_PL ,         0,   11,   15},
    {SymText_PM,          0,    9,   15},
    {SymText_2,           0,    8,   15},
    {SymText_3,           0,    8,   16},
    {SymText_REM,         0,    6,   15},
    {SymText_P,           0,    5,   15},
    {SymText_V,           0,    5,   16},
    {SymText_CD,          0,    4,   15},
    {SymText_R,           0,    3,   15},
    {SymText_W,           0,    3,   16},
    {SymClock,            0,    1,   14},
    {SymText_DISC,        0,    1,   13},
    {SymText_FINE,        0,    1,   12},
    {SymText_AUTO,        0,    1,   11},
    {SymText_SP,          0,    1,   10},
    {SymText_L,           0,    1,    9},
    {SymText_R,           1,    1,    8},
    {SymText_SAP,         0,    1,    7},
    {SymText_LP,          0,    1,    6},

    {SymText_PLAY,        0,   12,    1}, // row 2
    {SymArrowForward,     0,   12,    5},
    {SymText_REC,         0,   12,    4},
    {SymColon,            0,   10,   16}, // col 1
    {SymArrowHeadForward, 1,   10,   15}, // col 1
    {SymArrowHeadForward, 2,    7,   15}, // col 4
    {SymText_CH,          0,    2,   15},
    {SymText_VPS,         0,    1,    3},
    {SymText_OVER,        0,    1,    4},
    {SymText_EP,          0,    1,    5},

    {SymText_REC,         1,   12,    3}, // row 3
    {SymArrowReverse,     0,   12,    2},
    {SymText_PLAY,        1,   12,    6},
    {SymText_H,           0,   11,   16}, // col 0
    {SymText_M,           0,    9,   16}, // col 2
    {SymText_S,           0,    7,   16}, // col 4
    {SymText_H,           1,    6,   16}, // col 5
    {SymText_M,           1,    4,   16}, // col 7
    {SymText_S,           1,    2,   16}, // col 9
    {SymText_PDC,         0,    1,   16},
    {SymText_NTSC,        0,    1,    1},
    {SymText_MN,          0,    1,    2},
};

//
// 10x 14-segment display.
//
static const SegmentGroup14Seg s_segmentGroup14Seg[] PROGMEM =
{
// pinG, { a   b   c   d   e   f  g1  g2   h   i   j   k   l   m}}
    {11, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    {10, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 9, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 8, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 7, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 6, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 5, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 4, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 3, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
    { 2, {14, 10,  6,  1,  5,  9,  7,  8, 13, 12, 11,  4,  3,  2}},
};

void PioneerDVR220Layout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void PioneerDVR220Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool PioneerDVR220Layout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool PioneerDVR220Layout::getSegmentGroup14Seg(
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
