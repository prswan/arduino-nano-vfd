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
#include "PanasonicSABT330Pinout.h"

//
// This is on a Universal VFD V1.10 driver board driven by 1 x SN75518 32-bit driver IC.
// * The driver IC is the 1st IC in the serial chain.
// * This is a shared PCB with the Toshiba HD-A2 on the 2nd driver IC in the chain.
// * The display is fitted solder side up lay flat against the PCB.
// * V2 pins 31 (A28), 32 (A29) are cut trace isolated for Fil.
//
// See Universal VFD V1.10 Pinout.txt
//
// LSB=31, MSB=0 (physical pins 32 to 1). 31 is the first bit out and 0 the last bit out
//
// IC : Bit   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16  8  9 10 11 12 13 14 15 0  1  2  3  4  5  6  7
//      Byte  |           0         |  |         1          |  |          2         | |          3         |
//
// Pin Layout
// -------------------------------------------------------------------------------------------------------------------------------------------
// VFD Func :   F   F      S1  S2  S3  S4  S5  S6  S7  S8  S9 S10 S11 S12 S13 S14 S15 S16  nc  G1  G2  G3  G4  G5  G6  G7  G8  G9       F   F  
// -------------------------------------------------------------------------------------------------------------------------------------------
// VFD Pin  :   1   2       4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29      31  32
//--------------------------------------------------------------------------------------------------------------------------------------------
// V2 Pin   :  32  31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1    
//--------------------------------------------------------------------------------------------------------------------------------------------
// A Func.  :   F   F      26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1       F   F  
//--------------------------------------------------------------------------------------------------------------------------------------------
// U1 OUT   :              13  20  12  21  11  22  10  23   9  24   8  25   7  26   6  27   5  28   4  29   3  30   2  31   1  32
//--------------------------------------------------------------------------------------------------------------------------------------------
//
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {21, (28-1)}, // G1
    {22, ( 4-1)}, // G2
    {23, (29-1)}, // G3
    {24, ( 3-1)}, // G4
    {27, (30-1)}, // G5
    {26, ( 2-1)}, // G6
    {27, (31-1)}, // G7
    {28, ( 1-1)}, // G8
    {29, (32-1)}  // G9
};

static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    { 4, (13-1)}, // S1
    { 5, (20-1)}, // S2
    { 6, (12-1)}, // S3
    { 7, (21-1)}, // S4
    { 8, (11-1)}, // S5
    { 9, (22-1)}, // S6
    {10, (10-1)}, // S7
    {11, (23-1)}, // S8
    {12, ( 9-1)}, // S9
    {13, (24-1)}, // S10
    {14, ( 8-1)}, // S11
    {15, (25-1)}, // S12
    {16, ( 7-1)}, // S13
    {17, (26-1)}, // S14
    {18, ( 6-1)}, // S15
    {19, (27-1)}  // S16
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

void PanasonicSABT330Pinout::getProperties(
    PinoutProperties *pinoutProperties)
{
    memset(pinoutProperties, 0x00, sizeof(*pinoutProperties));

    pinoutProperties->driverType        = DriverTypeSN75518;
    pinoutProperties->spiClockFrequency = 2;
    pinoutProperties->registerLenInBits = 64;
    pinoutProperties->p_registerMask    = s_registerMask;
    pinoutProperties->numGrids          = ARRAYSIZE(s_pinMapGrid) - 1;
};

void PanasonicSABT330Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void PanasonicSABT330Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
