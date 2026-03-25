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
#include "PioneerDVR220Pinout.h"


//
// VFD pin number to controller function/line address pin number (GR1 to GR12).
// Taken from the service manual, the grid pins are connected in order.
//
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (GR-1)
    { 9, ( 1-1)}, // G1
    {10, ( 2-1)}, // G2
    {11, ( 3-1)}, // G3
    {12, ( 4-1)}, // G4
    {13, ( 5-1)}, // G5
    {14, ( 6-1)}, // G6
    {15, ( 7-1)}, // G7
    {16, ( 8-1)}, // G8
    {17, ( 9-1)}, // G9
    {18, (10-1)}, // G10
    {19, (11-1)}, // G11
    {20, (12-1)}, // G12
};

//
// VFD pin number to controller function/line address pin number (SG1 to SG19).
// Taken from the service manual, the segment pins are connected in order.
//
static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {41, ( 1-1)}, // S1
    {40, ( 2-1)}, // S2
    {39, ( 3-1)}, // S3
    {38, ( 4-1)}, // S4
    {37, ( 5-1)}, // S5
    {36, ( 6-1)}, // S6
    {35, ( 7-1)}, // S7
    {34, ( 8-1)}, // S8
    {33, ( 9-1)}, // S9
    {27, (10-1)}, // S10
    {26, (11-1)}, // S11
    {25, (12-1)}, // S12
    {24, (13-1)}, // S13
    {23, (14-1)}, // S14
    {22, (15-1)}, // S15
    {21, (16-1)}  // S16
};

//
// The resulting registerMask for this display.
// The driver IC operatees up to a 24-bit address.
// Only 20 bits are used for this display.
// configured for 20 bits, LS Byte and LS Bit first.
//
static const UINT8 s_registerMask[] PROGMEM =
{
    0xFF,0xFF,0xFF
};

void PioneerDVR220Pinout::getScanConfig(
    DriverType *driverType,
    const UINT8 **registerMask,
    UINT8 *registerLenInBits,
    UINT8 *numGrids)
{
    // Used to select the flavour in the PT631xDriverIC implementation.
    *driverType = DriverTypePT6311;

    *registerMask = s_registerMask;

    // Used to calculate the driver IC memory address layout.
    *registerLenInBits = 24;

    // This sets the driver IC grid configuration register.
    *numGrids = ARRAYSIZE(s_pinMapGrid) - 1;
};

void PioneerDVR220Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void PioneerDVR220Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
