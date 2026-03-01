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

//
// 7x 14-segment display with centre dot.
//
static const Region s_region[] PROGMEM =
{
    // type,          subType,                 id, len
    {RegionTypeChar,  RegionSubTypeChar14Seg,   0,  12}
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

void SonyDVPNS725PLayout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
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

/*
Symbols

0104 - pause symbol
0120 - "MP3"
0121 - repeat symbol
0122 - "1" next to repeat symbol
0123 - play symbol
0204 - "DVD"
0220 - dolby double D symbol and "D"
0221 - "V"
0222 - "CD" after "V"
0223 - col 5 dp
0304 - col 4 colon
0323 - col 4 dp
0423 - col 3 dp
0523 - col 2 dp
0623 - col 1 dp
0723 - col 0 dp
0704 - "TRK"
0720 - "Dts" symbol
0722 - movie camera symbol

*/