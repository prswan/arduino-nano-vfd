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

    //
    // 7 segment display
    //
    S_7SEG_a,
    S_7SEG_b,
    S_7SEG_c,
    S_7SEG_d,
    S_7SEG_e,
    S_7SEG_f,
    S_7SEG_g,
    S_7SEG_DP, // Decimal Point

    //
    // 14 segment display additions
    //
    S_14SEG_g1, // Sony g
    S_14SEG_g2, // Sony m
    S_14SEG_h,  // SOny h
    S_14SEG_i,  // Sony j
    S_14SEG_j,  // Sony k
    S_14SEG_k,  // Sony r
    S_14SEG_l,  // Sony p
    S_14SEG_m,  // Sony n
    S_14SEG_DP, // Decimal Point

    //
    // 15 segment centre dot addition
    //
    S_15SEG_s,

    //
    // 16 segment display additions
    //
    S_16SEG_a1,
    S_16SEG_a2,
    S_16SEG_d1,
    S_16SEG_d2,

    // Character separators
    S_COLON,

    //
    // Bar graph
    //
    S_BAR_0,    // On some displays this is permanent on coupled with the associated scale graphics
    S_BAR_n,    // Pure segments

    S_END

} Segment;

#endif
