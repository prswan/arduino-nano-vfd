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
#include "SamsungBDP1590Layout.h"

//
// 7x 14-segment display with centre dot.
//
static const Region s_region[] PROGMEM =
{
    // type,          subType,                 id, len
    {RegionTypeChar,  RegionSubTypeChar14Seg,   0,   6}
};

//
// 6x 14-segment display with centre dot and four corner dots (to figure that out later).
//
static const SegmentGroup14Seg s_segmentGroup14Seg[] PROGMEM =
{
    // seg, row ,col, pinG, pinS
    {
        {S_14SEG_a,   0, 0, 1,  1},
        {S_14SEG_b,   0, 0, 1,  2},
        {S_14SEG_c,   0, 0, 1,  3},
        {S_14SEG_d,   0, 0, 1,  4},
        {S_14SEG_e,   0, 0, 1,  5},
        {S_14SEG_f,   0, 0, 1,  6},
        {S_14SEG_g1,  0, 0, 1,  7},
        {S_14SEG_g2,  0, 0, 1,  8},
        {S_14SEG_h,   0, 0, 1,  9},
        {S_14SEG_i,   0, 0, 1, 10},
        {S_14SEG_j,   0, 0, 1, 11},
        {S_14SEG_k,   0, 0, 1, 12},
        {S_14SEG_l,   0, 0, 1, 13},
        {S_14SEG_m,   0, 0, 1, 14},
        {S_14SEG_s,   0, 0, 1, 15},
        {S_14SEG_dp,  0, 0, 1, 16},
    },
    {
        {S_14SEG_a,   0, 1, 2,  1},
        {S_14SEG_b,   0, 1, 2,  2},
        {S_14SEG_c,   0, 1, 2,  3},
        {S_14SEG_d,   0, 1, 2,  4},
        {S_14SEG_e,   0, 1, 2,  5},
        {S_14SEG_f,   0, 1, 2,  6},
        {S_14SEG_g1,  0, 1, 2,  7},
        {S_14SEG_g2,  0, 1, 2,  8},
        {S_14SEG_h,   0, 1, 2,  9},
        {S_14SEG_i,   0, 1, 2, 10},
        {S_14SEG_j,   0, 1, 2, 11},
        {S_14SEG_k,   0, 1, 2, 12},
        {S_14SEG_l,   0, 1, 2, 13},
        {S_14SEG_m,   0, 1, 2, 14},
        {S_14SEG_s,   0, 1, 2, 15},
        {S_14SEG_dp,  0, 1, 2, 16},
    },
    {
        {S_14SEG_a,   0, 2, 3,  1},
        {S_14SEG_b,   0, 2, 3,  2},
        {S_14SEG_c,   0, 2, 3,  3},
        {S_14SEG_d,   0, 2, 3,  4},
        {S_14SEG_e,   0, 2, 3,  5},
        {S_14SEG_f,   0, 2, 3,  6},
        {S_14SEG_g1,  0, 2, 3,  7},
        {S_14SEG_g2,  0, 2, 3,  8},
        {S_14SEG_h,   0, 2, 3,  9},
        {S_14SEG_i,   0, 2, 3, 10},
        {S_14SEG_j,   0, 2, 3, 11},
        {S_14SEG_k,   0, 2, 3, 12},
        {S_14SEG_l,   0, 2, 3, 13},
        {S_14SEG_m,   0, 2, 3, 14},
        {S_14SEG_s,   0, 2, 3, 15},
        {S_14SEG_dp,  0, 2, 3, 16},
    },
    {
        {S_14SEG_a,   0, 3, 4,  1},
        {S_14SEG_b,   0, 3, 4,  2},
        {S_14SEG_c,   0, 3, 4,  3},
        {S_14SEG_d,   0, 3, 4,  4},
        {S_14SEG_e,   0, 3, 4,  5},
        {S_14SEG_f,   0, 3, 4,  6},
        {S_14SEG_g1,  0, 3, 4,  7},
        {S_14SEG_g2,  0, 3, 4,  8},
        {S_14SEG_h,   0, 3, 4,  9},
        {S_14SEG_i,   0, 3, 4, 10},
        {S_14SEG_j,   0, 3, 4, 11},
        {S_14SEG_k,   0, 3, 4, 12},
        {S_14SEG_l,   0, 3, 4, 13},
        {S_14SEG_m,   0, 3, 4, 14},
        {S_14SEG_s,   0, 3, 4, 15},
        {S_14SEG_dp,  0, 3, 4, 16},
    },
};

void SamsungBDP1590Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};

bool SamsungBDP1590Layout::getSegmentGroup14Seg(
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

/*
Symbols


*/