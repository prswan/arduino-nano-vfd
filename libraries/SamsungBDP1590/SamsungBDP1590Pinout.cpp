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
#include "SamsungBDP1590Pinout.h"

//
// VFD pin number to controller function/line address pin number (GR1 to GR12).
// Taken from the service manual, the grid pins are connected in order.
//
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (GR-1)
    { 5, ( 1-1)}, // G1
    { 6, ( 2-1)}, // G2
    { 7, ( 3-1)}, // G3
    { 8, ( 5-1)}, // G4
    { 9, ( 5-1)}, // G5
    {10, ( 6-1)}, // G6
    {11, ( 7-1)}  // G7
};

//
// VFD pin number to controller function/line address pin number (SG1 to SG19).
// Taken from the service manual, the segment pins are NOT connected in order.
//
static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {16, (19-1)}, // S1
    {17, (18-1)}, // S2
    {18, (17-1)}, // S3
    {19, (16-1)}, // S4
    {20, (15-1)}, // S5
    {21, (14-1)}, // S6
    {22, (13-1)}, // S7
    {23, (12-1)}, // S8
    {24, (11-1)}, // S9
    {25, (10-1)}, // S10
    {26, ( 9-1)}, // S11
    {27, ( 8-1)}, // S12
    {28, ( 7-1)}, // S13
    {29, ( 6-1)}, // S14
    {30, ( 5-1)}, // S15
    {31, ( 4-1)}, // S16
    {32, ( 3-1)}, // S17
    {33, ( 2-1)}, // S18
    {34, ( 1-1)}  // S19
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

void SamsungBDP1590Pinout::getScanConfig(
    const UINT8 **registerMask,
    UINT8 *registerLenInBits,
    UINT8 *numGrids)
{
    *registerMask = s_registerMask;

    // Used to calculate the driver IC memory address layout.
    *registerLenInBits = 24;

    // This sets the driver IC grid configuration register.
    *numGrids = ARRAYSIZE(s_pinMapGrid) - 1;
};

void SamsungBDP1590Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void SamsungBDP1590Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
