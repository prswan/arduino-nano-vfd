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
#include "PanasonicDVDRV32Pinout.h"

//
// This is on a Universal VFD V1.00 driver board driven by 1 x A5818 32-bit driver IC.
// * The driver IC is the 2nd IC in the serial chain.
// * This is a shared PCB with the Sony DVP-NS725P on the 1st driver IC in the chain.
// * The display is fitted solder side up lay flat against the PCB.
// * V2 pins 49 (A46), pin 50 (A47) & 51 (A48) are cut trace isolated for Fil2 & resistor
// * V2 pins 53 to 65 (A50 to A62) are cut trace isolated and bridged to V2 pins 70 to 82 (A67 to A79)
//   - Saves using IC U2 when it will all fit on a single 32-bit register
//   - SDIN bridged to SDOUT on unused U2.
//
// See Universal VFD V1.00 Pinout.txt
//
// LSB=31, MSB=0 (physical pins 32 to 1). 31 is the first bit out and 0 the last bit out
//
// IC : Bit   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16  8  9 10 11 12 13 14 15 0  1  2  3  4  5  6  7
//      Byte  |           0         |  |         1          |  |          2         | |          3         |
//
// Pin Layout
// ------------------------------------------------------------------------------------------||------------------------------------------------------------------
// VFD Func :   F              S1  S2  S3  S4  S5  S6  S7  S8  S9 S10 S11 S12 S13 S14 S15 S16 G13 G12 G11 G10  G9  G8  G7  G6  G5  G4  G3  G2  G1               F  
// ------------------------------------------------------------------------------------------||------------------------------------------------------------------
// VFD Pin  :   1               5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  38  39  40  41  42  43  44  45  46  47  48  49  50              54
//-------------------------------------------------------------------------------------------||------------------------------------------------------------------
// V2 Pin   : 102 101 100  99  98  97  96  95  94  93  92  91  90  89  88  87  86  85  84  83  65  64  63  62  61  60  59  58  57  56  55  54  53  52  51  50  49    
//-------------------------------------------------------------------------------------------||--------------------------------------------------||--------------
// A Func.  :   F              95  94  93  92  91  90  89  88  87  86  85  84  83  82  81  80  79  78  77  76  75  74  73  72  71  70  69  68  67               F  
//-----------------------------------------------------------------------------------------------------------------------------------------------||--------------
// U3 OUT   :                  17  15  18  14  19  13  20  12  21  11  22  10  23   9  24   8  25   7  26   6  27   5  28   4  29   3  30   2  31
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
//
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {50, 32 + (31-1)}, // G1
    {49, 32 + ( 2-1)}, // G2
    {48, 32 + (30-1)}, // G3
    {47, 32 + ( 3-1)}, // G4
    {46, 32 + (29-1)}, // G5
    {45, 32 + ( 4-1)}, // G6
    {44, 32 + (28-1)}, // G7
    {43, 32 + ( 5-1)}, // G8
    {42, 32 + (27-1)}, // G9
    {41, 32 + ( 6-1)}, // G10
    {40, 32 + (26-1)}, // G11
    {39, 32 + ( 7-1)}, // G12
    {38, 32 + (25-1)}  // G13
};

static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    { 5, 32 + (17-1)}, // S1
    { 6, 32 + (15-1)}, // S2
    { 7, 32 + (18-1)}, // S3
    { 8, 32 + (14-1)}, // S4
    { 9, 32 + (19-1)}, // S5
    {10, 32 + (13-1)}, // S6
    {11, 32 + (20-1)}, // S7
    {12, 32 + (12-1)}, // S8
    {13, 32 + (21-1)}, // S9
    {14, 32 + (11-1)}, // S10
    {15, 32 + (22-1)}, // S11
    {16, 32 + (10-1)}, // S12
    {17, 32 + (23-1)}, // S13
    {18, 32 + ( 9-1)}, // S14
    {19, 32 + (24-1)}, // S15
    {20, 32 + ( 8-1)}  // S16
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

void PanasonicDVDRV32Pinout::getScanConfig(
    const UINT8 **registerMask,
    UINT8 *registerLenInBits,
    UINT8 *numGrids)
{
    *registerMask = s_registerMask;
    *registerLenInBits = 64;
    *numGrids = ARRAYSIZE(s_pinMapGrid) - 1;
};

void PanasonicDVDRV32Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void PanasonicDVDRV32Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
