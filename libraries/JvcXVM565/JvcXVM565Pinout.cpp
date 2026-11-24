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
#include "JvcXVM565Pinout.h"

//
// This is on a Universal VFD V1.10 driver board driven by 1 x SN75518 32-bit driver IC.
// * The driver IC is the 2nd IC in the serial chain.
// * This is a shared PCB with the TEAC PD-D1200 on the 1st driver IC in the chain.
// * The display is fitted solder side up lay flat against the PCB.
// * V2 pins 50 (A47), pin 49 (A46) are cut trace isolated for Fil.
// * Note that the service manual pin numbers do not include the 4 missing pins next to the filament pins!
// * SDIN bridged to SDOUT on unused U2.
//
// See Universal VFD V1.10 Pinout.txt
//
// LSB=31, MSB=0 (physical pins 32 to 1). 31 is the first bit out and 0 the last bit out
//
// IC : Bit   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16  8  9 10 11 12 13 14 15 0  1  2  3  4  5  6  7
//      Byte  |           0         |  |         1          |  |          2         | |          3         |
//
// Pin Layout
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VFD Func    :   F   F          S1  S2  S3  S4  S5  S6  S7  S8  S9 S10 S11 S12 S13 S14  nc  nc  nc  nc  nc  nc  nc  nc  nc  G1  G2  G3  G4  G5  G6  G7           F   F                 
// ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VFD Pin     :   1   2           3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32          33  34
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
// V2 Pin      : 102 101 100  99  98  97  96  95  94  93  92  91  90  89  88  87  86  85  84  83  82  81  80  79  78  77  76  75  74  73  72  71  70  69  68  67  66  65
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
// A Func.     :   F   F          95  94  93  92  91  90  89  88  87  86  85  84  83  82  81  80  79  78  77  76  75  74  73  72  71  70  69  68  67  66          63  62
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
// U3 OUT      :                  17  15  18  14  19  13  20  12  21  11  22  10  23   9  24   8  25   7  26   6  27   5  28   4  29   3  30   2  31   1
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {26, 32 + ( 4-1)}, // G1
    {27, 32 + (29-1)}, // G2
    {28, 32 + ( 3-1)}, // G3
    {29, 32 + (30-1)}, // G4
    {30, 32 + ( 2-1)}, // G5
    {31, 32 + (31-1)}, // G6
    {32, 32 + ( 1-1)}  // G7
};

static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    { 3, 32 + (17-1)}, // S1
    { 4, 32 + (15-1)}, // S2
    { 5, 32 + (18-1)}, // S3
    { 6, 32 + (14-1)}, // S4
    { 7, 32 + (19-1)}, // S5
    { 8, 32 + (13-1)}, // S6
    { 9, 32 + (20-1)}, // S7
    {10, 32 + (12-1)}, // S8
    {11, 32 + (21-1)}, // S9
    {12, 32 + (11-1)}, // S10
    {13, 32 + (22-1)}, // S11
    {14, 32 + (10-1)}, // S12
    {15, 32 + (23-1)}, // S13
    {16, 32 + ( 9-1)}  // S14
};

//
// The resulting registerMask for this display.
// The driver IC chain is 64-bits or 8 bytes.
// The second 32-bits are used for this display that are the first shifted in.
//
static const UINT8 s_registerMask[] PROGMEM =
{
    0xFF,0xFF,0xFF,0xFF, 0x00,0x00,0x00,0x00 
};

void JvcXVM565Pinout::getProperties(
    PinoutProperties *pinoutProperties)
{
    memset(pinoutProperties, 0x00, sizeof(*pinoutProperties));

    pinoutProperties->driverType        = DriverTypeSN75518;
    pinoutProperties->spiClockFrequency = 2;
    pinoutProperties->registerLenInBits = 64;
    pinoutProperties->p_registerMask    = s_registerMask;
    pinoutProperties->numGrids          = ARRAYSIZE(s_pinMapGrid) - 1;
};

void JvcXVM565Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void JvcXVM565Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
