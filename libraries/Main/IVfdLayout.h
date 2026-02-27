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
#ifndef IVfdLayout_h
#define IVfdLayout_h

#include "Arduino.h"
#include "Types.h"
#include "Segments.h"


//
// Segment group for 7 segment display characters.
// Character encoding is more efficient with direct index.
// As an array, this can represent a group of characters.
//
typedef struct _SegmentGroup7Seg
{
    SegmentMap a;
    SegmentMap b;
    SegmentMap c;
    SegmentMap d;
    SegmentMap e;
    SegmentMap f;
    SegmentMap g;

} SegmentGroup7Seg;


//
// Segment group for 14 segment display characters,
// including 15 segment versions with the centre dot.
// Character encoding is more efficient with direct index.
// As an array, this can represent a group of characters.
//
typedef struct _SegmentGroup14Seg
{
    SegmentMap a;
    SegmentMap b;
    SegmentMap c;
    SegmentMap d;
    SegmentMap e;
    SegmentMap f;
    SegmentMap g1;
    SegmentMap g2;
    SegmentMap h;
    SegmentMap i;
    SegmentMap j;
    SegmentMap k;
    SegmentMap l;
    SegmentMap m;
    // Optional centre dot for some displays
    SegmentMap s;
    // Optional Decimal Point on some characters
    SegmentMap dp;

} SegmentGroup14Seg;


//
// Aggregate container interface class for all the display layout information.
//
// In future, it may be a place to put something that describes the overall layout if needed?
// e.g. random example: TEAC RW-CD22
// - row 0, col 0, 8-segment bar    (IVfdLayoutBar)
// - row 1, col 0, 8-segment bar    (IVfdLayoutBar)
// - row 2, col  0,  2 digit  7-seg (IVfdLayout7Seg)
// - row 2, col  2,  9 digit 14-seg (IVfdLayout14Seg)
// - row 2, col 11,  2 digit  7-seg (IVfdLayout7Seg)
//

//
// This should be part of IVfdLayout, and can also add programatic Manufacturer & Model strings.
// Should we also git rid of the inheritance and just use a single API with false returns by default?
//
// Defines one layout map entry with logically approximate but contiguous rows & columns.
//
// There is ALWAYS a IvfdLayoutSymbol on every display.
//
// Notes:
// We can pass Vfd to Char14Seg in the API call and make it global to save RAM.
//
//typedef struct _VfdLayoutRegionMap
//{
//    UINT8 row;
//    UINT8 col;
//    UINT8 len;
//    RegionType type; // 7Seg, 14Seg, HorzBar, VertBar, Circle etc.
//
//} VfdLayoutRegionMap;


class IVfdLayout
{
public:

    //
    // Returns the SegmentMap groups of 7 segment digits based on
    // row and column general coordinates. 
    //
    // numEntries is also equivalent to the number of digits in the group.
    //
    // returns false if a group doesn't exist.
    //
    virtual bool getSegmentGroup7Seg(
        UINT8 row,
        UINT8 col,
        const SegmentGroup7Seg **p_segGroup,
        UINT8 *numEntries)
    {
        return false;
    };

    //
    // Returns the SegmentMap groups of 14 or 15 segment digits based on
    // row and column general coordinates. 
    //
    // numEntries is also equivalent to the number of digits in the group.
    //
    // returns false if a group doesn't exist.
    //
    virtual bool getSegmentGroup14Seg(
        UINT8 row,
        UINT8 col,
        const SegmentGroup14Seg **p_segGroup,
        UINT8 *numEntries)
    {
        return false;
    };

};

#endif
