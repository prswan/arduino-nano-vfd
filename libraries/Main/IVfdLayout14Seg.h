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
#ifndef IVfdLayout14Seg_h
#define IVfdLayout14Seg_h

#include "Arduino.h"
#include "Types.h"
#include "Segments.h"

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
    // Optional Decimal Point on some characters
    SegmentMap dp;
    // Optional centre dot for some displays
    SegmentMap s;

} SegmentGroup14Seg;

//
// Interface for the data container class holding the characteristics of the VFD.
//
class IVfdLayout14Seg
{
public:
    //
    // Returns the SegmentMap groups for one column of 14 segment digits
    // Separate groups are used for each row of digits
    // e.g. for 2 digit rows call twice to get each map.
    //
    // numEntries is also equivalent to the number of digits.
    //
    // returns false if a group doesn't exist.
    //
    virtual bool getSegmentGroup14Seg(
        UINT8 row,
        const SegmentGroup14Seg **p_segGroup,
        UINT8 *numEntries) = 0;
};

#endif
