//
// Copyright (c) 2025, Paul R. Swan
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
#ifndef IVfdLayout7Seg_h
#define IVfdLayout7Seg_h

#include "Arduino.h"
#include "Types.h"
#include "Segments.h"

//
// Maps the display element (segments) to the Grid and Segment pins.
//
// Most displays have several of the same segment type (e.g. in digits).
// To distinguish duplicate segments are counted by row and column
// starting from a top left origin counting columns left to right and
// rows top to bottom.
//
// e.g. 88:88
//  - The segments in the 4 digits are addressed as row=0 and col=0,1,2,3
//
// e.g. 88
//      88
//  - The segments in the 4 digits are addressed as row=0,1 and col=0,1
//
// Since most consumer service manuals use G1...Gn and S1...Sn the same
// is used here with 0 being invalid for ease of transcription.
//
typedef struct _SegmentMap
{
    Segment seg;
    UINT8 row;  // The row instance count
    UINT8 col;  // The column instance count
    UINT8 pinG; // Grid pin
    UINT8 pinS; // Segment pin

} SegmentMap;

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
// Interface for the data container class holding the characteristics of the VFD.
//
class IVfdLayout7Seg
{
public:
    //
    // Returns the SegmentMap groups for one column of 7 segment digits
    // Separate groups are used for each row of digits
    // e.g. for 2 digit rows call twice to get each map.
    //
    // numEntries is also equivalent to the number of digits.
    //
    // returns false if a group doesn't exist.
    //
    virtual bool getSegmentGroup7Seg(
        UINT8 row,
        const SegmentGroup7Seg **p_segGroup,
        UINT8 *numEntries) = 0;
};

#endif
