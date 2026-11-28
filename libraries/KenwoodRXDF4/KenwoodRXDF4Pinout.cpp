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
#include "KenwoodRXDF4Pinout.h"

//
// The display is mounted with VFD pin 57 at 2mm PCB position 1, so:
// PCB position = 58 - VFD pin.
//
// Universal VFD V1.20 mapping:
// - PCB positions 4..35 map to U1 and register bits 0..31.
// - PCB positions 36..67 map to U2 and register bits 32..63.
//
// The service manual identifies S1..S40 on VFD pins 6..45 and G1..G8
// on VFD pins 46..53. VFD pins 1..5 and 54..57 are not driver outputs.
//
// Segment pin map
static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    { 6, 32 + (24-1)}, // S1
    { 7, 32 + ( 8-1)}, // S2
    { 8, 32 + (25-1)}, // S3
    { 9, 32 + ( 7-1)}, // S4
    {10, 32 + (26-1)}, // S5
    {11, 32 + ( 6-1)}, // S6
    {12, 32 + (27-1)}, // S7
    {13, 32 + ( 5-1)}, // S8
    {14, 32 + (28-1)}, // S9
    {15, 32 + ( 4-1)}, // S10
    {16, 32 + (29-1)}, // S11
    {17, 32 + ( 3-1)}, // S12
    {18, 32 + (30-1)}, // S13
    {19, 32 + ( 2-1)}, // S14
    {20, 32 + (31-1)}, // S15
    {21, 32 + ( 1-1)}, // S16
    {22, 32 + (32-1)}, // S17
    {23, (16-1)}, // S18
    {24, (17-1)}, // S19
    {25, (15-1)}, // S20
    {26, (18-1)}, // S21
    {27, (14-1)}, // S22
    {28, (19-1)}, // S23
    {29, (13-1)}, // S24
    {30, (20-1)}, // S25
    {31, (12-1)}, // S26
    {32, (21-1)}, // S27
    {33, (11-1)}, // S28
    {34, (22-1)}, // S29
    {35, (10-1)}, // S30
    {36, (23-1)}, // S31
    {37, ( 9-1)}, // S32
    {38, (24-1)}, // S33
    {39, ( 8-1)}, // S34
    {40, (25-1)}, // S35
    {41, ( 7-1)}, // S36
    {42, (26-1)}, // S37
    {43, ( 6-1)}, // S38
    {44, (27-1)}, // S39
    {45, ( 5-1)}  // S40
};

static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    {46, (28-1)}, // G1
    {47, ( 4-1)}, // G2
    {48, (29-1)}, // G3
    {49, ( 3-1)}, // G4
    {50, (30-1)}, // G5
    {51, ( 2-1)}, // G6
    {52, (31-1)}, // G7
    {53, ( 1-1)}  // G8
};

//
// The display uses outputs on U1 and U2 of the 64-bit serial chain.
// Mask byte order is most-significant register byte first.
//
static const UINT8 s_registerMask[] PROGMEM =
{
    0xFF,0x80,0x00,0xFF,
    0x7F,0xFF,0xFF,0xFF
};

void KenwoodRXDF4Pinout::getProperties(
    PinoutProperties *pinoutProperties)
{
    memset(pinoutProperties, 0x00, sizeof(*pinoutProperties));

    pinoutProperties->driverType        = DriverTypeSN75518;
    pinoutProperties->spiClockFrequency = 2;
    pinoutProperties->registerLenInBits = 64;
    pinoutProperties->p_registerMask    = s_registerMask;
    pinoutProperties->numGrids          = ARRAYSIZE(s_pinMapGrid) - 1;
};

void KenwoodRXDF4Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void KenwoodRXDF4Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
