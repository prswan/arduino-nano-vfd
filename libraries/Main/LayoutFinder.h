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
#ifndef LayoutFinder_h
#define LayoutFinder_h

#include "IApp.h"
#include "Buttons.h"
#include "Display.h"
#include "ICharacter.h"

//
// Utility app that can be used to find the pin and segment pins, and
// the display elements they enable.
//
// Inputs:
//
//  Button 3 - Increment Grid
//             After the last grid pin the grid pin is reset back to 1
//  Button 2 - Increment Segment
//             After the last segment pin the segment pin is reset back to 1
//  Button 1 - 1) Clear Display
//                - Clear the display bitmap back to all OFF.
//             2) Enable All Segments
//                - Set all the segement pins in every grid scan to ON.
//             3) Test All
//                - Set all pins ON (effectively no scan, full drive)
//
class LayoutFinder : public IApp
{
    public:

        LayoutFinder(
            Buttons *buttons,
            Display *display,
            ICharacter *character // Optional, use NULL if no character print available
        );

        ~LayoutFinder() {};

        virtual void run(
            bool firstSelect
        );

    private:

        //
        // Small utility to print the 2 digit decimal valus of the current grid and segment pins
        // to row col 0,1 and col 2,3.
        //
        void printGridSeg(
        );

    private:

        Buttons    *m_buttons;
        Display    *m_display;
        ICharacter *m_character;
        bool        m_gridSelected;

        UINT8 m_grid;
        UINT8 m_seg;
};

#endif
