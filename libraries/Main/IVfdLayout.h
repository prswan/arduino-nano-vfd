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
#include "Sym.h"


//
// Indication of the compatible drive type for this VFD.
//
typedef enum 
{
    DriveTypeSN75518,
    DriveTypePT6315,
    DriveTypePT6311

} DriveType;

//
// Basic properties for the VFD.
//
typedef struct _Properties
{
    const UINT8* manufacturer;
    const UINT8* model;
    DriveType    driveType;

} Properties;

//
// Type identification for basic logical visual element regions.
//
typedef enum 
{
    RegionTypeChar,
    RegionTypeBar,
    RegionTypeCircle,
    RegionTypeNumberList,

    RegionTypeCustom

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
// Single standalone group of ad-hoc miscellaneous symbols not
// part of any character or composite display element.
//
// Where there are multiple of the same symbol, the instance
// count differentiates them. In general, the symbol group 
// array & instance count runs left to right and top to bottom.
//
typedef struct _SegmentGroupSymbol
{
    Sym   sym;
    UINT8 instance;
    UINT8 pinG;
    UINT8 pinS;

} SegmentGroupSymbol;

//
// Segment group for 7 segment display characters.
// As an array, this can represent a group of characters.
//
typedef struct _SegmentGroup7Seg
{
    UINT8 pinG;

    struct {
        UINT8 a;
        UINT8 b;
        UINT8 c;
        UINT8 d;
        UINT8 e;
        UINT8 f;
        UINT8 g;
    } pinS;

} SegmentGroup7Seg;

//
// Segment group for 14 segment display characters, including:
// - 15 segment versions with the centre dot
// - 17 segement versions with centre & corner dots.
// Character encoding is more efficient with direct index.
// As an array, this can represent a group of characters.
//
typedef struct _SegmentGroup14Seg
{
    UINT8 pinG;

    struct {
        UINT8 a;
        UINT8 b;
        UINT8 c;
        UINT8 d;
        UINT8 e;
        UINT8 f;
        UINT8 g1;
        UINT8 g2;
        UINT8 h;
        UINT8 i;
        UINT8 j;
        UINT8 k;
        UINT8 l;
        UINT8 m;
        // Optional 'g' centre dot for some displays
        UINT8 gc;
        // Optional 'a' top corner dots for some displays
        UINT8 ac;
        // Optional 'd' bottom corner dots for some displays
        UINT8 dc;
    } pinS;

} SegmentGroup14Seg;

//
// Segment group for a bar. At the time of writing:
// - None yet owned that use >1 grid for 1 bar.
// - None yet owned with >16 segments 
//   (seen photos of some that look longer, though)
//
// "vertical" 
//  - true  -  the bar runs vertically.
//  - false -  the bar runs horizontally.
//
// "reverse"
//  - true  - a horizontal bar runs right to left.
//          - a vertical bar runs top to bottom.
//  - false - a horizontal bar runs left to right (e.g. Tape VU meter).
//          - a vertical bar runs bottom to top (e.g. Graphic EQ).
//
// "seg1Symbol"
//  - true  - Segment 1 also lights other symbols in addtition to bar 1.
//  - false - Segment 1 is the same as Segment 2+
//
// As an array, this can represent a group of bars.
//
typedef struct _SegmentGroupBar
{
    bool vertical;
    bool reverse;
    bool seg1Symbol;

    UINT8 pinG;
    UINT8 pinS[16];

} SegmentGroupBar;

//
// Segment group for a number list, e.g. the track numbers on CD players. 
// e.g. TEAC PD-D1200:
//
//  1  2  3  4  5
//  6  7  8  9 10
// 11 12 13 14 15
// 16 17 18 19 20
//
// "numListLen" 
//  - The number of numbers in the list e.g. for 1 to 20 this is 20.
//
// "numCols"
//  - The number of columns in the number list grid, e.g. 5
//
// "numRows"
//  - The number of rows in the number list grid, e.g. 4
//
// "topToBottom"
//  - true  - The numbers increment row first.
//  - false - The numbers increment col first, left-to-right.
// false in the example above.
//
// "grid"
//  - Array of grids containing an array "list" of number value
//    and segement pin pairs for the number list.
//
typedef struct _SegmentGroupNumberList
{
    UINT8 numListLen;
    UINT8 numCols;
    UINT8 numRows;
    bool  topToBottom;

    struct {
        UINT8 pinG;

        struct {
            UINT8 value;
            UINT8 pinS;
        } list[20];

    } grid[3];

} SegmentGroupNumberList;

//
// When it's just too oddball wierd to categorize, provide a means
// to send back unstructured glyph layout information. It's intended
// to pair with a matching symbol display implementation to use it,
// unique to the VFD.
//
typedef struct _SegmentGroupGraphicSymbol
{
    UINT8 pinG;
    UINT8 pinS[16];

} SegmentGroupGraphicSymbol;

//
// Symbol display group paired with a unique graphic symbol.
//
// "sym" & "instance" are used to match the symbol.
// "segGroupIndex" is the entry into the paired "SegmentGroupGraphicSymbol" table.
// "on" defines whether the segment is on or off.
//
typedef struct _DisplayGroupGraphicSymbol
{
    Sym   sym;
    UINT8 instance;
    UINT8 segGroupIndex;
    UINT8 on[16];

} DisplayGroupGraphicSymbol;

//
// Defines one layout map entry with logically approximate but contiguous, unique regions & columns.
//
class IVfdLayout
{
public:

    //
    // Returns the general properties of the VFD
    // The returned properties are located in PROGMEM.
    //
    virtual void getProperties(
        const Properties **p_properties) = 0;


    //
    // Returns the region map for all the group elements in the display.
    //
    virtual void getRegionMap(
        const Region **p_region,
        UINT8 *numEntries) = 0;

    //
    // Returns the ad-hoc miscellaneous symbols group list.
    //
    // returns false if no symbols exist.
    //
    virtual bool getSegmentGroupSymbol(
        const SegmentGroupSymbol **p_segGroup,
        UINT8 *numEntries)
    {
        return false;
    };

    //
    // Returns the groups of 7 segment digits for the Region::id.
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
    // Returns the groups of 14 or 15 segment digits for the Region::id.
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

    //
    // Returns the groups of bars for the Region::id.
    //
    // numEntries is also equivalent to the number of bars in the region, Region::len.
    //
    // returns false if the region doesn't exist.
    //
    virtual bool getSegmentGroupBar(
        UINT8 regionId,
        const SegmentGroupBar **p_segGroup,
        UINT8 *numEntries)
    {
        return false;
    };

    //
    // Returns groups of custom unstructured glyph elements and the
    // symbol display group mappings to use them.
    //
    // returns false if the region doesn't exist.
    //
    virtual bool getSegmentGroupGraphicSymbol(
        const SegmentGroupGraphicSymbol **p_segmentGroup,
        UINT8 *numSegmentGroupEntries,
        const DisplayGroupGraphicSymbol **p_displayGroup,
        UINT8 *numDisplayGroupEntries)
    {
        return false;
    };

    //
    // Returns the groups of number lists for the Region::id.
    //
    // numEntries is also equivalent to the number of lists in the region, Region::len.
    //
    // returns false if the region doesn't exist.
    //
    virtual bool getSegmentGroupNumberList(
        UINT8 regionId,
        const SegmentGroupNumberList **p_segGroup,
        UINT8 *numEntries)
    {
        return false;
    };
};

#endif
