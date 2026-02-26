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
#ifndef IDisplay_h
#define IDisplay_h

#include "Arduino.h"
#include "Types.h"

//
// Primary interface for elemental use of VFDs.
//
class IDisplay
{
public:
    //
    // Clear the display back to blank
    //
    virtual void clear() = 0;

    //
    // Set all the segments of every grid scan to on.
    // This is a test function to easily see if a grid or segment pin was missed.
    //
    virtual void setAllSegmentsOn() = 0;

    //
    // Turn on/off the segment pinS on grid pinG where the pins are the
    // display logical pins G1..Gx and S1..Sx. The function will translate
    // the logical pins to physical pins driven by the driver IC.
    //
    // returns true on success or false if failed, e.g. pinG or pinS out of bounds.
    //
    virtual bool setSegment(
        UINT8 pinG,
        UINT8 pinS,
        bool on
    ) = 0;
};

#endif
