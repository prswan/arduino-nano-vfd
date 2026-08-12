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
#include "KenwoodKRV77RPinout.h"

//
// This is on a Universal VFD V1.00 driver board driven by 3 x A5818 32-bit driver ICs.
// * The display is fitted solder side up lay flat against the PCB.
// NOTE: this is a 0.156" pitch display installed on V1.
// * V1 pins 28,75,76 (A32,A93,A94) are cut on the V3 pad grid for FD and Fil.
//
// This is a long 214mm wide display comprising two separate displays:
// 1) Main display on the right (Grids 1GA to 9GA, Segments S1 to S20 and a to p. total 36 segments)
// 2) EQ display on the left (Grids 1GB to 8GB, Segments B1 to B13 and SCB)
//
// There are 66 driver pins total. For everything it needs all 3 drivers, however
// if S2 "[1 - 10]"" and S3 "[11 - 20]" are skipped, 64 driver pins would be possible with
// a lot of cross wiring. I didn't do that here and went with the simple 3 driver option.
//
// The service manual shows the following tied lines:
// - S5 & S19 ("DELAY" and Video Monitor "3")
// - S11 and o ("TUNED" and 7-seg -)
// I don't think there is any particular meaning, suspect just to fit in the available drive pins. 
//
// VFD Pin 49 "FD" appears to go to a metal bar between the two halves supporting the filament wires.
// In the service manual it's connected via 10K to +5V that translates to +Vbb on the Universal 
// VFD positive voltage drive board.
//
// See Universal VFD V1.00 Pinout.txt
//
// LSB=31, MSB=0 (physical pins 32 to 1). 31 is the first bit out and 0 the last bit out
//
// IC : Bit   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16  8  9 10 11 12 13 14 15 0  1  2  3  4  5  6  7
//      Byte  |           0         |  |         1          |  |          2         | |          3         |
//
// Pin Layout
// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VFD Func :  F   F       a   b   c 1GA 2GA   d   e   f   g   h   i   j   k   l   m   n   o   p 3GA 4GA  S1  S2  S3 5GA 6GA  S4  S5  S6 7GA 8GA  S7  S8  S9 S10  S11 S12 9GA S13 S14 S15 S16 S17 S18 S19     FD     S20  B1  B2  B3  B4  B5  B6  B7  B8  B9 B10 B11 B12 B13 1GB  2GB 3GB 4GB 5GB 6GB 7GB 8GB SCB      F   F
// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VFD Pin  :  1   2       4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47      49      51  52  53  54  55  56  57  58  59  60  61  62  63  64  65  66  67  68  69  70  71  72  73      75  76
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// V1 Pin   : 76  75  74  73  72  71  70  69  68  67  66  65  64  63  62  61  60  59  58  57  56  55  54  53  52  51  50  49  48  47  46  45  44  43  42  41  40  39  38  37  36  35  34  33  32  31  30  29  28  27  26  25  24  23  22  21  20  19  18  17  16  15  14  13  12  11  10   9   8   7   6   5   4   3   2   1
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// A Func.  :  F   F      91  89  88  87  86  84  83  82  81  79  78  77  76  74  73  72  71  68  67  66  65  63  62  61  60  58  57  56  55  53  52  51  50  47  46  45  44  42  41  40  39  37  36  35              30  29  26  25  24  23  21  20  19  18  16  15  14  13  11  10   9   8   6   5   4   3   1       F   F
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// U3 OUT   :             19  20  12  21  11  10  23   9  24  25   7  26   6   5  28   4  29   2  31   1  32
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// U2 OUT   :                                                                                                 17  15  18  14  13  20  12  21  22  10  23   9  25   7  26   6   5  28   4  29  30   2  31
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// U1 OUT   :                                                                                                                                                                                                         15  18  13  20  12  21  22  10  23   9   8  25   7  26  27   5  28   4   3  30   2  31  32
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Main display grid pin map
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    { 7, 64 + (21-1)}, // 1GA
    { 8, 64 + (11-1)}, // 2GA
    {22, 64 + (31-1)}, // 3GA
    {23, 64 + ( 1-1)}, // 4GA
    {27, 32 + (18-1)}, // 5GA
    {28, 32 + (14-1)}, // 6GA
    {32, 32 + (21-1)}, // 7GA
    {33, 32 + (22-1)}, // 8GA
    {32, 32 + ( 6-1)}  // 9GA
};

// Main display segment pin map 
static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    // 1st Logical Segment Group, S1 to S20
    {24, 64 + (32-1)}, // S1
    {25, 32 + (17-1)}, // S2
    {26, 32 + (15-1)}, // S3
    {29, 32 + (13-1)}, // S4
    {30, 32 + (20-1)}, // S5
    {31, 32 + (12-1)}, // S6
    {34, 32 + (10-1)}, // S7
    {35, 32 + (23-1)}, // S8
    {36, 32 + ( 9-1)}, // S9
    {37, 32 + (25-1)}, // S10
    {38, 32 + ( 7-1)}, // S11
    {39, 32 + (26-1)}, // S12
    {41, 32 + ( 5-1)}, // S13
    {42, 32 + (28-1)}, // S14
    {43, 32 + ( 4-1)}, // S15
    {44, 32 + (29-1)}, // S16
    {45, 32 + (30-1)}, // S17
    {46, 32 + ( 2-1)}, // S18
    {47, 32 + (31-1)}, // S19
    {51,  0 + (15-1)}, // S20
    // 2nd Logical Segment Letter Group S21+
    { 4, 64 + (19-1)}, // a - S21
    { 5, 64 + (20-1)}, // b - S22
    { 6, 64 + (12-1)}, // c - S23
    { 9, 64 + (10-1)}, // d - S24
    {10, 64 + (23-1)}, // e - S25
    {11, 64 + ( 9-1)}, // f - S26
    {12, 64 + (24-1)}, // g - S27
    {13, 64 + (25-1)}, // h - S28
    {14, 64 + ( 7-1)}, // i - S29
    {15, 64 + (26-1)}, // j - S30
    {16, 64 + ( 6-1)}, // k - S31
    {17, 64 + ( 5-1)}, // l - S32
    {18, 64 + (28-1)}, // m - S33
    {19, 64 + ( 4-1)}, // n - S34
    {20, 64 + (29-1)}, // o - S35
    {21, 64 + ( 2-1)}  // p - S36
};

//
// The resulting registerMask for the main display.
// The driver IC chain is 96-bits or 12 bytes.
// The last 65-bits are used for the main display that are the first 65-bits shifted in.
//
static const UINT8 s_registerMask[] PROGMEM =
{
    0xFF,0xFF,0xFF,0xFF, 
    0xFF,0xFF,0xFF,0xFF, 
    0x00,0x00,0x40,0x00
};

void KenwoodKRV77RPinout::getScanConfig(
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

void KenwoodKRV77RPinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void KenwoodKRV77RPinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
