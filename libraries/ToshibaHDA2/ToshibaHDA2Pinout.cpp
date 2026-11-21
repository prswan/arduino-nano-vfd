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
#include "ToshibaHDA2Pinout.h"

//
// This is on a Universal VFD V1.10 driver board driven by 1 x SN75518 32-bit driver IC.
// * The driver IC is the 2nd IC in the serial chain.
// * This is a shared PCB with the Panasonic SA-BT330 on the 1st driver IC in the chain.
// * The display is fitted solder side up lay flat against the PCB.
// * V2 pins 50 (A47), pin 49 (A46) are cut trace isolated for Fil.
// * There are 10 patch wires noted below in the table (P) to connect unused U3 drivers to U2 pins.
//   - Saves using IC U2 when it will all fit on a single 32-bit register
//   - SDIN bridged to SDOUT on unused U2.
//
// See Universal VFD V1.10 Pinout.txt
//
// LSB=31, MSB=0 (physical pins 32 to 1). 31 is the first bit out and 0 the last bit out
//
// IC : Bit   31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16  8  9 10 11 12 13 14 15 0  1  2  3  4  5  6  7
//      Byte  |           0         |  |         1          |  |          2         | |          3         |
//
// Pin Layout
// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VFD Func    :   F   F          G1  G2  G3  G4  G5  G6  G7  G8  G9 G10 G11 G12 G13 G14          S1  S2  S3  S4  S5  S6  S7  S8  S9 S10 S11 S12 S13 S14 S15 S16 S17 S18           F   F                 
// -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// VFD Pin     :   1   2           5   6   7   8   9  10  11  12  13  14  15  16  17  18          21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38          41  42
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// V1 Pin      :  80  79  78  77  76  75  74  73  72  71  70  69  68  67  66  65  64  63  62  61  60  59  58  57  56  55  54  53  52  51  50  49  48  47  46  45  44  43  42  41  40  39  
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// A Func.     :   F   F          94  93  92  91  89  88  87  86  84  83  82  81  79  78          74  73  72  71  68  67  66  65  63  62  61  60  58  57  56  55  53  52          47  46
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// V2 Pin      : 102 101          97  96  95  94  92  91  90  89  87  86  85  84  82  81          77  76  75  74  71  70  69  68  65  64  63  62  61  60  59  58  56  55          50  49
//------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------
// V2 Pin (P)  :                                                                                                                  99  98  93  88  83  80  79  78  73  72
//------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------
// A Func.(P)  :                                                                                                                  96  95  90  85  80  77  76  75  70  69
//------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------
// U3 OUT      :                  15  18  14  19  20  12  21  11  10  23   9  24  25   7           5  28   4  29   2  31   1  32  16  17  13  22   8  26   6  27   3  30
//------------------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------
//
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    { 5, 32 + (15-1)}, // G1
    { 6, 32 + (18-1)}, // G2
    { 7, 32 + (14-1)}, // G3
    { 8, 32 + (19-1)}, // G4
    { 9, 32 + (20-1)}, // G5
    {10, 32 + (12-1)}, // G6
    {11, 32 + (21-1)}, // G7
    {12, 32 + (11-1)}, // G8
    {13, 32 + (10-1)}, // G9
    {14, 32 + (23-1)}, // G10
    {15, 32 + ( 9-1)}, // G11
    {16, 32 + (24-1)}, // G12
    {17, 32 + (25-1)}, // G13
    {18, 32 + ( 7-1)}  // G14
};

static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {21, 32 + ( 5-1)}, // S1
    {22, 32 + (28-1)}, // S2
    {23, 32 + ( 4-1)}, // S3
    {24, 32 + (29-1)}, // S4
    {25, 32 + ( 2-1)}, // S5
    {26, 32 + (31-1)}, // S6
    {27, 32 + ( 1-1)}, // S7
    {28, 32 + (32-1)}, // S8
    {29, 32 + (16-1)}, // S9
    {30, 32 + (17-1)}, // S10
    {31, 32 + (13-1)}, // S11
    {32, 32 + (22-1)}, // S12
    {33, 32 + ( 8-1)}, // S13
    {34, 32 + (26-1)}, // S14
    {35, 32 + ( 6-1)}, // S15
    {36, 32 + (27-1)}, // S16
    {37, 32 + ( 3-1)}, // S17
    {38, 32 + (30-1)}  // S18
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

void ToshibaHDA2Pinout::getProperties(
    PinoutProperties *pinoutProperties)
{
    memset(pinoutProperties, 0x00, sizeof(*pinoutProperties));

    pinoutProperties->driverType        = DriverTypeSN75518;
    pinoutProperties->spiClockFrequency = 2;
    pinoutProperties->registerLenInBits = 64;
    pinoutProperties->p_registerMask    = s_registerMask;
    pinoutProperties->numGrids          = ARRAYSIZE(s_pinMapGrid) - 1;
};

void ToshibaHDA2Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void ToshibaHDA2Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
