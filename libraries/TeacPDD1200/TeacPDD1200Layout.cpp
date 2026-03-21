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
#include "TeacPDD1200Layout.h"

/*
Data
----
Original player measurements:
 - VFIL: 4.6 VAC
 - Vbb: -18.2VDC

Fitted to a Universal V1.10 PCB with 2 x 2.2R Fil resistors:
 - VFIL: 3.40 VAC, slight red glow
 - IFIL: 179mA
 - Vbb: -36.1 VDC, display is good & bright
 
There is about 82mm of pin width and 10 drive pins remaining on U1 plus 32 if U3 is fitted for
a second display on this PCB.
*/

static const UINT8 s_manufacturer[] PROGMEM = "TEAC";
static const UINT8 s_model[]        PROGMEM = "PD-D1200";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
    DriveTypeSN75518,
};

//
// 7x 7-segment display as one group of 3 and one of 4.
// TODO: Add the number list region.
//
static const Region s_region[] PROGMEM =
{
    // type,          subType,                 id, len
    {RegionTypeChar,  RegionSubTypeChar7Seg,    0,   3},
    {RegionTypeChar,  RegionSubTypeChar7Seg,    1,   4}
};

// TODO: Finish the symbol encoding.
static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
    {SymText_DISC,        0,    1,    1}, // row 1
    {SymText_TRACK,       0,    3,    1},
};

//
// 7x 7-segment display as one group of 3 and one of 4.
//
static const SegmentGroup7Seg s_segmentGroup7Seg0[] PROGMEM =
{
// pinG, { a   b   c   d   e   f   g}}
    { 1, { 5,  7, 10, 11,  9,  6,  8}},
    { 2, { 5,  7, 10, 11,  9,  6,  8}},
    { 3, { 5,  7, 10, 11,  9,  6,  8}},
};

static const SegmentGroup7Seg s_segmentGroup7Seg1[] PROGMEM =
{
// pinG, { a   b   c   d   e   f   g}}
    { 4, { 5,  7, 10, 11,  9,  6,  8}},
    { 5, { 5,  7, 10, 11,  9,  6,  8}},
    { 6, { 5,  7, 10, 11,  9,  6,  8}},
    { 7, { 5,  7, 10, 11,  9,  6,  8}},
};

void TeacPDD1200Layout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void TeacPDD1200Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool TeacPDD1200Layout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool TeacPDD1200Layout::getSegmentGroup7Seg(
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

/*
Layout
------

0101 - DISC
0102 - Play symbol & PLAY
0103 - Pause symbol & PAUSE
0104 - nothing
0105 - reg 0 col 0 seg a 
0106 - reg 0 col 0 seg f
0107 - reg 0 col 0 seg b
0108 - reg 0 col 0 seg g
0109 - reg 0 col 0 seg e
0110 - reg 0 col 0 seg c
0111 - reg 0 col 0 seg d

0201 - 20
0202 - 15
0203 - 10
0204 - 5
0205 - reg 0 col 1 seg a 
0206-0211 as grid 01

0301 - TRACK
0302 - nothing
0303 - nothing
0304 - nothing
0305 - reg 0 col 2 seg a 
0306-0311 as grid 01

0401 - TOTAL
0402 - EACH
0403 - REMAIN
0404 - EDIT
0405 - reg 1 col 0 seg a 
0406-0411 as grid 01

0501 - INTRO
0502 - MIN
0503 - r1 col 1 colon
0504 - nothing
0505 - reg 1 col 1 seg a 
0506-0511 as grid 01

0601 - SHUFFLE
0602 - SEC
0603 - nothing
0604 - nothing
0605 - reg 1 col 2 seg a 
0606-0611 as grid 01

0701 - MEMORY in box
0702 - REPEAT & box
0703 - ALL in repeat box
0704 - ONE in repeat box
0705 - reg 1 col 3 seg a 
0706-0711 as grid 01

0801 - 17
0802 - 12
0803 - 7
0804 - 2
0805 - 16
0806 - 11
0807 - 6
0808 - 1
0809-0811 - nothing

0901 - 19
0902 - 14
0903 - 9
0904 - 4
0905 - 18
0906 - 13
0907 - 8
0908 - 3
0909-0911 - nothing

*/