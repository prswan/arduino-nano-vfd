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
#include "TeacPDD1200Pinout.h"

//
// This is on a Universal VFD V1.10 driver board driven by 1 x A5818 32-bit driver IC.
// * The driver IC is the 1st IC in the serial chain.
// * The display is fitted solder side up lay flat against the PCB.
// NOTE: this is a 0.156" pitch display installed on V1, but wire strapped on the 2mm matrix.
// * V1 pins 41 (A50) & 42 (A51) are cut trace isolated for Fil2.
// * V2 pins 4,5,8 (A1,A2,A5) are wire strapped to V2 pins 38,39,40. 
//
// See Universal VFD V1.00 Pinout.txt
//
// No freely available/downloadable service manual was found.
// * Number assignment arbitrary from LayoutFinder.
//
// LSB=31, MSB=0 (physical pins 32 to 1). 31 is the first bit out and 0 the last bit out
//
// IC : Bit   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16  8  9 10 11 12 13 14 15 0  1  2  3  4  5  6  7
//      Byte  |           0         |  |         1          |  |          2         | |          3         |
//
// Pin Layout
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VFD Func :  F   F                                  G1  S1  G2      S2  G3  S3  S4  G4      G5                  G6  S5  G7  S6  G8      G9  S7  S8  S9     S10 S11           F   F  
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VFD Pin  :  1   2                                  11  12  13      15  16  17  18  19      21                  26  27  28  29  30      32  33  34  35      37  38          41  42
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// V1 Pin   : 42  41  40  39  38  37  36  35  34  33  32  31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1    
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// A Func.  :  F   F                                   5   2   1  34  32  31  30  29  26  25  24  23  21  20  19  18  16  15  14  13  11  10   9   8   6   5   4   3   1   F   F   F  
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// U1 OUT   :                                         30   1  32      16  17  15  18  13  20  12  21  22  10  23   9   8  25   7  26  27   5  28   4   3  30   2  31  32
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {11, (30-1)}, // G1
    {13, (32-1)}, // G2
    {16, (17-1)}, // G3
    {19, (13-1)}, // G4
    {21, (12-1)}, // G5
    {26, ( 9-1)}, // G6
    {28, (25-1)}, // G7
    {30, (26-1)}, // G8
    {32, ( 5-1)}  // G9
};

//
// TBD.
//
static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {12, ( 1-1)}, // S1
    {15, (16-1)}, // S2
    {17, (15-1)}, // S3
    {18, (18-1)}, // S4
    {27, ( 8-1)}, // S5
    {29, ( 7-1)}, // S6
    {33, (28-1)}, // S7
    {34, ( 4-1)}, // S8
    {35, ( 3-1)}, // S9
    {37, ( 2-1)}, // S10
    {38, (31-1)}  // S11
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

void TeacPDD1200Pinout::getScanConfig(
    const UINT8 **registerMask,
    UINT8 *registerLenInBits,
    UINT8 *numGrids)
{
    *registerMask = s_registerMask;
    *registerLenInBits = 64;
    *numGrids = ARRAYSIZE(s_pinMapGrid) - 1;
};

void TeacPDD1200Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void TeacPDD1200Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
