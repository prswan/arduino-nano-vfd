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
#include "LayoutFinder.h"

// Grid or Segment selected for increment
static bool s_gridSelected;

// Current grid number
static UINT8 s_grid;

// Current segment number
static UINT8 s_seg;

void LayoutFinder::onSelect(
    Controller* controller
)
{
    IDisplay* display = controller->uutVfd->display;

    s_gridSelected = false;

    s_grid = 1;
    s_seg  = 1;

    display->clear();

    display->setSegment(s_grid, s_seg, true);

    controller->stdOut->printf("\f%2.2d%2.2d", s_grid, s_seg);
};

void LayoutFinder::next(
    Controller* controller
)
{
    IDisplay* display = controller->uutVfd->display;

    display->setSegment(s_grid, s_seg, false);

    if (s_gridSelected)
    {
        s_grid++;

        if (!display->setSegment(s_grid, s_seg, true))
        {
            s_grid = 1;

            display->setSegment(s_grid, s_seg, true);
        }
    }
    else
    {
        s_seg++;

        if (!display->setSegment(s_grid, s_seg, true))
        {
            s_seg = 1;

            display->setSegment(s_grid, s_seg, true);
        }
    }

    controller->stdOut->printf("\r%2.2d%2.2d", s_grid, s_seg);
};

void LayoutFinder::onNextShortPress(
    Controller* controller
)
{
    next(controller);
};

void LayoutFinder::onNextLongPress(
    Controller* controller
)
{
    if (s_gridSelected)
    {
        s_gridSelected = false;
    }
    else
    {
        s_gridSelected = true;
    }

    next(controller);
};


