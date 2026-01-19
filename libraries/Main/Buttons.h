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
#ifndef Buttons_h
#define Buttons_h

#include "Types.h"


//
// Handle the read of direct attached buttons.
//
// * Caller must spin poll for button presses at least every 50ms.
// * Debounce is performed by 50ms sample
// * Ensures each press is reported only once on first press.
//   - Button must be released to activate unable press.
//
class Buttons
{
    public:

        Buttons(
            int b1pin,
            int b2pin,
            int b3pin
        );

        bool isB1Pressed()
        { return isPressed(0); };

        bool isB2Pressed()
        { return isPressed(1); };

        bool isB3Pressed()
        { return isPressed(2); };

    private:

        bool isPressed(
            int button
        );

        typedef struct _ButtonState
        {
            int    pin;
            UINT32 nextUpdateTime;
            bool   wasReported;
        } ButtonState;

        ButtonState m_state[3] = {0};
};

#endif
