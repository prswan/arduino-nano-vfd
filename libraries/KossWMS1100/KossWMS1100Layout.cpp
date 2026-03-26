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
#include "KossWMS1100Layout.h"

/*
Data
----
eBay purchase of facetplate only, no service manual found.

Attached to the Controller PCB the display has OK brightness but is flickering.
 - VFIL: 4.00 VAC
 - Vbb: -24.1 VDC
 2 x 2.2R Fil resistors yield VFIL at VFD of 2.68 VAC.

 TODO: Investigate flickering, possibly there is an AC path to Vbb on the PCB
 that likely used DC FIL voltage since it was in a car.
*/

static const UINT8 s_manufacturer[] PROGMEM = "KOSS";
static const UINT8 s_model[]        PROGMEM = "WMS1100";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
};

//
// 5x 7-segment display.
//
// TODO: To evaluate if the odd display format is worth doing something with.
// - Region 0 has 1x 7-seg, 2 bars, 1 x 6 seg (1,2,3) 
// - Region 1 has 5x 7-seg with additional isolated 14-seg pieces
//
static const Region s_region[] PROGMEM =
{
    // type,           subType,                 id, len
    {RegionTypeChar,   RegionSubTypeChar7Seg,   0,   1},
    {RegionTypeChar,   RegionSubTypeChar7Seg,   1,   5},
    {RegionTypeChar,   RegionSubTypeChar7Seg,   2,   2}
};

// TODO: Finish the symbol map.
static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
    {SymDiscIn,           0,   11,    5}, // row 1
    {SymText_TRACK,       0,    1,    8},
};

// 1x full 7-segment display
static const SegmentGroup7Seg s_segmentGroup7Seg0[] PROGMEM =
{
// pinG, { a   b   c   d   e   f   g}}
    {10, { 1,  2,  5,  7,  6,  3,  4}},
};

// 5x 7-segment display
static const SegmentGroup7Seg s_segmentGroup7Seg1[] PROGMEM =
{
// pinG, { a   b   c   d   e   f   g}}
    { 8, { 1,  2,  5,  7,  6,  3,  4}},
    { 7, { 1,  2,  5,  7,  6,  3,  4}},
    { 6, { 1,  2,  5,  7,  6,  3,  4}},
    { 5, { 1,  2,  5,  7,  6,  3,  4}},
    { 4, { 1,  2,  5,  7,  6,  3,  4}},
};

// 2x 7-segment display
static const SegmentGroup7Seg s_segmentGroup7Seg2[] PROGMEM =
{
// pinG, { a   b   c   d   e   f   g}}
    { 3, { 1,  2,  5,  7,  6,  3,  4}},
    { 2, { 1,  2,  5,  7,  6,  3,  4}},
};

// TODO: Add the bar layout

