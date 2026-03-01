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
#ifndef Controller_h
#define Controller_h

#include "Types.h"
#include "IVfdPinout.h"
#include "IVfdLayout.h"
#include "IDisplay.h"
#include "ShiftRegisterBitMap.h"
#include "ShiftRegisterScan.h"
#include "Buttons.h"
#include "VfdStdOut.h"

//
// There can be up to 16 displays visually arranged right to left and top to bottom
// on Controller Ports 1 through 8.
// Unused entries are NULL.
//
// We could pass a Vfd object to printf that can then use it to call Char14Seg?
//
// printf(Vfd *vfd, row, col, const UINT8 *format, ...)
// -> Get the VfdLayoutMap for the supplied Vfd
// -> Parse it to find where this print should be directed
//    the row/col coordinates MUST map to the start of a layout region
//     and MUST be a character region type,
//     and the print will end at the end of the layout region.
// -> call ICharacter->print(IVfdLayout *layout, IDisplay *display, row, col, ascii)
//
// Port 1: vfd[0][0], vfd[0][1]  => bitMap[0]
// Port 2: vfd[1][0], vfd[1][1]  => bitMap[1]
// ...
// Port 8: vfd[7][0], vfd[7][1]  => bitMap[7]
//
typedef struct _Controller
{
    Vfd vfd[8][2];

    ShiftRegisterBitMap* bitMap[8];
    ShiftRegisterScan*   scan;

    Buttons* buttons;

    //
    // A small cheat to specify where to find a primary output.
    //
    // e.g. Vfd[port][display] in character region regionId. 
    //
    struct {

        UINT8 port;
        UINT8 display;
        UINT8 regionId;

    } primary;

    // 
    // VfdStdOut for the character implementations.
    //
    RegionSubTypeCharMap regionSubTypeMap[2];

    Vfd  *stdOutVfd;
    UINT8 stdOutRegionId;

    // Unit Under Test VFD for bring-up and layout.
    Vfd  *uutVfd;
    UINT8 uutRegionId;

} Controller;

#endif
