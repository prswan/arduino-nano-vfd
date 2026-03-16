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
#ifndef IDriverIC_h
#define IDriverIC_h

#include "Arduino.h"
#include "Types.h"

//
// Interface to VFD Integrated Driver/Controller IC's based on simple integrated bit maps.
// e.g. PT6311, PT6315, MC3401 etc. there are many clones and variants.
//
// This is intended to be a stateless transport layer implementation.
//
class IDriverIC
{
    public:

        //
        // Must be called ONCE before any data is written, set the display characteristics.
        // This is used to determine the memory layout & addressing.
        //
        virtual bool setDisplayMode(
            UINT8 port,
            UINT8 numGrids,
            UINT8 numSegments
        ) = 0;

        //
        // Writes a sequence of consecutive segment data bytes to the IDIC bit map at the indicated grid address. 
        // The implementation converts the grid address into an IDIC memory address.
        //
        // returns false on failure, e.g. the address was out of range.
        //
        virtual bool write(
            UINT8 port,
            UINT8 gridAddress,
            const UINT8 *segData,
            UINT8 segDataLenInBytes
        ) = 0;
};


#endif
