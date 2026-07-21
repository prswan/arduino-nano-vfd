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
#ifndef AppEngine_h
#define AppEngine_h

#include "Controller.h"

//
// This is used as the call made based on the timer tick.
// Background
//
typedef void (*runCallback)(Controller *controller);

// No callback.
#define NO_RUN_CALLBACK ((runCallback) (NULL))

//
// This is used as the call made based on engine state 
// transitions in response to buttons.
// Foreground
//
typedef void (*onCallback)(Controller *controller);

// No callback.
#define NO_ON_CALLBACK ((onCallback) (NULL))

//
// Entry for the AppEngine to interact with applications
// and utilities comprising one background continuous run
// callback tied to the coarse timer and various foreground
// action callbacks from the AppEngine state button inputs.
//
// TODO: Needs to move to PROGMEM
//
// After power on, for code simplicity, the first entry 0 is skipped
// and 1+ is selected.
//
// The termination of an array is description[0] == 0
//
typedef struct _AppEngineMenu {

    UINT8            description[8]; // 7 characters + null
    runCallback      run;
    onCallback       onSelect;
    onCallback       onDeSelect;
    onCallback       onNextShortPress;
    onCallback       onNextLongPress;

} AppEngineMenu;

//
// Does not return
//
void AppEngine(Controller *controller, AppEngineMenu *menu);

#endif
