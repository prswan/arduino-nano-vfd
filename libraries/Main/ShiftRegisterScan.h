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
#include "SPI.h"
#include "Types.h"
#include "ShiftRegisterBitMap.h"

//
// VFD serial driver scan.
//
class ShiftRegisterScan
{
public:
    ShiftRegisterScan(
        ShiftRegisterBitMap *bitMap,
        int pinStrobe,
        int pinBlank);

    ~ShiftRegisterScan();

    //
    // Update the display with the bitmap content.
    // scan should be spin-called and will return immediately if no update
    // is needed.
    //
    // The return value can be used to synchronize other operations to the start of
    // a new grid.
    // - false - No action.
    // - true  - Grid update was performed
    //
    bool run();

private:
    ShiftRegisterBitMap *m_bitMap;

    UINT8 m_registerLenInBytes;
    
    UINT8 *m_register;

    SPISettings m_spiSettings{1000000, MSBFIRST, SPI_MODE0};

    int m_pinStrobe;
    int m_pinBlank;

    UINT32 m_nextUpdateTimeInUS;
};

#endif
