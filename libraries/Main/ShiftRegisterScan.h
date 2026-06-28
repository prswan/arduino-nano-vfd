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
#ifndef ShiftRegisterScan_h
#define ShiftRegisterScan_h

#include "Arduino.h"
#include "Types.h"
#include "MuxSpi.h"
#include "ShiftRegisterBitMap.h"

//
// VFD serial driver scan.
//
class ShiftRegisterScan
{
public:

    //
    // bitMap     - Pointer to an array of bitMaps.
    // numBitMaps - Number of entries in the bitmap array.
    //
    // There is a 1-1 mapping between enrties in the bitMap
    // array and the associated port ([0] == PL1, [1] == PL2 ...)
    // Unusued ports have a NULL bitMap entry.
    //
    ShiftRegisterScan(
        MuxSpi*               muxSpi,
        ShiftRegisterBitMap** bitMap,
        UINT8                 numBitMaps);

    ~ShiftRegisterScan() {};

    //
    // Update the display with the bitmap content.
    //
    // This is called by the timer ISR.
    //
    void scan();

    //
    // Return the time taken for 1 grid scan in microseconds.
    //
    UINT32 getScanTimeInUs()
    {
        UINT32 x = m_scanTimeInUs;
        m_scanTimeInUs = 0;
        return x;
    };

private:
    MuxSpi*               m_muxSpi;
    ShiftRegisterBitMap** m_bitMap;
    UINT8                 m_numBitMaps;

    UINT32                m_scanTimeInUs;
};

#endif
