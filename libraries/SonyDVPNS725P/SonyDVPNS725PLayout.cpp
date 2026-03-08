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
#include "SonyDVPNS725PLayout.h"


static const UINT8 s_manufacturer[] PROGMEM = "SONY";
static const UINT8 s_model[]        PROGMEM = "DVP-NS725P";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
    DriveTypeSN75518,
};

//
// 7x 14-segment display with centre dot.
//
static const Region s_region[] PROGMEM =
{
    // type,          subType,                 id, len
    {RegionTypeChar,  RegionSubTypeChar14Seg,   0,   7}
};

static const SegmentGroupSymbol s_segmentGroupSymbol[] PROGMEM =
{
    // sym,        instance, pinG, pinS
    {SymText_DVD,         0,    2,    4}, // row 1
    {SymPlayForward,      0,    1,   23},
    {SymPause,            0,    1,    4},
    {SymText_TRK,         0,    7,    4},

    {SymText_V,           0,    2,   21}, // row 2
    {SymText_CD,          0,    2,   22},
    {SymRepeat,           0,    1,   21},
    {SymText_1,           0,    1,   22},
    {SymMovieCamera,      0,    7,   22},

    {SymColon,            0,    5,    4},
    {SymColon,            1,    3,    4},

    {SymDolbyDoubleD_D,   0,    2,   20}, // row 3
    {SymText_MP3,         0,    1,   20},
    {SymText_dts,         0,    7,   20},

    {SymDecimalPoint,     0,    7,   23},
    {SymDecimalPoint,     1,    6,   23},
    {SymDecimalPoint,     2,    5,   23},
    {SymDecimalPoint,     3,    4,   23},
    {SymDecimalPoint,     4,    3,   23},
    {SymDecimalPoint,     5,    2,   23},
};

