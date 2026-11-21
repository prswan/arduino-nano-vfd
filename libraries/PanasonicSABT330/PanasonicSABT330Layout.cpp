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
#include "PanasonicSABT330Layout.h"

/*
Data
----
Original player measurements could not be taken as the player did not power on.

Insignia NS-R2001 Transformer
-----------------------------
 - VFIL @ Controller PCB Input  : 3.96 VAC
 - VFIL @ Controller PL0 2x  0R : 3.96 VAC
 - VFIL @ VFD            2x 10R : 1.81 VAC
 - IFIL (calculated)            : 108mA
 Display looks good, slight red filament glow in the dark.
 The similar Panasonic DMR-ES25 Koala VFD measured 2.18 VDC in system.
 */

static const UINT8 s_manufacturer[] PROGMEM = "PANASONIC";
static const UINT8 s_model[]        PROGMEM = "SA-BT330";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
};

//
// 8x 14-segment display.
//
static const Region s_region[] PROGMEM =
{
    // type,          subType,                 id, len
    {RegionTypeChar,  RegionSubTypeChar14Seg,   0,   8}
};

static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
    {SymColon,            0,    4,   15}, // row 1
    {SymColon,            1,    6,   15},
    {SymText_RDS,         0,    9,   14},

    {SymText_W,           0,    9,   13}, // row 2

    {SymDecimalPoint,     0,    4,   16}, // row 3
    {SymDecimalPoint,     1,    6,   16},
    {SymText_SRD,         0,    9,    2},
};

//
// 8x 14-segment display.
//
static const SegmentGroup14Seg s_segmentGroup14Seg[] PROGMEM =
{
// pinG, { a   b   c   d   e   f  g1  g2   h   i   j   k   l   m}}
    { 1, {14, 13,  2,  4,  3, 12,  7,  8,  9, 10, 11,  1,  5,  6}},
    { 2, {14, 13,  2,  4,  3, 12,  7,  8,  9, 10, 11,  1,  5,  6}},
    { 3, {14, 13,  2,  4,  3, 12,  7,  8,  9, 10, 11,  1,  5,  6}},
    { 4, {14, 13,  2,  4,  3, 12,  7,  8,  9, 10, 11,  1,  5,  6}},
    { 5, {14, 13,  2,  4,  3, 12,  7,  8,  9, 10, 11,  1,  5,  6}},
    { 6, {14, 13,  2,  4,  3, 12,  7,  8,  9, 10, 11,  1,  5,  6}},
    { 7, {14, 13,  2,  4,  3, 12,  7,  8,  9, 10, 11,  1,  5,  6}},
    { 8, {14, 13,  2,  4,  3, 12,  7,  8,  9, 10, 11,  1,  5,  6}},
};

void PanasonicSABT330Layout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void PanasonicSABT330Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool PanasonicSABT330Layout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool PanasonicSABT330Layout::getSegmentGroup14Seg(
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
