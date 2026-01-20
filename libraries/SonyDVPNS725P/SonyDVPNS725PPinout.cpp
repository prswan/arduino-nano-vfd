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
#include "SonyDVPNS725PPinout.h"

//
// This is on a Universal VFD V1.00 driver board driven by 1 x A5818 32-bit driver IC.
// * The display is fitted solder side up lay flat against the PCB.
// * V2 pin 65 (A62) & pin 66 (A63) are cut trace isolated and bridged to Fil1
//
// See Universal VFD V1.00 Pinout.txt
//
// LSB=31, MSB=0 (physical pins 32 to 1). 31 is the first bit out and 0 the last bit out
//
// IC : Bit   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16  8  9 10 11 12 13 14 15 0  1  2  3  4  5  6  7
//      Byte  |           0         |  |         1          |  |          2         | |          3         |
//
// Pin Layout
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VFD Func :  F   F          G7  G6  G5  G4  G3  G2  G1  S1  S2  S3  S4  S5  S6  S7  S8  S9 S10 S11 S12 S13 S14 S15 S16 S17 S18 S19 S20 S21 S22 S23           F   F  
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VFD Pin  :  1   2           5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34          37  38
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
// V2 Pin   : 65  66  67  68  69  70  71  72  73  74  75  76  77  78  79  80  81  82  83  84  85  86  87  88  89  90  91  92  93  94  95  96  97  98  99 100 101 102    
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
// A Func.  :  F   F          66  67  68  69  70  71  72  73  74  75  76  77  78  79  80  81  82  83  84  85  86  87  88  89  90  91  92  93  94  95           F   F  
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
// U3 OUT   :                  1  31   2  30   3  29   4  28   5  27   6  26   7  25   8  24   9  23  10  22  11  21  12  20  13  19  14  18  15  17
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
static const PinMap s_pinMapGrid[] PROGMEM =
    {
        {0, 0},
        // pin, bit (OUT-1)
        {11,  3}, // G1
        {10, 30}, // G2
        { 9,  2}, // G3
        { 8, 29}, // G4
        { 7,  1}, // G5
        { 6, 30}, // G6
        { 5,  0}, // G7
};

static const PinMap s_pinMapSegment[] PROGMEM =
    {
        {0, 0},
        // pin, bit (OUT-1)
        {12, 27}, // S1
        {13,  4}, // S2  - a
        {14, 26}, // S3  - h
        {15,  5}, // S4  - j
        {16, 25}, // S5  - k
        {17,  6}, // S6  - b
        {18, 24}, // S7  - f
        {19,  7}, // S8  - m
        {20, 23}, // S9  - s
        {21,  8}, // S10 - g
        {22, 22}, // S11 - e
        {23,  9}, // S12 - n
        {24, 21}, // S13 - p
        {25, 10}, // S14 - r
        {26, 20}, // S15 - c
        {27, 11}, // S16 - d
        {28, 19}, // S17
        {29, 12}, // S18
        {30, 18}, // S19
        {31, 13}, // S20 - Dp
        {32, 17}, // S21
        {33, 14}, // S22
        {34, 16}  // S23
};

void SonyDVPNS725PPinout::getScanConfig(
    UINT8 *registerLenInBits,
    UINT8 *numGrids)
{
    *registerLenInBits = 32;
    *numGrids = ARRAYSIZE(s_pinMapGrid) - 1;
};

void SonyDVPNS725PPinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void SonyDVPNS725PPinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
