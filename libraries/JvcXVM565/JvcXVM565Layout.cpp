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
#include "JvcXVM565Layout.h"

/*
Data
----
Original player measurements were not taken. From the service manual:
 - VFIL:  2.9 VDC
 - Vbb: -21.2 VDC

Insignia NS-R2001 Transformer
-----------------------------
 - VFIL @ Controller PCB Input  : 3.99 VAC
 - VFIL @ Controller PL0 2x  0R : 3.72 VAC
 - VFIL @ VFD            2x 7R5 : 2.06 VAC
 - IFIL (calculated)            : 111mA
Even with a lower VFIL than was listed in the manual, display is bright & even.
*/

static const UINT8 s_manufacturer[] PROGMEM = "JVC";
static const UINT8 s_model[]        PROGMEM = "XV-M565";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
};

//
// The manual didn't document the layout, reverse engineered using the LayoutFinder.
//
static const Region s_region[] PROGMEM =
{
    // type,          subType,                id, len
    {RegionTypeChar,  RegionSubTypeChar7Seg,   0,   1},
    {RegionTypeChar,  RegionSubTypeChar7Seg,   1,   4},
    {RegionTypeChar,  RegionSubTypeChar7Seg,   2,   5}
};

static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
    {SymText_3D_PHONIC,  0,    1,    1},
    {SymText_PROGRAM,    0,    4,    1},
    {SymText_RANDOM,     0,    6,    1},
    {SymText_REPEAT,     0,    6,    4},
    {SymText_1,          0,    6,    5},
    {SymText_A_minus,    0,    6,    6},
    {SymText_B,          0,    6,    7},
    {SymText_DISC,       0,    1,    2},
    {SymText_TITLE,      0,    1,    3},
    {SymText_CHAP,       0,    1,    5},
    {SymText_KARAOKE,    0,    4,    2},
    {SymText_RESUME,     0,    6,    2},
    {SymText_THEATER,    0,    6,    8},
    {SymText_KEY,        0,    1,    4},
    {SymText_TRACK,      0,    1,    6},
    {SymText_V_MASK,     0,    6,    3},
    {SymText_V_REPLACE,  0,    6,    9},
    {SymText_DVD,        0,    4,    3},
    {SymText_VCD,        0,    4,    4},
    {SymText_EACH,       0,    4,    5},
    {SymColon,           0,    4,    7},
    {SymColon,           1,    6,   10},
    {SymText_REMAIN,     0,    4,    6},
    {SymMinus,           0,    6,   11}
};

//
// The display provides two sets of seven segment outputs per grid.
// The JVC notes list each character's segments in a,b,f,g,c,e,d order.
//
static const SegmentGroup7Seg s_segmentGroup7Seg0[] PROGMEM =
{
    // pinG, { a,  b,  c,  d,  e,  f,  g }
    {  1,    { 8,  9, 12, 14, 13, 10, 11}}
};

static const SegmentGroup7Seg s_segmentGroup7Seg1[] PROGMEM =
{
    // pinG, { a,  b,  c,  d,  e,  f,  g }
    {  2,    { 1,  2,  5,  7,  6,  3,  4}},
    {  2,    { 8,  9, 12, 14, 13, 10, 11}},
    {  3,    { 1,  2,  5,  7,  6,  3,  4}},
    {  3,    { 8,  9, 12, 14, 13, 10, 11}}
};

static const SegmentGroup7Seg s_segmentGroup7Seg2[] PROGMEM =
{
    // pinG, { a,  b,  c,  d,  e,  f,  g }
    {  4,    { 8,  9, 12, 14, 13, 10, 11}},
    {  5,    { 1,  2,  5,  7,  6,  3,  4}},
    {  5,    { 8,  9, 12, 14, 13, 10, 11}},
    {  7,    { 1,  2,  5,  7,  6,  3,  4}},
    {  7,    { 8,  9, 12, 14, 13, 10, 11}}
};

void JvcXVM565Layout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void JvcXVM565Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool JvcXVM565Layout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool JvcXVM565Layout::getSegmentGroup7Seg(
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

/*
LayoutFinder

0101 - 3D_PHONIC
0102 - DISC
0103 - TITLE
0104 - KEY
0105 - TRACK
0106 - nc
0107 - nc
0108 - r0 - a
0109 - r0 - b
0110 - r0 - f
0111 - r0 - g
0112 - r0 - c
0113 - r0 - e
0114 - r0 - d

0201 - r1c0 - a
0202 - r1c0 - b
0203 - r1c0 - f
0204 - r1c0 - g
0205 - r1c0 - c
0206 - r1c0 - e
0207 - r1c0 - d
0208 - r1c1 - a
0209 - r1c1 - b
0210 - r1c1 - f
0211 - r1c1 - g
0212 - r1c1 - c
0213 - r1c1 - e
0214 - r1c1 - d

0301 - r1c2 - a
0302 - r1c2 - b
0303 - r1c2 - f
0304 - r1c2 - g
0305 - r1c2 - c
0306 - r1c2 - e
0307 - r1c2 - d
0308 - r1c3 - a
0309 - r1c3 - b
0310 - r1c3 - f
0311 - r1c3 - g
0312 - r1c3 - c
0313 - r1c3 - e
0314 - r1c3 - d

0401 - PROGRAM
0402 - KARAOKE
0403 - DVD
0404 - VCD
0405 - EACH
0406 - REMAIN
0407 - i0 colon
0408 - r2c0 - a
0409 - r2c0 - b
0410 - r2c0 - f
0411 - r2c0 - g
0412 - r2c0 - c
0413 - r2c0 - e
0414 - r2c0 - d

0501 - r2c1 - a
0502 - r2c1 - b
0503 - r2c1 - f
0504 - r2c1 - g
0505 - r2c1 - c
0506 - r2c1 - e
0507 - r2c1 - d
0508 - r2c2 - a
0509 - r2c2 - b
0510 - r2c2 - f
0511 - r2c2 - g
0512 - r2c2 - c
0513 - r2c2 - e
0514 - r2c2 - d

0601 - RANDOM
0602 - RESUME
0603 - V_MASK
0604 - REPEAT
0605 - '1' (next to repeat)
0606 - A minus (next to repeat)
0607 - B (next to A-)
0608 - THEATER
0609 - V_REPLACE
0610 - i1 colon
0611 - i0 minus
0612 - nc
0613/14 - nc

0701 - r2c3 - a
0702 - r2c3 - b
rest of grid 7 same as grid 5 for r2c3 & c4

Symbol row order:
3D-PHONIC, PROGRAM, RANDOM, REPEAT, 1, A-, B
DISC, TITLE, CHAP, KARAOKE, RESUME, THEATER
KEY, TRACK, V_MASK, V_REPLACE,
DVD, VCD
EACH, i0 colon, i1 colon
REMAIN, minus
*/
