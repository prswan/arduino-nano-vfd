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

Attached to the Controller PCB the display looks good:
 - VFIL: 5.44 VAC
 - Vbb: +36.5 VDC
 2 x 1R Fil resistors yield VFIL at VFD of 5.32 VAC. 

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
    // type,          subType,                id, len
    {RegionTypeChar,  RegionSubTypeChar7Seg,   0,   3},
    {RegionTypeChar,  RegionSubTypeChar14Seg,  1,   5},
    {RegionTypeChar,  RegionSubTypeChar7Seg,   2,   2},
};

// TODO: Add the symbols for this display
static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
//    {SymText_DVD,         0,   13,    1}, // row 1
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

