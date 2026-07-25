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
#include "TestUtils.h"
#include "Symbol.h"
#include "Bar.h"
#include "NumberList.h"

//
// Source: https://github.com/mpflaga/Arduino-MemoryFree, Commit Hash: 0083982
// Unzip To: C:\Users\<user>>\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\libraries\MemoryFree
//
#include <MemoryFree.h>


void SegOn::onSelect(
    Controller* controller
)
{
    IDisplay* uutDisplay = controller->uutVfd->display;

    uutDisplay->setAllSegmentsOn();
};

void PinOn::onSelect(
    Controller* controller
)
{
    IDisplay* uutDisplay = controller->uutVfd->display;

    uutDisplay->clear();

    //
    // Only applicable to the ShiftRegister implementation.
    // The integrated bit map driver IC's don't have pin control.
    //
    if (controller->isShiftRegister)
    {
        ShiftRegisterDisplay *shiftRegisterDisplay = (ShiftRegisterDisplay *) uutDisplay;

        shiftRegisterDisplay->setAllPins(true);
    }
    else
    {
        controller->stdOut->printf("Unavailable");
    }
};

void Manufacturer::onSelect(
    Controller* controller
)
{
    controller->uutVfd->display->clear();

    Properties* p_properties;

    controller->uutVfd->layout->getProperties(&p_properties);

    const UINT8* p_string = pgm_read_ptr(&p_properties->manufacturer);

    controller->stdOut->print_P(controller->stdOutVfd, 
                                controller->stdOutRegionId,
                                p_string);
};

void Manufacturer::onNextShortPress(
    Controller* controller
)
{
    Properties* p_properties;

    controller->uutVfd->layout->getProperties(&p_properties);

    const UINT8* p_string = pgm_read_ptr(&p_properties->model);

    controller->stdOut->printf("\f");

    controller->stdOut->print_P(controller->stdOutVfd, 
                                controller->stdOutRegionId,
                                p_string);
};

void Performance::onNextShortPress(
    Controller* controller
)
{
    //
    // Only applicable to the ShiftRegister implementation.
    // The integrated bit map driver IC's perform the scan.
    //
    if (controller->isShiftRegister)
    {
        controller->stdOut->printf("\r%4.4d uS", controller->sys.sr.scan->getScanTimeInUs());
    }
    else
    {
        controller->stdOut->printf("Unavailable");
    }
};

void Memory::onNextShortPress(
    Controller* controller
)
{
    controller->stdOut->printf("\r%4.4d Bytes", freeMemory());
};


UCHAR TestAscii::s_currentChar;

void TestAscii::onSelect(
    Controller* controller
)
{
    controller->uutVfd->display->clear();

    s_currentChar = 0x20;

    controller->stdOut->printf(controller->uutVfd,
                               controller->uutRegionId,
                               "\f");
};

void TestAscii::onNextShortPress(
    Controller* controller
)
{
    VfdStdOut* stdOut = controller->stdOut;

    if (++s_currentChar >= 127)
    {
        s_currentChar = 0x20;
    }

    stdOut->printf("\r%2.2d %c", s_currentChar, s_currentChar);

    // Print to all the available displays, up to 16 (8 ports and 2 per port max)
    for (UINT8 disp = 0 ; disp < 16 ; disp++)
    {
        Vfd *iVfd = &controller->vfd[disp / 2][disp % 2];

        // If there is nothing in this slot, or it's the AppEngine menu, or it's the app StdOut, skip it
        if ((iVfd->display == NULL) || (iVfd == controller->appEngineVfd) || (iVfd == controller->stdOutVfd))
        {
            continue;
        }

        // Print to the first 4 regions on those displays for debug
        for (UINT8 region = 0 ; region < 4 ; region++)
        {
            stdOut->printf(iVfd, region, "\r");

            // Print a whole row to help debug differing digit encodings
            for (UINT8 row = 0 ; row < 16 ; row++)
            {
                stdOut->printf(iVfd, region, "%c", s_currentChar);
            }
        }
    }
};


UINT8 TestSymbol::s_groupIndex;

void TestSymbol::onSelect(
    Controller* controller
)
{
    Vfd* uutVfd = controller->uutVfd;

    uutVfd->display->clear();

    s_groupIndex = 0;

    // Blind symbol set to test out this API, at least 1 activated for each supported display.
    Symbol::set(uutVfd, 0, SymPlayForward, true);
    Symbol::set(uutVfd, 0, SymPause,       true);
    Symbol::set(uutVfd, 1, SymPause,       true);
    Symbol::set(uutVfd, 0, SymText_CD,     true);
    Symbol::set(uutVfd, 0, SymText_AUTO,   true);
};

void TestSymbol::onNextShortPress(
    Controller* controller
)
{
    VfdStdOut* stdOut = controller->stdOut;
    Vfd* uutVfd = controller->uutVfd;

    if (s_groupIndex == 0)
    {
        uutVfd->display->clear();
    }

    Sym sym = SymNone;
    UINT8 instance = 0;

    bool success = Symbol::set(uutVfd, s_groupIndex, true, &sym, &instance);

    if (success)
    {
        stdOut->printf("\r%1.1d %3.3d", instance, (int) sym);

        s_groupIndex++;
    }
    else
    {
        s_groupIndex = 0;
    }
};


UINT8 TestBar::s_currentPosition;
bool  TestBar::s_showScale;

void TestBar::onSelect(
    Controller* controller
)
{
    controller->uutVfd->display->clear();

    s_currentPosition = 0;
    s_showScale = false;
};

void TestBar::onNextShortPress(
    Controller* controller
)
{
    controller->stdOut->printf("\r%2.2d %c", s_currentPosition, (s_showScale ? 'S' : ' '));

    // The Koss WMS1100 has 2 regions and up to 3 bars per region.
    for (UINT8 r = 0 ; r < 2 ; r++)
    {
        for (UINT8 i = 0 ; i < 3 ; i++)
        {
            Bar::set(controller->uutVfd, r, i, s_showScale, (s_currentPosition + r + i));
        }
    }

    if (++s_currentPosition >= (ARRAYSIZE(SegmentGroupBar::pinS) + 2))
    {
        s_currentPosition = 0;
        s_showScale = !s_showScale;
    }
};

UINT8 TestNumberList::s_currentNumber;
bool  TestNumberList::s_displayAllTo;

void TestNumberList::onSelect(
    Controller* controller
)
{
    controller->uutVfd->display->clear();

    s_currentNumber = 0;
    s_displayAllTo = false;
};

void TestNumberList::onNextShortPress(
    Controller* controller
)
{
    controller->stdOut->printf("\r%2.2d %c", s_currentNumber, (s_displayAllTo ? 'A' : '1'));

    NumberList::set(controller->uutVfd, 0, 0, s_displayAllTo, s_currentNumber);

    if (++s_currentNumber >= (ARRAYSIZE(SegmentGroupNumberList::grid[0].list) + 2))
    {
        s_currentNumber = 0;
        s_displayAllTo = !s_displayAllTo;
    }
};
