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
#ifndef SonyTCWR775Layout_h
#define SonyTCWR775Layout_h

#include "Arduino.h"
#include "IVfdLayout7Seg.h"

//
// VFD implementation for the Sony TC-WR775 Twin Cassette Deck.
// driven by a single A6518 32-bit serial driver IC.
//
class SonyTCWR775Layout : public IVfdLayout7Seg
{
public:
    SonyTCWR775Layout() {};

    ~SonyTCWR775Layout() {};

    virtual bool getSegmentGroup7Seg(
        UINT8 row,
        const SegmentGroup7Seg **p_segGroup,
        UINT8 *numEntries);
};

/*
//
// print a 0..9 single hex digit into the display map.
//
PERROR print7Seg(DisplayMap *map, UINT8 row, UINT8 col, UINT8 value);

*/

#endif
