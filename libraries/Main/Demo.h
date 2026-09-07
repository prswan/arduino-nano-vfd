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
#ifndef Demo_h
#define Demo_h

#include "Controller.h"


//
// Full system demo
//
class Demo
{
    public:

        static void onSelect(
            Controller* controller
        );

        static void onNextShortPress(
            Controller* controller
        );

        static void onNextLongPress(
            Controller* controller
        );

        static void run(
            Controller* controller
        );

    private:

        static void runAscii(
            Controller* controller,
            Vfd*        vfd,
            UINT8       dispIndex,
            UINT32      rndNum
        );

        static void runBar(
            Controller* controller,
            Vfd*        vfd,
            UINT8       dispIndex,
            UINT32      rndNum
        );

        static void runNumberList(
            Controller* controller,
            Vfd*        vfd,
            UINT8       dispIndex,
            UINT32      rndNum
        );

        static void runSymbols(
            Controller* controller,
            Vfd*        vfd,
            UINT8       dispIndex,
            UINT32      rndNum
        );

    private:

        static bool  s_runBackground;
        static bool  s_debug;
};

#endif
