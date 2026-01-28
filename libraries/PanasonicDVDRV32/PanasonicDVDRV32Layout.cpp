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
#include "PanasonicDVDRV32Layout.h"

//
// 12x 14-segment standard display.
// The manual didn't document the layout, reverse engineered using the LayoutFinder.
// The manual does define the grid & segment pins, so the initial 1-1 mapping using 
// 4 grids G9-G12 for the numbers for the first pass with LayoutFinder.
// These are kept here as an example.
//
static const SegmentGroup14Seg s_segmentGroup14Seg[] PROGMEM =
{
    // seg, row ,col, pinG, pinS
    {
        {S_14SEG_a,   0, 0, 42,  5},
        {S_14SEG_b,   0, 0, 42,  6},
        {S_14SEG_c,   0, 0, 42,  7},
        {S_14SEG_d,   0, 0, 42,  8},
        {S_14SEG_e,   0, 0, 42,  9},
        {S_14SEG_f,   0, 0, 42, 10},
        {S_14SEG_g1,  0, 0, 42, 11},
        {S_14SEG_g2,  0, 0, 42, 12},
        {S_14SEG_h,   0, 0, 42, 13},
        {S_14SEG_i,   0, 0, 42, 14},
        {S_14SEG_j,   0, 0, 42, 15},
        {S_14SEG_k,   0, 0, 42, 16},
        {S_14SEG_l,   0, 0, 42, 17},
        {S_14SEG_m,   0, 0, 42, 18},
        {S_14SEG_s,   0, 0,  0,  0}, // No centre dot
        {S_14SEG_dp,  0, 0,  0,  0}, // No decimal points
    },
    {
        {S_14SEG_a,   0, 1, 41,  5},
        {S_14SEG_b,   0, 1, 41,  6},
        {S_14SEG_c,   0, 1, 41,  7},
        {S_14SEG_d,   0, 1, 41,  8},
        {S_14SEG_e,   0, 1, 41,  9},
        {S_14SEG_f,   0, 1, 41, 10},
        {S_14SEG_g1,  0, 1, 41, 11},
        {S_14SEG_g2,  0, 1, 41, 12},
        {S_14SEG_h,   0, 1, 41, 13},
        {S_14SEG_i,   0, 1, 41, 14},
        {S_14SEG_j,   0, 1, 41, 15},
        {S_14SEG_k,   0, 1, 41, 16},
        {S_14SEG_l,   0, 1, 41, 17},
        {S_14SEG_m,   0, 1, 41, 18},
        {S_14SEG_s,   0, 1,  0,  0}, // No centre dot
        {S_14SEG_dp,  0, 1,  0,  0}, // No decimal points
    },
    {
        {S_14SEG_a,   0, 2, 40,  5},
        {S_14SEG_b,   0, 2, 40,  6},
        {S_14SEG_c,   0, 2, 40,  7},
        {S_14SEG_d,   0, 2, 40,  8},
        {S_14SEG_e,   0, 2, 40,  9},
        {S_14SEG_f,   0, 2, 40, 10},
        {S_14SEG_g1,  0, 2, 40, 11},
        {S_14SEG_g2,  0, 2, 40, 12},
        {S_14SEG_h,   0, 2, 40, 13},
        {S_14SEG_i,   0, 2, 40, 14},
        {S_14SEG_j,   0, 2, 40, 15},
        {S_14SEG_k,   0, 2, 40, 16},
        {S_14SEG_l,   0, 2, 40, 17},
        {S_14SEG_m,   0, 2, 40, 18},
        {S_14SEG_s,   0, 2,  0,  0}, // No centre dot
        {S_14SEG_dp,  0, 2,  0,  0}, // No decimal points
    },
    {
        {S_14SEG_a,   0, 3, 39,  5},
        {S_14SEG_b,   0, 3, 39,  6},
        {S_14SEG_c,   0, 3, 39,  7},
        {S_14SEG_d,   0, 3, 39,  8},
        {S_14SEG_e,   0, 3, 39,  9},
        {S_14SEG_f,   0, 3, 39, 10},
        {S_14SEG_g1,  0, 3, 39, 11},
        {S_14SEG_g2,  0, 3, 39, 12},
        {S_14SEG_h,   0, 3, 39, 13},
        {S_14SEG_i,   0, 3, 39, 14},
        {S_14SEG_j,   0, 3, 39, 15},
        {S_14SEG_k,   0, 3, 39, 16},
        {S_14SEG_l,   0, 3, 39, 17},
        {S_14SEG_m,   0, 3, 39, 18},
        {S_14SEG_s,   0, 3,  0,  0}, // No centre dot
        {S_14SEG_dp,  0, 3,  0,  0}, // No decimal points
    },
    {{S_NONE}}
};

bool PanasonicDVDRV32Layout::getSegmentGroup14Seg(
    UINT8 row,
    const SegmentGroup14Seg **p_segGroup,
    UINT8 *numEntries)
{
    if (row == 0)
    {
        *p_segGroup = s_segmentGroup14Seg;
        *numEntries = ARRAYSIZE(s_segmentGroup14Seg);
        return true;
    }

    return false;
}
