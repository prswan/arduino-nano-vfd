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


static UCHAR s_asciiCurrentChar = 0;

void Ascii::onSelect(
    Controller* controller
)
{
    s_asciiCurrentChar = 0x20;

    controller->stdOut->printf(controller->uutVfd,
                               controller->uutRegionId,
                               "\f");
};

void Ascii::onNextShortPress(
    Controller* controller
)
{
    VfdStdOut* stdOut = controller->stdOut;

    if (++s_asciiCurrentChar >= 127)
    {
        s_asciiCurrentChar = 0x20;
    }

    stdOut->printf("\r%2.2d %c", s_asciiCurrentChar, s_asciiCurrentChar);

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
                stdOut->printf(iVfd, region, "%c", s_asciiCurrentChar);
            }
        }
    }
};
