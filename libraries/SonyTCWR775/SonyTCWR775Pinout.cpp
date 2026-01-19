//
// Copyright (c) 2025, Paul R. Swan
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
#include "SonyTCWR775Pinout.h"

//
// This is the prototype Verboard build with single A5818 32-bit driver IC.
//
// IC1 - LSB=31, MSB=0 (physical pins 32 to 1). 31 is the first bit out and 0 the last bit out
//
// Pin Layout
// ------------------------------------------------------------------------------------------------------------
// VFD: ---  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 --- 27 28 29 30 31 32 33 34 35 36 37 39 39 40 41 42
// ------------------------------------------------------------------------------------------------------------
// IC1: Bit  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15     31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16
//      Byte |          3         |  |          2         |     |           0         |  |         1          |
//
//
static const PinMap s_pinMapGrid[] PROGMEM =
    {
        {0, 0},
        // pin, bit
        {12, 7}, // G1
        {11, 6}, // G2
        {10, 5}, // G3
        {9, 4},  // G4
        {8, 3},  // G5
        {7, 2},  // G6
        {6, 1},  // G7
        {5, 0}   // G8
};

static const PinMap s_pinMapSegment[] PROGMEM =
    {
        {0, 0},
        // pin, bit
        {42, 16}, // a - S1
        {41, 17}, // b - S2
        {40, 18}, // c - S3
        {39, 19}, // d - S4
        {38, 20}, // e - S5
        {37, 21}, // f - S6
        {36, 22}, // g - S7
        {35, 23}, // h - S8
        {34, 24}, // i - S9
        {33, 25}, // j - S10
        {32, 26}, // k - S11
        {31, 27}, // l - S12
        {30, 28}, // m - S13
        {17, 12}, // n - S14
        {16, 11}, // o - S15
        {17, 10}, // p - S16
        {14, 9},  // q - S17
        {13, 8}   // r - S18
};

void SonyTCWR775Pinout::getScanConfig(
    UINT8 *registerLenInBits,
    UINT8 *numGrids)
{
    *registerLenInBits = 32;
    *numGrids = ARRAYSIZE(s_pinMapGrid) - 1;
};

void SonyTCWR775Pinout::getPinMapGrid(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapGrid;
    *numEntries = ARRAYSIZE(s_pinMapGrid);
};

void SonyTCWR775Pinout::getPinMapSegment(
    const PinMap **p_pinMap,
    UINT8 *numEntries)
{
    *p_pinMap = s_pinMapSegment;
    *numEntries = ARRAYSIZE(s_pinMapSegment);
};
