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

LayoutFinder::LayoutFinder(
    Buttons *buttons,
    Display *display,
    ICharacter *character) : m_buttons(buttons),
                             m_display(display),
                             m_character(character)
{
    m_grid = 1;
    m_seg = 1;
};

void LayoutFinder::printGridSeg()
{
    if (m_character == NULL)
    {
        return;
    }

    m_character->print(0, 0, '0' + (m_grid / 10));
    m_character->print(0, 1, '0' + (m_grid % 10));
    m_character->print(0, 2, '0' + (m_seg / 10));
    m_character->print(0, 3, '0' + (m_seg % 10));
}

void LayoutFinder::run(
    bool firstSelect
)
{
    if (firstSelect)
    {
        m_grid = 1;
        m_seg = 1;

        m_display->clear();

        m_display->setSegment(m_grid, m_seg, true);

        printGridSeg();
    }

    // Increment grid
    if (m_buttons->isB2Pressed())
    {
        m_display->setSegment(m_grid, m_seg, false);

        m_grid++;

        if (!m_display->setSegment(m_grid, m_seg, true))
        {
            m_grid = 1;

            m_display->setSegment(m_grid, m_seg, true);
        }

        printGridSeg();
    }

    // Increment seg
    if (m_buttons->isB3Pressed())
    {
        m_display->setSegment(m_grid, m_seg, false);

        m_seg++;

        if (!m_display->setSegment(m_grid, m_seg, true))
        {
            m_seg = 1;

            m_display->setSegment(m_grid, m_seg, true);
        }

        printGridSeg();
    }
};
