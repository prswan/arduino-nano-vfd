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
#ifndef SamsungBDP1590Pinout_h
#define SamsungBDP1590Pinout_h

#include "Arduino.h"
#include "IVfdPinout.h"

//
// VFD pinout for the Sony DVP-NS725P DVD Player front panel.
// Uses an MC3401 integrated bitmap display controller, equivalent to Princeton PT6315. 
//
class SamsungBDP1590Pinout : public IVfdPinout
{
public:
    SamsungBDP1590Pinout() {};

    ~SamsungBDP1590Pinout() {};

    virtual void getScanConfig(
        const UINT8 **registerMask,
        UINT8 *registerLenInBits,
        UINT8 *numGrids);

    virtual void getPinMapGrid(
        const PinMap **p_pinMap,
        UINT8 *numEntries);

    virtual void getPinMapSegment(
        const PinMap **p_pinMap,
        UINT8 *numEntries);
};

#endif
