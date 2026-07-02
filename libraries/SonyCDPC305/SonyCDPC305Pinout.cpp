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
#include "SonyCDPC305Pinout.h"

//
// This is on a Universal VFD V1.10 driver board driven by 1 x SN75518 32-bit driver IC.
// * The driver IC is the 1st IC in the serial chain.
// * This is a shared PCB with the Philips FC-40 on the 2nd & 3rd driver ICs in the chain.
// * The display is fitted solder side up lay flat against the PCB.
// * To accomodate the FC-40 nipple, the display overhangs the PCB by 1 pin with 1 FIL pin cut.
// * V1 pins 2 (FIL), 3 (FIL) are cut trace isolated and patched to V2 pins 5 (A2), 10 (A7)  
// * V1 pins 20 (A21), 21 (A23) are cut trace isolated and patched to FIL
//
// See Universal VFD V1.10 Pinout.txt
//
// LSB=31, MSB=0 (physical pins 32 to 1). 31 is the first bit out and 0 the last bit out
//
// IC : Bit   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16  8  9 10 11 12 13 14 15 0  1  2  3  4  5  6  7
//      Byte  |           0         |  |         1          |  |          2         | |          3         |
//
// Pin Layout
// --------------------------------------------------------------------------------------------------
// VFD Func :  F   F   a   b  6G   c   d   e  5G  f   g   4G   h   i  3G   j  2G   k  1G   l   F   F
// --------------------------------------------------------------------------------------------------
// VFD Pin  :  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22
//---------------------------------------------------------------------------------------------------
// V1 Pin   : 31  20  19  18  17  16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1  nc
//---------------------------------------------------------------------------------------------------
// A Func.  :         20  19  18  16  15  14  13  11  10   9   8   6   5   4   3   1   7   2   F  
//---------------------------------------------------------------------------------------------------
// U1 OUT   :         10  23   9   8  25   7  26  27   5  28   4   3  30   2  31  32  29   1
//---------------------------------------------------------------------------------------------------
//
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {19, (29-1)}, // G1
    {17, (31-1)}, // G2
    {15, (30-1)}, // G3
    {12, (28-1)}, // G4
    { 9, (26-1)}, // G5
    { 5, ( 9-1)}, // G6
};

// The service manual layout diagram showed the 7-seg pinout but not the symbols.
static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    { 3, (10-1)}, // S1  - a
    { 4, (23-1)}, // S2  - b
    { 6, ( 8-1)}, // S3  - c
    { 7, (25-1)}, // S4  - d
    { 8, ( 7-1)}, // S5  - e
    {10, (27-1)}, // S6  - f
    {11, ( 5-1)}, // S7  - g
    {13, ( 4-1)}, // S8  - h
    {14, ( 3-1)}, // S9  - i
    {16, ( 2-1)}, // S10 - j
    {18, (32-1)}, // S11 - k
    {20, ( 1-1)}, // S12 - l
};

//
// The resulting registerMask for this display.
// The driver IC chain is 96-bits or 12 bytes.
// The first 32-bits are used for this display that are the last 32-bits shifted in.
//
static const UINT8 s_registerMask[] PROGMEM =
{
    0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,
    0xFF,0xFF,0xFF,0xFF
};

void SonyCDPC305Pinout::getScanConfig(
    DriverType *driverType,
    const UINT8 **registerMask,
    UINT8 *registerLenInBits,
    UINT8 *numGrids)
{
    *driverType = DriverTypeSN75518;
    *registerMask = s_registerMask;
    *registerLenInBits = 96;
    *numGrids = ARRAYSIZE(s_pinMapGrid) - 1;
};

void SonyCDPC305Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void SonyCDPC305Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
