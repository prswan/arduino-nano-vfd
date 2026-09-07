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
#include "Demo.h"
#include "Symbol.h"
#include "Bar.h"
#include "NumberList.h"


bool  Demo::s_runBackground;
bool  Demo::s_debug;

void Demo::onSelect(
    Controller* controller
)
{
};

void Demo::onNextShortPress(
    Controller* controller
)
{
    s_runBackground = !s_runBackground;
    s_debug = true;

    controller->stdOut->printf("\f%s", (s_runBackground ? "Background" : "Off"));
};

void Demo::onNextLongPress(
    Controller* controller
)
{
    controller->appEngineVfd->display->clear();
    controller->stdOutVfd->display->clear();

    s_runBackground = true;
    s_debug = false;
};

void Demo::run(
    Controller* controller
)
{
    if (!s_runBackground)
    {
        return;
    }

    UINT32 tickCount = controller->timer->getTickCount();

    // Assign 64 time slots as 16 displays & 4 region types
    UINT8 slot = (UINT8) (tickCount % 64);

    UINT8 dispIndex = (slot / 4);
    UINT8 elemIndex = (slot % 4);
    
    if (s_debug)
    {
        controller->stdOut->printf("\r%3.3d %2.2d %1.1d ", slot, dispIndex, elemIndex);
    }

    Vfd* vfd = &controller->vfd[dispIndex / 2][dispIndex % 2];

    if (vfd->display == NULL)
    {
        return;
    }

    UINT32 rndNum = random();

    switch (elemIndex)
    {
        case 0: {
            runAscii(controller,
                     vfd,
                     dispIndex,
                     rndNum);

            break;
        }

        case 1: {
            runBar(controller,
                   vfd,
                   dispIndex,
                   rndNum);

            break;
        }

        case 2: {
            runNumberList(controller,
                          vfd,
                          dispIndex,
                          rndNum);

            break;
        }

        case 3: {
            runSymbols(controller,
                       vfd,
                       dispIndex,
                       rndNum);

            break;
        }

        default: {
            break;
        }
    }
};

void Demo::runAscii(
    Controller* controller,
    Vfd*        vfd,
    UINT8       dispIndex,
    UINT32      rndNum
)
{
    // Skip the informational VFDs if debug is on
    if (s_debug && ((vfd == controller->appEngineVfd) || (vfd == controller->stdOutVfd)))
    {
        return;
    }

    // Generate random region and character column
    UINT8 reg = (rndNum >> 12) %  4;
    UINT8 col = (rndNum >>  8) % 16;

    for (UINT8 i = 0 ; i < ARRAYSIZE(controller->regionSubTypeMap) ; i++)
    {
        UINT8 chr = (rndNum % 10);

        if (controller->regionSubTypeMap[i].ichar == NULL)
        {
            continue;
        }

        if (controller->regionSubTypeMap[i].subChar == RegionSubTypeChar14Seg)
        {
            chr = ' ' + (rndNum % (128 - ' '));
        }

        if (controller->regionSubTypeMap[i].subChar == RegionSubTypeChar7Seg)
        {
            chr = '0' + (rndNum % 10);
        }

        // regionSubTypeMap is in complexity order, so the first one to succeed sticks 
        if (controller->regionSubTypeMap[i].ichar->print(vfd, reg, col, chr))
        {
            break;
        }
    }
};

void Demo::runBar(
    Controller* controller,
    Vfd*        vfd,
    UINT8       dispIndex,
    UINT32      rndNum
)
{
    static UINT8 s_currentIndex;

    // If this is the first call, increment the index
    if (dispIndex == 0)
    {
        if (++s_currentIndex > 16)
        {
            s_currentIndex = 0;
        }
    }

    for (UINT8 i = 0 ; i < 7 ; i=i+2)
    {
        Bar::set(vfd, 0, (i + 0), false, s_currentIndex);        // forwards
        Bar::set(vfd, 0, (i + 1), false, (16 - s_currentIndex)); // backwards
    }

    Bar::set(vfd, 1, 0, false, (16 - s_currentIndex)); // backwards
};

void Demo::runNumberList(
    Controller* controller,
    Vfd*        vfd,
    UINT8       dispIndex,
    UINT32      rndNum
)
{
    static UINT8 s_currentNumber;
    static bool  s_displayAllTo;

    // If this is the first call, increment the index
    if (dispIndex == 0)
    {
        if (++s_currentNumber >= (ARRAYSIZE(SegmentGroupNumberList::grid[0].list) + 2))
        {
            s_currentNumber = 0;
            s_displayAllTo = !s_displayAllTo;
        }
    }

    NumberList::set(vfd, 0, 0, s_displayAllTo, s_currentNumber);
};

void Demo::runSymbols(
    Controller* controller,
    Vfd*        vfd,
    UINT8       dispIndex,
    UINT32      rndNum
)
{
    SegmentGroupSymbol* p_segGroup;
    UINT8 numEntries;

    // Get the number of entries to always pick a valid symbol
    bool success = vfd->layout->getSegmentGroupSymbol(&p_segGroup, &numEntries);

    // This can fail if the display has no symbols (e.g. a pure EQ display)
    if (!success)
    {
        return;
    }

    // Pick a random symbol to random on/off
    bool on = ((rndNum % 2) == 1);
    UINT8 index = (rndNum >> 1) % numEntries;

    Sym sym = SymNone;
    UINT8 instance = 0;

    Symbol::set(vfd, index, on, &sym, &instance);
};
