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
#include "KossWMS1100Pinout.h"


//
// VFD pin number to controller function/line address pin number (GR1 to GR16).
// No information found about this system, assigned 1-1.
//
static const PinMap s_pinMapGrid[] PROGMEM =
{
    {0, 0},
    // pin, bit (GR-1)
    { 1, ( 1-1)}, // G1
    { 2, ( 2-1)}, // G2
    { 3, ( 3-1)}, // G3
    { 4, ( 4-1)}, // G4
    { 5, ( 5-1)}, // G5
    { 6, ( 6-1)}, // G6
    { 7, ( 7-1)}, // G7
    { 8, ( 8-1)}, // G8
    { 9, ( 9-1)}, // G9
    {10, (10-1)}, // G10
    {11, (11-1)}, // G11
    {12, (12-1)}, // G12
    {13, (13-1)}, // G13
    {14, (14-1)}, // G14
    {15, (15-1)}, // G15
    {16, (16-1)}, // G16
};

//
// VFD pin number to controller function/line address pin number (SG1 to SG19).
// No information found about this system, assigned 1-1.
//
static const PinMap s_pinMapSegment[] PROGMEM =
{
    {0, 0},
    // pin, bit (OUT-1)
    { 1, ( 1-1)}, // S1
    { 2, ( 2-1)}, // S2
    { 3, ( 3-1)}, // S3
    { 4, ( 4-1)}, // S4
    { 5, ( 5-1)}, // S5
    { 6, ( 6-1)}, // S6
    { 7, ( 7-1)}, // S7
    { 8, ( 8-1)}, // S8
    { 9, ( 9-1)}, // S9
    {10, (10-1)}, // S10
    {11, (11-1)}, // S11
    {12, (12-1)}, // S12
};

//
// The resulting registerMask for this display.
// The driver IC operatees up to a 24-bit address.
// LS Byte and LS Bit first.
//
static const UINT8 s_registerMask[] PROGMEM =
{
    0xFF,0xFF,0xFF
};

void KossWMS1100Pinout::getScanConfig(
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

void KossWMS1100Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void KossWMS1100Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
