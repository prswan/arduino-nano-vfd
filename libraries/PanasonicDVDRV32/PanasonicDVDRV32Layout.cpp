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


/*
//
// 12x 14-segment standard display.
// The manual didn't document the layout, reverse engineered using the LayoutFinder.
// The manual does define the grid & segment pins, so the initial 1-1 mapping using 
// 4 grids G9-G12 for the numbers for the first pass with LayoutFinder.
// - G1 or G13 guessed as the symbols grid on the far left, thus avoided.
// These are kept here as an example.
//
static const SegmentGroup14Seg s_segmentGroup14Seg[] PROGMEM =
{
    // seg, row ,col, pinG, pinS
    {
        {S_14SEG_a,   0, 0,  9,  1},
        {S_14SEG_b,   0, 0,  9,  2},
        {S_14SEG_c,   0, 0,  9,  3},
        {S_14SEG_d,   0, 0,  9,  4},
        {S_14SEG_e,   0, 0,  9,  5},
        {S_14SEG_f,   0, 0,  9,  6},
        {S_14SEG_g1,  0, 0,  9,  7},
        {S_14SEG_g2,  0, 0,  9,  8},
        {S_14SEG_h,   0, 0,  9,  9},
        {S_14SEG_i,   0, 0,  9, 10},
        {S_14SEG_j,   0, 0,  9, 11},
        {S_14SEG_k,   0, 0,  9, 12},
        {S_14SEG_l,   0, 0,  9, 13},
        {S_14SEG_m,   0, 0,  9, 14},
        {S_14SEG_s,   0, 0,  0,  0}, // No centre dot
        {S_14SEG_dp,  0, 0,  0,  0}, // No decimal points
    },
    {
        {S_14SEG_a,   0, 1, 10,  1},
        {S_14SEG_b,   0, 1, 10,  2},
        {S_14SEG_c,   0, 1, 10,  3},
        {S_14SEG_d,   0, 1, 10,  4},
        {S_14SEG_e,   0, 1, 10,  5},
        {S_14SEG_f,   0, 1, 10,  6},
        {S_14SEG_g1,  0, 1, 10,  7},
        {S_14SEG_g2,  0, 1, 10,  8},
        {S_14SEG_h,   0, 1, 10,  9},
        {S_14SEG_i,   0, 1, 10, 10},
        {S_14SEG_j,   0, 1, 10, 11},
        {S_14SEG_k,   0, 1, 10, 12},
        {S_14SEG_l,   0, 1, 10, 13},
        {S_14SEG_m,   0, 1, 10, 14},
        {S_14SEG_s,   0, 1,  0,  0}, // No centre dot
        {S_14SEG_dp,  0, 1,  0,  0}, // No decimal points
    },
    {
        {S_14SEG_a,   0, 2, 11,  1},
        {S_14SEG_b,   0, 2, 11,  2},
        {S_14SEG_c,   0, 2, 11,  3},
        {S_14SEG_d,   0, 2, 11,  4},
        {S_14SEG_e,   0, 2, 11,  5},
        {S_14SEG_f,   0, 2, 11,  6},
        {S_14SEG_g1,  0, 2, 11,  7},
        {S_14SEG_g2,  0, 2, 11,  8},
        {S_14SEG_h,   0, 2, 11,  9},
        {S_14SEG_i,   0, 2, 11, 10},
        {S_14SEG_j,   0, 2, 11, 11},
        {S_14SEG_k,   0, 2, 11, 12},
        {S_14SEG_l,   0, 2, 11, 13},
        {S_14SEG_m,   0, 2, 11, 14},
        {S_14SEG_s,   0, 2,  0,  0}, // No centre dot
        {S_14SEG_dp,  0, 2,  0,  0}, // No decimal points
    },
    {
        {S_14SEG_a,   0, 3, 12,  1},
        {S_14SEG_b,   0, 3, 12,  2},
        {S_14SEG_c,   0, 3, 12,  3},
        {S_14SEG_d,   0, 3, 12,  4},
        {S_14SEG_e,   0, 3, 12,  5},
        {S_14SEG_f,   0, 3, 12,  6},
        {S_14SEG_g1,  0, 3, 12,  7},
        {S_14SEG_g2,  0, 3, 12,  8},
        {S_14SEG_h,   0, 3, 12,  9},
        {S_14SEG_i,   0, 3, 12, 10},
        {S_14SEG_j,   0, 3, 12, 11},
        {S_14SEG_k,   0, 3, 12, 12},
        {S_14SEG_l,   0, 3, 12, 13},
        {S_14SEG_m,   0, 3, 12, 14},
        {S_14SEG_s,   0, 3,  0,  0}, // No centre dot
        {S_14SEG_dp,  0, 3,  0,  0}, // No decimal points
    },
    {{S_NONE}}
};
*/

