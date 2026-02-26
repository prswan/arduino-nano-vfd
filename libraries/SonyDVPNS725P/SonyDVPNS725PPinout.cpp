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
// * The driver IC is the 1st IC in the serial chain.
// * This is a shared PCB with the Panasonic DVD-RV32 on the 2nd driver IC in the chain.
// * The display is fitted solder side up lay flat against the PCB.
// * V2 pins 35 (A62), 36 (A63), 37 (A64) are cut trace isolated for Fil1 & resistor.
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
// V2 Pin   : 38  37  36  35  34  33  32  31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10   9   8   7  6   5   4   3   2   1    
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
// A Func.  :  F   F          31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10   9   8   7   6   5   4  3   2           F   F  
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
// U1 OUT   :                 17  15  18  14  19  13  20  12  21  11  22  10  23   9  24   8  25   7  26   6  27   5  28   4  29   3  30   2  31  1
//-------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {11, (20-1)}, // G1
    {10, (13-1)}, // G2
    { 9, (19-1)}, // G3
    { 8, (14-1)}, // G4
    { 7, (18-1)}, // G5
    { 6, (15-1)}, // G6
    { 5, (17-1)}  // G7
};

//
// The service manual layout table lists 20 pins P1 to P20 whereas the pinout
// defines P1 to P23. The LayoutFinder app identified the first three segment
// pins as unused, so layout P1 to P20 maps to pinout P4 to P23
//
static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {12, (12-1)}, // S1
    {13, (21-1)}, // S2
    {14, (11-1)}, // S3
    {15, (22-1)}, // S4
    {16, (10-1)}, // S5  - a
    {17, (23-1)}, // S6  - h
    {18, ( 9-1)}, // S7  - j
    {19, (24-1)}, // S8  - k
    {20, ( 8-1)}, // S9  - b
    {21, (25-1)}, // S10 - f
    {22, ( 7-1)}, // S11 - m
    {23, (26-1)}, // S12 - s
    {24, ( 6-1)}, // S13 - g
    {25, (27-1)}, // S14 - e
    {26, ( 5-1)}, // S15 - n
    {27, (28-1)}, // S16 - p
    {28, ( 4-1)}, // S17 - r
    {29, (29-1)}, // S18 - c
    {30, ( 3-1)}, // S19 - d
    {31, (30-1)}, // S20
    {32, ( 2-1)}, // S21
    {33, (31-1)}, // S22
    {34, ( 1-1)}  // S23 - Dp
};

//
// The resulting registerMask for this display.
// The driver IC chain is 64-bits or 8 bytes.
// The first 32-bits are used for this display that are the last 32-bits shifted in.
//
static const UINT8 s_registerMask[] PROGMEM =
{
    0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF
};

void SonyDVPNS725PPinout::getScanConfig(
    const UINT8 **registerMask,
    UINT8 *registerLenInBits,
    UINT8 *numGrids)
{
    *registerMask = s_registerMask;
    *registerLenInBits = 64;
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
