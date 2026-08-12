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
#include "KenwoodKRV77REQPinout.h"

//
// EQ Display, see KenwoodKRV77RPinout for the overall information.
//
// See Universal VFD V1.00 Pinout.txt
//
// LSB=31, MSB=0 (physical pins 32 to 1). 31 is the first bit out and 0 the last bit out
//
// IC : Bit   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16  8  9 10 11 12 13 14 15 0  1  2  3  4  5  6  7
//      Byte  |           0         |  |         1          |  |          2         | |          3         |
//
// Pin Layout
// -----------...---------------------------------------------------------------------------------------------------------------
// VFD Func :     FD     S20  B1  B2  B3  B4  B5  B6  B7  B8  B9 B10 B11 B12 B13 1GB  2GB 3GB 4GB 5GB 6GB 7GB 8GB SCB      F   F
// -----------...---------------------------------------------------------------------------------------------------------------
// VFD Pin  :     49      51  52  53  54  55  56  57  58  59  60  61  62  63  64  65  66  67  68  69  70  71  72  73      75  76
//------------...---------------------------------------------------------------------------------------------------------------
// V1 Pin   :     28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1
//------------...---------------------------------------------------------------------------------------------------------------
// A Func.  :             30  29  26  25  24  23  21  20  19  18  16  15  14  13  11  10   9   8   6   5   4   3   1       F   F
//------------...---------------------------------------------------------------------------------------------------------------
// U3 OUT   : 
//------------...---------------------------------------------------------------------------------------------------------------
// U2 OUT   : 
//------------...---------------------------------------------------------------------------------------------------------------
// U1 OUT   :             15  18  13  20  12  21  22  10  23   9   8  25   7  26  27   5  28   4   3  30   2  31  32
//------------...---------------------------------------------------------------------------------------------------------------

// EQ display grid pin map
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {65, (27-1)}, // 1GB
    {66, ( 5-1)}, // 2GB
    {67, (28-1)}, // 3GB
    {68, ( 4-1)}, // 4GB
    {69, ( 3-1)}, // 5GB
    {70, (30-1)}, // 6GB
    {71, ( 2-1)}, // 7GB
    {72, (31-1)}  // 8GB
};

// EQ display segment pin map 
static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {52, (18-1)}, // B1
    {53, (13-1)}, // B2
    {54, (20-1)}, // B3
    {55, (12-1)}, // B4
    {56, (21-1)}, // B5
    {57, (22-1)}, // B6
    {58, (10-1)}, // B7
    {59, (23-1)}, // B8
    {60, ( 9-1)}, // B9
    {61, ( 8-1)}, // B10
    {62, (25-1)}, // B11
    {63, ( 7-1)}, // B12
    {64, (26-1)}, // B13
    {73, (32-1)}  // SCB (scales)
};

//
// The resulting registerMask for the EQ display.
// The driver IC chain is 96-bits or 12 bytes.
// The first 31-bits are used for the EQ display that are the last 31-bits shifted in.
//
static const UINT8 s_registerMask[] PROGMEM =
{
    0x00,0x00,0x00,0x00, 
    0x00,0x00,0x00,0x00, 
    0xFF,0xFF,0xBF,0xFF
};

void KenwoodKRV77REQPinout::getScanConfig(
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

void KenwoodKRV77REQPinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void KenwoodKRV77REQPinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