void KossWMS1100Layout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void KossWMS1100Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool KossWMS1100Layout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool KossWMS1100Layout::getSegmentGroup7Seg(
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

        case 3:
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
------------

0101 - Sub. W and alpha symbol
0102 - EQ text and 3 blue boxes
0103 - ROCK
0104 - CLAS
0105 - POP
0106 - ST
0107 - LOUD
0108 - TRACK
0109 - tape head symbol?
0110 - LOC
0111 - CH
0112 - nothing

0201 - r 2 col 1 seg a
0202 - r 2 col 1 seg b
0203 - r 2 col 1 seg f
0204 - r 2 col 1 seg g
0205 - r 2 col 1 seg c
0206 - r 2 col 1 seg e
0207 - r 2 col 1 seg d
0208-0212 - nothing

0301 - r 2 col 0 seg a
0302 - r 2 col 0 seg b
0303 - r 2 col 0 seg f
0304 - r 2 col 0 seg g
0305 - r 2 col 0 seg c
0306 - r 2 col 0 seg e
0307 - r 2 col 0 seg d
0308-0312 - nothing

0401 - r 1 col 4 seg a
0402 - r 1 col 4 seg b
0403 - r 1 col 4 seg f
0404 - r 1 col 4 seg g
0405 - r 1 col 4 seg c
0406 - r 1 col 4 seg e
0407 - r 1 col 4 seg d
0408 - r 1 col 4 seg i
0409 - r 1 col 4 seg l
0410 - r 1 col 4 seg m
0411-0412 - nothing

0501 - r 1 col 3 seg a
0502 - r 1 col 3 seg b
0503 - r 1 col 3 seg f
0504 - r 1 col 3 seg g
0505 - r 1 col 3 seg c
0506 - r 1 col 3 seg e
0507 - r 1 col 3 seg d
0508 - r 1 col 3 seg i
0509 - r 1 col 3 seg l
0510-0512 - nothing

0601 - r 1 col 2 seg a
0602 - r 1 col 2 seg b
0603 - r 1 col 2 seg f
0604 - r 1 col 2 seg g
0605 - r 1 col 2 seg c
0606 - r 1 col 2 seg e
0607 - r 1 col 2 seg d
0608 - r 1 col 2 seg i
0609 - r 1 col 2 seg l
0610 - r 1 col 2 dp
0611-0612 - nothing

0701 - r 1 col 1 seg a
0702 - r 1 col 1 seg b
0703 - r 1 col 1 seg f
0704 - r 1 col 1 seg g
0705 - r 1 col 1 seg c
0706 - r 1 col 1 seg e
0707 - r 1 col 1 seg d
0708 - r 1 col 1 seg h
0709 - r 1 col 1 colon
0710 - r 1 col 1 seg m
0711-0712 - nothing

0801 - r 1 col 0 seg a
0802 - r 1 col 0 seg b
0803 - r 1 col 0 seg f
0804 - r 1 col 0 seg g
0805 - r 1 col 0 seg c
0806 - r 1 col 0 seg e
0807 - r 1 col 0 seg d
0808 - r 1 col 0 seg h
0809 - r 1 col 0 seg i
0810 - r 1 col 0 seg l
0811 - r 1 col 0 seg m
0812 - nothing

0901 - r 0 col 2 seg a
0902 - r 0 col 2 seg b
0903 - nothing (missing seg f, presumably a 1,2,3)
0904 - r 0 col 2 seg g
0905 - r 0 col 2 seg c
0906 - r 0 col 2 seg e
0907 - r 0 col 2 seg d
0908-0912 - nothing

1001 - r 0 col 0 seg a
1002 - r 0 col 0 seg b
1003 - r 0 col 0 seg f
1004 - r 0 col 0 seg g
1005 - r 0 col 0 seg c
1006 - r 0 col 0 seg e
1007 - r 0 col 0 seg d
1008 - r 0 col 1 down arrow
1009 - r 0 col 1 seg b-c
1010 - r 0 col 1 seg e-f
1011 - r 0 col 1 up arrow
1012 - r 0 col 0 heart

// The circle forms a 4 segment clockwise animation
1101 - SCAN
1102 - RPT
1103 - DISC
1104 - RND
1105 - disc clamp symbol?
1106 - circle pie seg   0deg, 180deg, radius seg 135deg, 315deg
1107 - circle pie seg  45deg, 225deg, radius seg   0deg, 180deg
1108 - circle pie seg  90deg, 270deg, radius seg  45deg, 225deg
1109 - circle pie seg 315deg, 225deg, radius seg  90deg, 270deg
1110-1112 - nothing

1201 - r 0 col 0,1 bar 0 ; r 2 col 3,4 bar 0 & scale
1202 - r 0 col 0,1 bar 1 ; r 2 col 3,4 bar 1
1203 - r 0 col 0,1 bar 2 ; r 2 col 3,4 bar 2
1204 - r 0 col 0,1 bar 3 ; r 2 col 3,4 bar 3
1205 - r 0 col 0,1 bar 4 ; r 2 col 3,4 bar 4
1206 - r 0 col 0,1 bar 5 ; r 2 col 3,4 bar 5
1207 - r 0 col 0,1 bar 6 ; r 2 col 3,4 bar 6
1208 - r 0 col 0,1 bar 7 ; r 2 col 3,4 bar 7
1209 - r 0 col 0,1 bar 8 ; r 2 col 3,4 bar 8
1210-1212 - nothing

1301 - r 2 col 0,1,2 bar 0
1302 - r 2 col 0,1,2 bar 1
1303 - r 2 col 0,1,2 bar 2
1304 - r 2 col 0,1,2 bar 3
1305 - r 2 col 0,1,2 bar 4
1306 - r 2 col 0,1,2 bar 5
1307 - r 2 col 0,1,2 bar 6
1308 - r 2 col 0,1,2 bar 7
1309 - r 2 col 0,1,2 bar 8
1310-1312 - nothing

1401 - r 1 col 6,7,8,9 bar 0
1402 - r 1 col 6,7,8,9 bar 1
1403 - r 1 col 6,7,8,9 bar 2
1404 - r 1 col 6,7,8,9,10 bar 3
1405 - r 1 col 6,7,8,9,10 bar 4
1406 - r 1 col 6,7,8,9,10 bar 5
1407 - r 1 col 6,7,8,9,10 bar 6
1408 - r 1 col 6,7,8,9,10,11 bar 7
1409 - r 1 col 6,7,8,9,10,11 bar 8
1410-1412 - nothing

1501 - r 1 col 2,3,4,5 bar 0
1502 - r 1 col 2,3,4,5 bar 1
1503 - r 1 col 2,3,4,5 bar 2
1504 - r 1 col 1,2,3,4,5 bar 3
1505 - r 1 col 1,2,3,4,5 bar 4
1506 - r 1 col 1,2,3,4,5 bar 5
1507 - r 1 col 1,2,3,4,5 bar 6
1508 - r 1 col 0,1,2,3,4,5 bar 7
1509 - r 1 col 0,1,2,3,4,5 bar 8
1510-1512 - nothing

1601 - r 1 col 2,3,4 bar 0
1602 - r 1 col 2,3,4 bar 1
1603 - r 1 col 2,3,4 bar 2
1604 - r 1 col 2,3,4 bar 3
1605 - r 1 col 2,3,4 bar 4
1606 - r 1 col 2,3,4 bar 5
1607 - r 1 col 2,3,4 bar 6
1608 - r 1 col 2,3,4 bar 7
1609 - r 1 col 2,3,4 bar 8
1610-1612 - nothing

*/