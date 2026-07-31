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
#include "KronosSystem55Pinout.h"

//
// This is a complete front panel PCB originaly wired as a 5 bit wide data bus with the
// following modifications:
// - Since we're using 1-bit SPI, the board was patched to connect SERIAL OUT to DATA IN
//   from U1 to U5 creating a single 60-bit serial chain.
// - Diodes CR1 to CR7 were removed and CR1 to CR3 were replaced with a 0R link.
// - We also needed the built in latch that wasn't used on this PCB but thankfully common
//   to a pullup. This net was patched to the unused "key" IDC pin pad for ease of wiring.
//

//
// There is no public manual for this so the pin-to-driver mapping is 1-to-1 
// and also in character order
//
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {16, (16-1)}, // G1
    { 4, ( 4-1)}, // G2
    {40, (40-1)}, // G3
    {52, (52-1)}, // G4
    {15, (15-1)}, // G5
    { 3, ( 3-1)}, // G6
    {39, (39-1)}, // G7
    {51, (51-1)}, // G8
    {14, (14-1)}, // G9
    { 2, ( 2-1)}, // G10
    {38, (38-1)}, // G11
    {50, (50-1)}, // G12
    {13, (13-1)}, // G13
    { 1, ( 1-1)}, // G14
    {37, (37-1)}, // G15
    {49, (49-1)}  // G16
};

//
// 5x7 only, 35 pins.
//
// There is no public manual for this so the pin-to-driver mapping is 1-to-1 
// and also in 5x7 character font byte & bit order
//
// Top    Left  is Column 1 Row 1
// Bottom Left  is Column 1 Row 7
// Top    Right is Column 5 Row 1
// Bottom Left  is Column 5 Row 7
//
static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {35, (35-1)}, // S1  - C1 R1
    {34, (34-1)}, // S2  - C1 R2
    {33, (33-1)}, // S3  - C1 R3
    {32, (32-1)}, // S4  - C1 R4
    {31, (31-1)}, // S5  - C1 R5
    {30, (30-1)}, // S6  - C1 R6
    {29, (29-1)}, // S7  - C1 R7

    {23, (23-1)}, // S8  - C2 R1
    {22, (22-1)}, // S9  - C2 R2
    {21, (21-1)}, // S10 - C2 R3
    {20, (20-1)}, // S11 - C2 R4
    {19, (19-1)}, // S12 - C2 R5
    {18, (18-1)}, // S13 - C2 R6
    {17, (17-1)}, // S14 - C2 R7

    {11, (11-1)}, // S15 - C3 R1
    {10, (10-1)}, // S16 - C3 R2
    { 9, ( 9-1)}, // S17 - C3 R3
    { 8, ( 8-1)}, // S18 - C3 R4
    { 7, ( 7-1)}, // S19 - C3 R5
    { 6, ( 6-1)}, // S20 - C3 R6
    { 5, ( 5-1)}, // S21 - C3 R7

    {47, (47-1)}, // S22 - C4 R1
    {46, (46-1)}, // S23 - C4 R2
    {45, (45-1)}, // S24 - C4 R3
    {44, (44-1)}, // S25 - C4 R4
    {43, (43-1)}, // S26 - C4 R5
    {42, (42-1)}, // S27 - C4 R6
    {41, (41-1)}, // S28 - C4 R7

    {59, (59-1)}, // S29 - C5 R1
    {58, (58-1)}, // S30 - C5 R2
    {57, (57-1)}, // S31 - C5 R3
    {56, (56-1)}, // S32 - C5 R4
    {55, (55-1)}, // S33 - C5 R5
    {54, (54-1)}, // S34 - C5 R6
    {53, (53-1)}  // S35 - C5 R7
};

//
// The resulting registerMask for this display.
// The driver IC chain is 5 x 12-bits or 60 bits total.
// This system requires 8-bit alignment so rounded up to 64-bits
// - The first 4 bits in fall off the end of the shift.
//
static const UINT8 s_registerMask[] PROGMEM =
{
    0x0F,0xFF,0xFF,0xFF, 0xFF,0xFF,0xFF,0xFF
};

void KronosSystem55Pinout::getScanConfig(
    DriverType *driverType,
    const UINT8 **registerMask,
    UINT8 *registerLenInBits,
    UINT8 *numGrids)
{
    *driverType = DriverTypeSN75518;
    *registerMask = s_registerMask;
    *registerLenInBits = 64;
    *numGrids = ARRAYSIZE(s_pinMapGrid) - 1;
};

void KronosSystem55Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void KronosSystem55Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