//
// 7x 14-segment display with centre dot.
// These were documented in the service manual.
//
static const SegmentGroup14Seg s_segmentGroup14Seg[] PROGMEM =
{
    // seg, row ,col, pinG, pinS
    {
        {S_14SEG_a,   0, 0, 7,  5},
        {S_14SEG_b,   0, 0, 7,  9},
        {S_14SEG_c,   0, 0, 7, 18},
        {S_14SEG_d,   0, 0, 7, 19},
        {S_14SEG_e,   0, 0, 7, 14},
        {S_14SEG_f,   0, 0, 7, 10},
        {S_14SEG_g1,  0, 0, 7, 13},
        {S_14SEG_g2,  0, 0, 7, 11},
        {S_14SEG_h,   0, 0, 7,  6},
        {S_14SEG_i,   0, 0, 7,  7},
        {S_14SEG_j,   0, 0, 7,  8},
        {S_14SEG_k,   0, 0, 7, 17},
        {S_14SEG_l,   0, 0, 7, 16},
        {S_14SEG_m,   0, 0, 7, 15},
        {S_14SEG_s,   0, 0, 7, 12},
        {S_14SEG_dp,  0, 0, 7, 23},
    },
    {
        {S_14SEG_a,   0, 1, 6,  5},
        {S_14SEG_b,   0, 1, 6,  9},
        {S_14SEG_c,   0, 1, 6, 18},
        {S_14SEG_d,   0, 1, 6, 19},
        {S_14SEG_e,   0, 1, 6, 14},
        {S_14SEG_f,   0, 1, 6, 10},
        {S_14SEG_g1,  0, 1, 6, 13},
        {S_14SEG_g2,  0, 1, 6, 11},
        {S_14SEG_h,   0, 1, 6,  6},
        {S_14SEG_i,   0, 1, 6,  7},
        {S_14SEG_j,   0, 1, 6,  8},
        {S_14SEG_k,   0, 1, 6, 17},
        {S_14SEG_l,   0, 1, 6, 16},
        {S_14SEG_m,   0, 1, 6, 15},
        {S_14SEG_s,   0, 1, 6, 12},
        {S_14SEG_dp,  0, 1, 6, 23},
    },
    {
        {S_14SEG_a,   0, 2, 5,  5},
        {S_14SEG_b,   0, 2, 5,  9},
        {S_14SEG_c,   0, 2, 5, 18},
        {S_14SEG_d,   0, 2, 5, 19},
        {S_14SEG_e,   0, 2, 5, 14},
        {S_14SEG_f,   0, 2, 5, 10},
        {S_14SEG_g1,  0, 2, 5, 13},
        {S_14SEG_g2,  0, 2, 5, 11},
        {S_14SEG_h,   0, 2, 5,  6},
        {S_14SEG_i,   0, 2, 5,  7},
        {S_14SEG_j,   0, 2, 5,  8},
        {S_14SEG_k,   0, 2, 5, 17},
        {S_14SEG_l,   0, 2, 5, 16},
        {S_14SEG_m,   0, 2, 5, 15},
        {S_14SEG_s,   0, 2, 5, 12},
        {S_14SEG_dp,  0, 2, 5, 23},
    },
    {
        {S_14SEG_a,   0, 3, 4,  5},
        {S_14SEG_b,   0, 3, 4,  9},
        {S_14SEG_c,   0, 3, 4, 18},
        {S_14SEG_d,   0, 3, 4, 19},
        {S_14SEG_e,   0, 3, 4, 14},
        {S_14SEG_f,   0, 3, 4, 10},
        {S_14SEG_g1,  0, 3, 4, 13},
        {S_14SEG_g2,  0, 3, 4, 11},
        {S_14SEG_h,   0, 3, 4,  6},
        {S_14SEG_i,   0, 3, 4,  7},
        {S_14SEG_j,   0, 3, 4,  8},
        {S_14SEG_k,   0, 3, 4, 17},
        {S_14SEG_l,   0, 3, 4, 16},
        {S_14SEG_m,   0, 3, 4, 15},
        {S_14SEG_s,   0, 3, 4, 12},
        {S_14SEG_dp,  0, 3, 4, 23},
    },
    {
        {S_14SEG_a,   0, 4, 3,  5},
        {S_14SEG_b,   0, 4, 3,  9},
        {S_14SEG_c,   0, 4, 3, 18},
        {S_14SEG_d,   0, 4, 3, 19},
        {S_14SEG_e,   0, 4, 3, 14},
        {S_14SEG_f,   0, 4, 3, 10},
        {S_14SEG_g1,  0, 4, 3, 13},
        {S_14SEG_g2,  0, 4, 3, 11},
        {S_14SEG_h,   0, 4, 3,  6},
        {S_14SEG_i,   0, 4, 3,  7},
        {S_14SEG_j,   0, 4, 3,  8},
        {S_14SEG_k,   0, 4, 3, 17},
        {S_14SEG_l,   0, 4, 3, 16},
        {S_14SEG_m,   0, 4, 3, 15},
        {S_14SEG_s,   0, 4, 3, 12},
        {S_14SEG_dp,  0, 4, 3, 23},
    },
    {
        {S_14SEG_a,   0, 5, 2,  5},
        {S_14SEG_b,   0, 5, 2,  9},
        {S_14SEG_c,   0, 5, 2, 18},
        {S_14SEG_d,   0, 5, 2, 19},
        {S_14SEG_e,   0, 5, 2, 14},
        {S_14SEG_f,   0, 5, 2, 10},
        {S_14SEG_g1,  0, 5, 2, 13},
        {S_14SEG_g2,  0, 5, 2, 11},
        {S_14SEG_h,   0, 5, 2,  6},
        {S_14SEG_i,   0, 5, 2,  7},
        {S_14SEG_j,   0, 5, 2,  8},
        {S_14SEG_k,   0, 5, 2, 17},
        {S_14SEG_l,   0, 5, 2, 16},
        {S_14SEG_m,   0, 5, 2, 15},
        {S_14SEG_s,   0, 5, 2, 12},
        {S_14SEG_dp,  0, 5, 2, 23},
    },
    {
        {S_14SEG_a,   0, 6, 1,  5},
        {S_14SEG_b,   0, 6, 1,  9},
        {S_14SEG_c,   0, 6, 1, 18},
        {S_14SEG_d,   0, 6, 1, 19},
        {S_14SEG_e,   0, 6, 1, 14},
        {S_14SEG_f,   0, 6, 1, 10},
        {S_14SEG_g1,  0, 6, 1, 13},
        {S_14SEG_g2,  0, 6, 1, 11},
        {S_14SEG_h,   0, 6, 1,  6},
        {S_14SEG_i,   0, 6, 1,  7},
        {S_14SEG_j,   0, 6, 1,  8},
        {S_14SEG_k,   0, 6, 1, 17},
        {S_14SEG_l,   0, 6, 1, 16},
        {S_14SEG_m,   0, 6, 1, 15},
        {S_14SEG_s,   0, 6, 1, 12},
        {S_14SEG_dp,  0, 6, 1, 23},
    },
};

void SonyDVPNS725PLayout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void SonyDVPNS725PLayout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool SonyDVPNS725PLayout::getSegmentGroupSymbol(
    const SegmentGroupSymbol **p_segGroup,
    UINT8 *numEntries)
{
    *p_segGroup = s_segmentGroupSymbol;
    *numEntries = ARRAYSIZE(s_segmentGroupSymbol);
    return true;
};

bool SonyDVPNS725PLayout::getSegmentGroup14Seg(
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
