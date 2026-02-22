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
#ifndef Segments_h
#define Segments_h

//
// Segment identification
//
typedef enum {
    S_NONE = 0,

    // 7 segment display
    S_7SEG_a,
    S_7SEG_b,
    S_7SEG_c,
    S_7SEG_d,
    S_7SEG_e,
    S_7SEG_f,
    S_7SEG_g,
    S_7SEG_dp, // Decimal Point

    // 14 segment display additions
    S_14SEG_a,
    S_14SEG_b,
    S_14SEG_c,
    S_14SEG_d,
    S_14SEG_e,
    S_14SEG_f,
    S_14SEG_g,
    S_14SEG_g1, // Sony g
    S_14SEG_g2, // Sony m
    S_14SEG_h,  // SOny h
    S_14SEG_i,  // Sony j
    S_14SEG_j,  // Sony k
    S_14SEG_k,  // Sony r
    S_14SEG_l,  // Sony p
    S_14SEG_m,  // Sony n
    S_14SEG_dp, // Decimal Point

    // 14 segment centre dot addition
    S_14SEG_s,

    // 16 segment display additions
    S_16SEG_a1,
    S_16SEG_a2,
    S_16SEG_d1,
    S_16SEG_d2,

    // Character separators
    S_COLON,

    // Bar graph
    S_BAR_0,  // On some displays this is permanent on coupled with the associated scale graphics
    S_BAR_1,
    S_BAR_2,
    S_BAR_3,
    S_BAR_4,
    S_BAR_5,
    S_BAR_6,
    S_BAR_7,
    S_BAR_8,
    S_BAR_9,
    S_BAR_10,
    S_BAR_11,
    S_BAR_12,
    S_BAR_13,
    S_BAR_14,
    S_BAR_15,

    // Begin Symbols
    S_SYM_BEGIN,

    S_SYM_PLAY_FORWARD,
    S_SYM_PLAY_REVERSE,
    S_SYM_PAUSE,
    S_SYM_TEXT_PLAY,
    S_SYM_TEXT_REC,

    S_SYM_END,
    // End Symbols

    //
    S_END

} Segment;

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

#endif
