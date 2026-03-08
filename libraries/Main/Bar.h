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
#ifndef Bar_h
#define Bar_h

#include "IDisplay.h"


//
// Functions for managing bar elements.
//
class Bar
{
public:
    Bar() {};

    ~Bar() {};

    //
    // Set the length of a bar from it's origin.
    //
    // "scale" - control the display of an attached scale, if there is one.
    // If there is no attached scale, it has no effect.
    // - true  - the scale is displayed and the bar starts from segment 1.
    // - false - segment bar 1 & associated scale are skipped to start at segment 2.
    //
    // "len" - the length of the bar to set in segments with 0 being all off.
    // If len exceeds the number of segments in the bar, the remainder is ignored.
    // The maximum known length is set by SegmentGroupBar.pinS[].
    //
    // returns false if the region or instance does not exist.
    //  
    static bool set(
        Vfd  *vfd,
        UINT8 regionId,
        UINT8 instance,
        bool  scale,
        UINT8 len
    );

};

#endif