//
// 12x 14-segment standard display.
// The manual didn't document the layout, reverse engineered using the LayoutFinder.
//
static const SegmentGroup14Seg s_segmentGroup14Seg[] PROGMEM =
{
    // seg, row ,col, pinG, pinS
    {
        {S_14SEG_a,   0,  0, 12,  1},
        {S_14SEG_b,   0,  0, 12,  5},
        {S_14SEG_c,   0,  0, 12,  9},
        {S_14SEG_d,   0,  0, 12, 14},
        {S_14SEG_e,   0,  0, 12, 10},
        {S_14SEG_f,   0,  0, 12,  6},
        {S_14SEG_g1,  0,  0, 12,  8},
        {S_14SEG_g2,  0,  0, 12,  7},
        {S_14SEG_h,   0,  0, 12,  2},
        {S_14SEG_i,   0,  0, 12,  3},
        {S_14SEG_j,   0,  0, 12,  4},
        {S_14SEG_k,   0,  0, 12, 11},
        {S_14SEG_l,   0,  0, 12, 12},
        {S_14SEG_m,   0,  0, 12, 13},
        {S_14SEG_s,   0,  0,  0,  0}, // No centre dot
        {S_14SEG_dp,  0,  0,  0,  0}, // No decimal points
    },
    {
        {S_14SEG_a,   0,  1, 11,  1},
        {S_14SEG_b,   0,  1, 11,  5},
        {S_14SEG_c,   0,  1, 11,  9},
        {S_14SEG_d,   0,  1, 11, 14},
        {S_14SEG_e,   0,  1, 11, 10},
        {S_14SEG_f,   0,  1, 11,  6},
        {S_14SEG_g1,  0,  1, 11,  8},
        {S_14SEG_g2,  0,  1, 11,  7},
        {S_14SEG_h,   0,  1, 11,  2},
        {S_14SEG_i,   0,  1, 11,  3},
        {S_14SEG_j,   0,  1, 11,  4},
        {S_14SEG_k,   0,  1, 11, 11},
        {S_14SEG_l,   0,  1, 11, 12},
        {S_14SEG_m,   0,  1, 11, 13},
    },
    {
        {S_14SEG_a,   0,  2, 10,  1},
        {S_14SEG_b,   0,  2, 10,  5},
        {S_14SEG_c,   0,  2, 10,  9},
        {S_14SEG_d,   0,  2, 10, 14},
        {S_14SEG_e,   0,  2, 10, 10},
        {S_14SEG_f,   0,  2, 10,  6},
        {S_14SEG_g1,  0,  2, 10,  8},
        {S_14SEG_g2,  0,  2, 10,  7},
        {S_14SEG_h,   0,  2, 10,  2},
        {S_14SEG_i,   0,  2, 10,  3},
        {S_14SEG_j,   0,  2, 10,  4},
        {S_14SEG_k,   0,  2, 10, 11},
        {S_14SEG_l,   0,  2, 10, 12},
        {S_14SEG_m,   0,  2, 10, 13},
    },
    {
        {S_14SEG_a,   0,  3,  9,  1},
        {S_14SEG_b,   0,  3,  9,  5},
        {S_14SEG_c,   0,  3,  9,  9},
        {S_14SEG_d,   0,  3,  9, 14},
        {S_14SEG_e,   0,  3,  9, 10},
        {S_14SEG_f,   0,  3,  9,  6},
        {S_14SEG_g1,  0,  3,  9,  8},
        {S_14SEG_g2,  0,  3,  9,  7},
        {S_14SEG_h,   0,  3,  9,  2},
        {S_14SEG_i,   0,  3,  9,  3},
        {S_14SEG_j,   0,  3,  9,  4},
        {S_14SEG_k,   0,  3,  9, 11},
        {S_14SEG_l,   0,  3,  9, 12},
        {S_14SEG_m,   0,  3,  9, 13},
    },
    {
        {S_14SEG_a,   0,  4,  8,  1},
        {S_14SEG_b,   0,  4,  8,  5},
        {S_14SEG_c,   0,  4,  8,  9},
        {S_14SEG_d,   0,  4,  8, 14},
        {S_14SEG_e,   0,  4,  8, 10},
        {S_14SEG_f,   0,  4,  8,  6},
        {S_14SEG_g1,  0,  4,  8,  8},
        {S_14SEG_g2,  0,  4,  8,  7},
        {S_14SEG_h,   0,  4,  8,  2},
        {S_14SEG_i,   0,  4,  8,  3},
        {S_14SEG_j,   0,  4,  8,  4},
        {S_14SEG_k,   0,  4,  8, 11},
        {S_14SEG_l,   0,  4,  8, 12},
        {S_14SEG_m,   0,  4,  8, 13},
    },
    {
        {S_14SEG_a,   0,  5,  7,  1},
        {S_14SEG_b,   0,  5,  7,  5},
        {S_14SEG_c,   0,  5,  7,  9},
        {S_14SEG_d,   0,  5,  7, 14},
        {S_14SEG_e,   0,  5,  7, 10},
        {S_14SEG_f,   0,  5,  7,  6},
        {S_14SEG_g1,  0,  5,  7,  8},
        {S_14SEG_g2,  0,  5,  7,  7},
        {S_14SEG_h,   0,  5,  7,  2},
        {S_14SEG_i,   0,  5,  7,  3},
        {S_14SEG_j,   0,  5,  7,  4},
        {S_14SEG_k,   0,  5,  7, 11},
        {S_14SEG_l,   0,  5,  7, 12},
        {S_14SEG_m,   0,  5,  7, 13},
    },
    {
        {S_14SEG_a,   0,  6,  6,  1},
        {S_14SEG_b,   0,  6,  6,  5},
        {S_14SEG_c,   0,  6,  6,  9},
        {S_14SEG_d,   0,  6,  6, 14},
        {S_14SEG_e,   0,  6,  6, 10},
        {S_14SEG_f,   0,  6,  6,  6},
        {S_14SEG_g1,  0,  6,  6,  8},
        {S_14SEG_g2,  0,  6,  6,  7},
        {S_14SEG_h,   0,  6,  6,  2},
        {S_14SEG_i,   0,  6,  6,  3},
        {S_14SEG_j,   0,  6,  6,  4},
        {S_14SEG_k,   0,  6,  6, 11},
        {S_14SEG_l,   0,  6,  6, 12},
        {S_14SEG_m,   0,  6,  6, 13},
    },
    {
        {S_14SEG_a,   0,  7,  5,  1},
        {S_14SEG_b,   0,  7,  5,  5},
        {S_14SEG_c,   0,  7,  5,  9},
        {S_14SEG_d,   0,  7,  5, 14},
        {S_14SEG_e,   0,  7,  5, 10},
        {S_14SEG_f,   0,  7,  5,  6},
        {S_14SEG_g1,  0,  7,  5,  8},
        {S_14SEG_g2,  0,  7,  5,  7},
        {S_14SEG_h,   0,  7,  5,  2},
        {S_14SEG_i,   0,  7,  5,  3},
        {S_14SEG_j,   0,  7,  5,  4},
        {S_14SEG_k,   0,  7,  5, 11},
        {S_14SEG_l,   0,  7,  5, 12},
        {S_14SEG_m,   0,  7,  5, 13},
    },
    {
        {S_14SEG_a,   0,  8,  4,  1},
        {S_14SEG_b,   0,  8,  4,  5},
        {S_14SEG_c,   0,  8,  4,  9},
        {S_14SEG_d,   0,  8,  4, 14},
        {S_14SEG_e,   0,  8,  4, 10},
        {S_14SEG_f,   0,  8,  4,  6},
        {S_14SEG_g1,  0,  8,  4,  8},
        {S_14SEG_g2,  0,  8,  4,  7},
        {S_14SEG_h,   0,  8,  4,  2},
        {S_14SEG_i,   0,  8,  4,  3},
        {S_14SEG_j,   0,  8,  4,  4},
        {S_14SEG_k,   0,  8,  4, 11},
        {S_14SEG_l,   0,  8,  4, 12},
        {S_14SEG_m,   0,  8,  4, 13},
    },
    {
        {S_14SEG_a,   0,  9,  3,  1},
        {S_14SEG_b,   0,  9,  3,  5},
        {S_14SEG_c,   0,  9,  3,  9},
        {S_14SEG_d,   0,  9,  3, 14},
        {S_14SEG_e,   0,  9,  3, 10},
        {S_14SEG_f,   0,  9,  3,  6},
        {S_14SEG_g1,  0,  9,  3,  8},
        {S_14SEG_g2,  0,  9,  3,  7},
        {S_14SEG_h,   0,  9,  3,  2},
        {S_14SEG_i,   0,  9,  3,  3},
        {S_14SEG_j,   0,  9,  3,  4},
        {S_14SEG_k,   0,  9,  3, 11},
        {S_14SEG_l,   0,  9,  3, 12},
        {S_14SEG_m,   0,  9,  3, 13},
    },
    {
        {S_14SEG_a,   0, 10,  2,  1},
        {S_14SEG_b,   0, 10,  2,  5},
        {S_14SEG_c,   0, 10,  2,  9},
        {S_14SEG_d,   0, 10,  2, 14},
        {S_14SEG_e,   0, 10,  2, 10},
        {S_14SEG_f,   0, 10,  2,  6},
        {S_14SEG_g1,  0, 10,  2,  8},
        {S_14SEG_g2,  0, 10,  2,  7},
        {S_14SEG_h,   0, 10,  2,  2},
        {S_14SEG_i,   0, 10,  2,  3},
        {S_14SEG_j,   0, 10,  2,  4},
        {S_14SEG_k,   0, 10,  2, 11},
        {S_14SEG_l,   0, 10,  2, 12},
        {S_14SEG_m,   0, 10,  2, 13},
    },
    {
        {S_14SEG_a,   0, 11,  1,  1},
        {S_14SEG_b,   0, 11,  1,  5},
        {S_14SEG_c,   0, 11,  1,  9},
        {S_14SEG_d,   0, 11,  1, 14},
        {S_14SEG_e,   0, 11,  1, 10},
        {S_14SEG_f,   0, 11,  1,  6},
        {S_14SEG_g1,  0, 11,  1,  8},
        {S_14SEG_g2,  0, 11,  1,  7},
        {S_14SEG_h,   0, 11,  1,  2},
        {S_14SEG_i,   0, 11,  1,  3},
        {S_14SEG_j,   0, 11,  1,  4},
        {S_14SEG_k,   0, 11,  1, 11},
        {S_14SEG_l,   0, 11,  1, 12},
        {S_14SEG_m,   0, 11,  1, 13},
    },
    {{S_NONE}}
};

bool PanasonicDVDRV32Layout::getSegmentGroup14Seg(
    UINT8 row,
    UINT8 col,
    const SegmentGroup14Seg **p_segGroup,
    UINT8 *numEntries)
{
    if ((row > 0) || (col > 0))
    {
        return false;
    }

    *p_segGroup = s_segmentGroup14Seg;
    *numEntries = ARRAYSIZE(s_segmentGroup14Seg);

    return true;
}


/*
Symbols

1301 - DVD (red back)
1302 - PGM
1303 - A-
1304 - B
1305 - VIDEO (red back)
1306 - RND
1307 - repeat symbol
1308 - AUDIO (red back)
1309 - WMA (red back)
1310 - play symbol
1311 - CD (red back)
1312 - VR (red back)
1313 - MP3 (red back)
1314 - pause symbol

0215 - D.ENH
0315 - CINEMA
0415 - BASS
0515 - A.SRD
0615 - D.MIX
0715 - PG
0815 - D.N.R.
0915 - CHAP
1015 - TRACK
1115 - TITLE
1215 - GROUP

0216 - col 10 colon
0416 - col  8 colon
*/