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
#include "PhilipsFC40Pinout.h"

//
// This is on a Universal VFD V1.00 driver board driven by 2 x SN75518 32-bit driver ICs.
// * The display is fitted solder side up lay flat against the PCB.
// NOTE: this is a 0.156" pitch display installed on V1.
// * V1 pins 31,30 (A36,A35) are cut on V3 pad and patched for Fil.
// * V1 pins 59,58 (A73,A72) are cut on V3 pad (unused "Internal Connect")
// * V1 pin  78 (F) is cut on V3 pad (duplicate 6G)
// * V1 pins 57,51,39 (A71,A62,A46) are cut on V3 pad (duplicate 2G)
// * V1 pin  66 (A82) is cut on V3 pad (duplicate 3G)
//
// See Universal VFD V1.10 Pinout.txt
//
// LSB=31, MSB=0 (physical pins 32 to 1). 31 is the first bit out and 0 the last bit out
//
// IC : Bit   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16  8  9 10 11 12 13 14 15 0  1  2  3  4  5  6  7
//      Byte  |           0         |  |         1          |  |          2         | |          3         |
//
// Pin Layout
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VFD Func :  F   F  6G  S1  S2  S3  6G  S4      5G  S6  S7  4G  S8  3G  S9 S10 S11 S12      3G  ic  ic  2G      S5   a   l   m  2G   p   k   o   n   j       i   h   d   e   c  2G   g   f   b     S13  2G  1G   F   F 
// ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VFD Pin  :  1   2   3   4   5   6   7   8      10  11  12  13  14  15  16  17  18  19      21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51 
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// V1 Pin   : 80  79  78  77  76  75  74  73      71  70  69  68  67      65  64  63  62      60  59  58  57  56  55  54  53  52      50  49  48  47  46  45  44  43  42  41  40      38  37  36  35  34  33  32   F   F 
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// A Func.  :  F   F      96  94  93  92  91  89  88  87  86  84  83      81  79  78  77  76  74              68  67  66  65  63      61  60  58  57  56  55  53  52  51  50  47      45  44  42  41  40  39  37 
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// U3 OUT   :             16  15  18  14  19  20  12  21  11  10  23   9  24  25   7  26   6   5               2  31   1  32
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// U2 OUT   :                                                                                                                 17      18  14  13  20  12  21  22  10  23   9  25      26   6   5  28   4  29  30
//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {49, 32 + (30-1)}, // 1GA
    {48, 32 + (29-1)}, // 2GA
    {21, 64 + ( 5-1)}, // 3GA
    {13, 64 + (10-1)}, // 4GA
    {10, 64 + (12-1)}, // 5GA
    { 7, 64 + (14-1)}, // 6GA
};

static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    // 1st Logical Segment Group, S1 to S13
    { 4, 64 + (16-1)}, // S1
    { 5, 64 + (15-1)}, // S2
    { 6, 64 + (18-1)}, // S3
    { 8, 64 + (19-1)}, // S4
    {26, 64 + (31-1)}, // S5
    {11, 64 + (21-1)}, // S6
    {12, 64 + (11-1)}, // S7
    {14, 64 + (23-1)}, // S8
    {16, 64 + (24-1)}, // S9
    {17, 64 + (25-1)}, // S10
    {18, 64 + ( 7-1)}, // S11
    {19, 64 + (26-1)}, // S12
    {47, 32 + ( 4-1)}, // S13
    // 2nd Logical Segment Letter Group S14+
    {27, 64 + ( 1-1)}, // a - S14
    {45, 32 + ( 5-1)}, // b - S15
    {41, 32 + (25-1)}, // c - S16
    {39, 32 + (23-1)}, // d - S17
    {40, 32 + ( 9-1)}, // e - S18
    {44, 32 + ( 6-1)}, // f - S19
    {43, 32 + (26-1)}, // g - S20
    {38, 32 + (10-1)}, // h - S21
    {37, 32 + (22-1)}, // i - S22
    {35, 32 + (12-1)}, // j - S23
    {32, 32 + (14-1)}, // k - S24
    {28, 64 + (32-1)}, // l - S25
    {29, 32 + (17-1)}, // m - S26
    {34, 32 + (20-1)}, // n - S27
    {33, 32 + (13-1)}, // o - S28
    {31, 32 + (18-1)}  // p - S29
};

//
// The resulting registerMask for the main display.
// The driver IC chain is 96-bits or 12 bytes.
// The last 64-bits are used for this display that are the first 64-bits shifted in.
//
static const UINT8 s_registerMask[] PROGMEM =
{
    0xFF,0xFF,0xFF,0xFF, 
    0xFF,0xFF,0xFF,0xFF, 
    0x00,0x00,0x00,0x00
};

void PhilipsFC40Pinout::getScanConfig(
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

void PhilipsFC40Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void PhilipsFC40Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};

