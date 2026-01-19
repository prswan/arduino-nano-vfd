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

#include "Buttons.h"

// Button sample period
static const UINT32 s_samplePeriodInMs = 50;


Buttons::Buttons(
    int b1pin,
    int b2pin,
    int b3pin
)
{
    UINT32 nextUpdateTime = millis() + s_samplePeriodInMs;

    m_state[0].pin = b1pin;
    m_state[1].pin = b2pin;
    m_state[2].pin = b3pin;

    m_state[0].nextUpdateTime = nextUpdateTime;
    m_state[1].nextUpdateTime = nextUpdateTime;
    m_state[2].nextUpdateTime = nextUpdateTime;

    // Set the pin modes
    pinMode(b1pin, INPUT_PULLUP);
    pinMode(b2pin, INPUT_PULLUP);
    pinMode(b3pin, INPUT_PULLUP);
};


bool
Buttons::isPressed(
    int button
)
{
    UINT32 currentTime = millis();

    if (currentTime < m_state[button].nextUpdateTime)
    {
        return false;
    }

    // Set the next sample time
    m_state[button].nextUpdateTime = currentTime + s_samplePeriodInMs;

    // Button is pressed
    if (digitalRead(m_state[button].pin) == LOW)
    {
        // We already reported it pressed, don't report again.
        if (m_state[button].wasReported)
        {
            return false;
        }

        // New press, we'll report in this call.
        m_state[button].wasReported = true;
    }
    else
    {
        // Button not pressed, clear press state
        m_state[button].wasReported = false;
    }

    return m_state[button].wasReported;
};

