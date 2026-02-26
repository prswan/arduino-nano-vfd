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
#ifndef ShiftRegisterBitMap_h
#define ShiftRegisterBitMap_h

#include "Arduino.h"
#include "Types.h"
#include "ShiftRegisterDisplay.h"

//
// VFD serial register bitmap class for multiple displays on the same
// serial register chain.
//
class ShiftRegisterBitMap
{
public:
    ShiftRegisterBitMap(
        IVfdPinout *vfd1,
        IVfdPinout *vfd2
    );

    ~ShiftRegisterBitMap();

    //
    // Return the displays created from the bit map.
    //
    IDisplay* getDisplay(int index)
    {
        return m_display[index];
    }

    //
    // Return the maximal register length defined by the VFD driver.
    //
    UINT8 getRegisterLenInBytes()
    {
        return m_registerLenInBytes;
    };

    //
    // Get the current register data to display out in the scan.
    // This is an aggregate for multiple displays as follows:
    //
    // - "data" buffer cleared
    // - Register content for Display 0 Grid x read & masked into "data"
    // - Register content for Display 1 Grid y read & masked into "data"
    // - true returned.
    //
    // false (failure) is returned if the supplied data buffer doesn't
    // match the registerLenInBytes.
    //
    bool getCurrentRegisterData(
        UINT8 *data, 
        UINT8 dataLenInBytes
    );

    //
    // Increment the grid pointers to the next register data line.
    //
    void incGrids();

private:

    ShiftRegisterDisplay* m_display[2];

    UINT8 m_registerLenInBits;
    UINT8 m_maxNumGrids;
    UINT8 m_registerLenInBytes;
    UINT8 m_bitMapSizeInBytes;

    UINT8 *m_bitMap;
};

#endif
