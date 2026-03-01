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
// Type identification for basic logical visual element regions.
//
typedef enum 
{
    RegionTypeChar,
    RegionTypeBar,
    RegionTypeCircle,
    RegionTypeNumberList

} RegionType;

//
// Sub types for the specific implementations of the basic ASCII character
// element region implementations.
//
typedef enum 
{
    RegionSubTypeChar5x7,
    RegionSubTypeChar14Seg,
    RegionSubTypeChar7Seg,
    RegionSubTypeChar123,

} RegionSubTypeChar;

//
// Aggregation of the the various region sub types.
//
typedef union _RegionSubType
{
    RegionSubTypeChar subChar;

} RegionSubType;

//
// Defines one region entry with logically approximate but contiguous id's & groups.
// Composite graphics such as bars, circles and number lists are considered single characters.
//
// Some elements are so specfic in their design there is no generic representation requiring
// one off special handling.
//
// Real maximally complex example: Aiwa NSX-520
//
//   type        subtype       id len
// ----------------------------------
// - Char        Char14Seg,     0,  5
// - Char        Char7Seg,      1,  4
// - Char        Char123        2,  1
// - Char        Char123        3,  1
// - Char        Char123        4,  1
// - Bar,                       0,  2
// - Bar,                       1,  9
// - NumberList,                0,  1
// - Circle,                    0,  1
// - Circle,                    1,  1
// - Circle,                    2,  1
//
typedef struct _Region
{
    RegionType    type;
    RegionSubType subType;
    UINT8         id;
    UINT8         len;

} Region;

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
// This should be part of IVfdLayout, and can also add programatic Manufacturer & Model strings.
// Should we also git rid of the inheritance and just use a single API with false returns by default?
//
// Defines one layout map entry with logically approximate but contiguous, unique rows & columns.
//
// There is ALWAYS a IvfdLayoutSymbol on every display.
//
// Notes:
// We can pass Vfd to Char14Seg in the API call and make it global to save RAM.
//
class IVfdLayout
{
public:

    //
    // Returns the region map for all the group elements in the display.
    //
    virtual void getRegionMap(
        const Region **p_region,
        UINT8 *numEntries) = 0;

    //
    // Returns the SegmentMap groups of 7 segment digits for the Region::id.
    //
    // numEntries is also equivalent to the number of digits in the region, Region::len.
    //
    // returns false if the region doesn't exist.
    //
    virtual bool getSegmentGroup7Seg(
        UINT8 regionId,
        const SegmentGroup7Seg **p_segGroup,
        UINT8 *numEntries)
    {
        return false;
    };

    //
    // Returns the SegmentMap groups of 14 or 15 segment digits for the Region::id.
    //
    // numEntries is also equivalent to the number of digits in the region, Region::len.
    //
    // returns false if the region doesn't exist.
    //
    virtual bool getSegmentGroup14Seg(
        UINT8 regionId,
        const SegmentGroup14Seg **p_segGroup,
        UINT8 *numEntries)
    {
        return false;
    };

};

#endif
