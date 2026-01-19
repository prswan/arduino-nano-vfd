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
#include "SonyTCWR775Layout.h"

/* TODO

  * Additon of the remaining single indicator elements
    - There needs to be a class that handles these, to look up elements
      and calls Display.

  * Definition & additon of the SegmentGroupBar
    - Like 7Seg, and array of instance definitions for row/col.
    - "Bar" class to activate them.
    - Needs a way to be indepedent of number of segments in the bar.
      - Ideas
        - As a bar, percentage of max.
        - Special effects
          - Night Rider "Kit" scan?
          - Single bar counter
          - "scale" bar 0  on or off.
*/

//
// 8x 7-segment displays in two groups of 4
// These were documented in the service manual.
//
static const SegmentGroup7Seg s_segmentGroup7Seg[] PROGMEM =
    {
        //      seg,   row ,col, pinG, pinS
        {
            {S_7SEG_a, 0, 0, 5, 1},
            {S_7SEG_b, 0, 0, 5, 2},
            {S_7SEG_c, 0, 0, 5, 3},
            {S_7SEG_d, 0, 0, 5, 4},
            {S_7SEG_e, 0, 0, 5, 5},
            {S_7SEG_f, 0, 0, 5, 6},
            {S_7SEG_g, 0, 0, 5, 7}},
        {
            {S_7SEG_a, 0, 1, 5, 9},
            {S_7SEG_b, 0, 1, 5, 10},
            {S_7SEG_c, 0, 1, 5, 11},
            {S_7SEG_d, 0, 1, 5, 12},
            {S_7SEG_e, 0, 1, 5, 13},
            {S_7SEG_f, 0, 1, 5, 14},
            {S_7SEG_g, 0, 1, 5, 15}
        },
        {
            {S_7SEG_a, 0, 2, 4, 1},
            {S_7SEG_b, 0, 2, 4, 2},
            {S_7SEG_c, 0, 2, 4, 3},
            {S_7SEG_d, 0, 2, 4, 4},
            {S_7SEG_e, 0, 2, 4, 5},
            {S_7SEG_f, 0, 2, 4, 6},
            {S_7SEG_g, 0, 2, 4, 7},
        },
        {
            {S_7SEG_a, 0, 3, 4, 9},
            {S_7SEG_b, 0, 3, 4, 10},
            {S_7SEG_c, 0, 3, 4, 11},
            {S_7SEG_d, 0, 3, 4, 12},
            {S_7SEG_e, 0, 3, 4, 13},
            {S_7SEG_f, 0, 3, 4, 14},
            {S_7SEG_g, 0, 3, 4, 15},
        },
        {
            {S_7SEG_a, 0, 4, 3, 1},
            {S_7SEG_b, 0, 4, 3, 2},
            {S_7SEG_c, 0, 4, 3, 3},
            {S_7SEG_d, 0, 4, 3, 4},
            {S_7SEG_e, 0, 4, 3, 5},
            {S_7SEG_f, 0, 4, 3, 6},
            {S_7SEG_g, 0, 4, 3, 7},
        },
        {
            {S_7SEG_a, 0, 5, 3, 9},
            {S_7SEG_b, 0, 5, 3, 10},
            {S_7SEG_c, 0, 5, 3, 11},
            {S_7SEG_d, 0, 5, 3, 12},
            {S_7SEG_e, 0, 5, 3, 13},
            {S_7SEG_f, 0, 5, 3, 14},
            {S_7SEG_g, 0, 5, 3, 15},
        },
        {
            {S_7SEG_a, 0, 6, 2, 1},
            {S_7SEG_b, 0, 6, 2, 2},
            {S_7SEG_c, 0, 6, 2, 3},
            {S_7SEG_d, 0, 6, 2, 4},
            {S_7SEG_e, 0, 6, 2, 5},
            {S_7SEG_f, 0, 6, 2, 6},
            {S_7SEG_g, 0, 6, 2, 7},
        },
        {
            {S_7SEG_a, 0, 7, 2, 9},
            {S_7SEG_b, 0, 7, 2, 10},
            {S_7SEG_c, 0, 7, 2, 11},
            {S_7SEG_d, 0, 7, 2, 12},
            {S_7SEG_e, 0, 7, 2, 13},
            {S_7SEG_f, 0, 7, 2, 14},
            {S_7SEG_g, 0, 7, 2, 15},
        },
        {{S_NONE}}};

bool SonyTCWR775Layout::getSegmentGroup7Seg(
    UINT8 row,
    const SegmentGroup7Seg **p_segGroup,
    UINT8 *numEntries)
{
    if (row == 0)
    {
        *p_segGroup = s_segmentGroup7Seg;
        *numEntries = ARRAYSIZE(s_segmentGroup7Seg);
        return true;
    }

    return false;
}

/*
Right side symbols
G1 S1 - "DOLBY NR" S_TEXT_DOLBY_NR
G1 S2 - white square 'B' S_SYMBOL_WHITE_SQUARE_B
G1 S3 - red left arrow S_SYMBOL_RED_LEFT_ARROW
G1 S4 - "PLAY" S_TEXT_PLAY
G1 S5 - red right arrow
G1 S6 - white square 'C' S_SYMBOL_WHITE_SQUARE_C
G1 S7 - "MEMORY"
G1 S8 - red pause symbol S_SYMBOL_RED_PAUSE
G1 S9 - red "REC"
G1 S10+ - n/a

Left side symbols
G6 S1 - "DOLBY NR"
G6 S2 - white square 'B'
G6 S3 - red left arrow
G6 S4 - "PLAY"
G6 S5 - red right arrow
G6 S6 - white square 'C'
G6 S7 - "MEMORY"
G6 S8 - red pause symbol
G6 S9 - red "REC"
G6 S10 - FADE and box
G6 S11 - red right arrow in fade box
G6 S12 - "BLANK SKIP"
G6 S13 - "AUTO PAUSE"
G6 S14 - red left arrow in fade box
G6 S15+ n/c

Top:
G7 S1 - Top bar L, bar 1 and top scale
G7 S2 - 2
G7 S3 - 5
G7 S4 - 7
G7 S5 - 6
G7 S6 - 3
G7 S7 - 4
G7 S8 - 8
G7 S9 - 9
G7 S10 - 10
G7 S11 - 13
G7 S12 - 15
G7 S13 - 14
G7 S14 - 11
G7 S15 - 12
G7 S16 - 16
G7 S17+

Bottom G8
G8 S1 - bottom bar R, bar 1, dolby double D symbol
G8 S2 - S16 same as above
G8 S17 - Red dot bar 4
G8 S18 - Red dot bar 1 thru 3
G8 S19+ n/c

*/
