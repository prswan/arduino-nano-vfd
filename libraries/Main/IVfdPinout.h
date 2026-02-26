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
#ifndef IVfdPinout_h
#define IVfdPinout_h

#include "Arduino.h"
#include "Types.h"

//
// This maps the display pin to the driver IC register bit.
//
// There are two translations encompassed:
// pin - The physical VFD pin number, 1..n
// bit - The driver IC register bit connected to the physical VFD pin number
//       0..7, 0 - low, shift first, 7 - high, shift last.
//
// The prototype VFD driver Verboard is 1 driver IC of 32-bits (4 bytes).
// The production VFD driver PCB is 3 chained driver IC's making 96-bits (12 bytes).
//
// There are two pin maps for each display:
//
// * The Grid pin map that also defines the (static) grid enable bits used in the grid scan
// * The Segment pin map
//
typedef struct _PinMap
{
    UINT8 pin;
    UINT8 bit;

} PinMap;

//
// Interface for the data container class holding the characteristics of the VFD.
//
class IVfdPinout
{
public:
    //
    // Returns the scan configuration information
    //
    // registerMask - Pointer to the driver IC register mask for this display
    //                in PROGMEN bytes rounded up from registerLenInBits.
    // registerLenInBits - The number of bits in the driver IC shift register.
    // numGrids - The number of grids for the bitmap scan, usually the same as the grid pin count.
    //
    virtual void getScanConfig(
        const UINT8 **registerMask,
        UINT8 *registerLenInBits,
        UINT8 *numGrids) = 0;

    //
    // Returns the physical connection map for the grid pins G1 .. Gx
    // as bit positions in the scan bitmap.
    // pinMap[0] is not used, the map entries begin at pinMap[1].
    // The pinMap is located in PROGMEM.
    //
    virtual void getPinMapGrid(
        const PinMap **p_pinMap,
        UINT8 *numEntries) = 0;

    //
    // Returns the physical connection map for the segment pins S1 .. Sx
    // as bit positions in the scan bitmap.
    // pinMap[0] is not used, the map entries begin at pinMap[1].
    // The pinMap is located in PROGMEM.
    //
    virtual void getPinMapSegment(
        const PinMap **p_pinMap,
        UINT8 *numEntries) = 0;
};

#endif
