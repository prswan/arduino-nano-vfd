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
static const UINT32 s_longPressPeriodInMs = 1000;

Buttons::Buttons(
    int pinNext,
    int pinSelect
)
{
    UINT32 nextUpdateTime = millis() + s_samplePeriodInMs;

    m_stateNext.pin   = pinNext;
    m_stateSelect.pin = pinSelect;

    m_stateNext.nextUpdateTime   = nextUpdateTime;
    m_stateSelect.nextUpdateTime = nextUpdateTime;
 
    // Set the pin modes
    pinMode(pinNext,   INPUT_PULLUP);
    pinMode(pinSelect, INPUT_PULLUP);
};


void
Buttons::updateButtonState(
    ButtonState *state
)
{
    UINT32 currentTime = millis();

    if (currentTime < state->nextUpdateTime)
    {
        return false;
    }

    // Set the next sample time
    state->nextUpdateTime = currentTime + s_samplePeriodInMs;

    // Button is pressed
    if (digitalRead(state->pin) == LOW)
    {
        // We already saw it was pressed
        if (state->wasPressed)
        {
            //
            // If it's been held down for a long time, report the press
            // and update the press time. The net effect is that every
            // long press period a long key press (auto-repeat) will be
            // generated.
            //
            if (currentTime > (state->wasPressedTime + s_longPressPeriodInMs))
            {
                state->reportLong = true;
                state->autoRepeat = true;

                state->wasPressedTime = currentTime;
            }

            return;
        }

        // New press, we'll report in this call.
        state->wasPressed = true;
        state->wasPressedTime = currentTime;
    }
    else
    {
        // Button was previously pressed, determine what type of press
        if (state->wasPressed)
        {
            // If auto repeating long presses, clear state, otherwise report a short press
            if (state->autoRepeat)
            {
                state->autoRepeat = false;
            }
            else
            {
                state->reportShort = true;
            }

            // Clear the press state
            state->wasPressed = false;
            state->wasPressedTime = 0;
        }
    }
};


bool
Buttons::isActive(
    ButtonState *state
)
{
    if (digitalRead(state->pin) == LOW)
    {
        return true;
    }

    return false;
};


bool
Buttons::isShortPressed(
    ButtonState *state
)
{
    updateButtonState(state);

    if (state->reportShort)
    {
        state->reportShort = false;
        return true;
    }

    return false;
};


bool
Buttons::isLongPressed(
    ButtonState *state
)
{
    updateButtonState(state);

    if (state->reportLong)
    {
        state->reportLong = false;
        return true;
    }

    return false;
};
