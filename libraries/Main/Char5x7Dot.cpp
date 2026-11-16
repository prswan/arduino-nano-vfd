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
#include "Char5x7Dot.h"
#include "HD44780UA02Font.h"


bool Char5x7Dot::print(
    Vfd  *vfd,
    UINT8 regionId,
    UINT8 col,
    UINT8 ascii)
{
    UINT8 numEntriesSegmentGroup5x7Dot;
    const SegmentGroup5x7Dot *p_segmentGroup5x7Dot;
    bool success = vfd->layout->getSegmentGroup5x7Dot(
        regionId,
        &p_segmentGroup5x7Dot,
        &numEntriesSegmentGroup5x7Dot);

    if (!success || (col >= numEntriesSegmentGroup5x7Dot) || (ascii < 0x10))
    {
        return false;
    }

    const SegmentGroup5x7Dot *p_seg = &p_segmentGroup5x7Dot[col];
    UINT8 pinG = pgm_read_byte_near(&p_seg->pinG);
    SegmentState segState[35];
    UINT8 fontIndex = ascii - 0x10;

    for (UINT8 column = 0; column < 5; column++)
    {
        UINT16 columnBits = pgm_read_word_near(
            &HD44780UA02Font[fontIndex][column]);

        for (UINT8 row = 0; row < 7; row++)
        {
            UINT8 dot = (column * 7) + row;

            segState[dot].pinS = pgm_read_byte_near(&p_seg->pinS[dot]);
            // The font stores the seven rows in bits 1 through 7, top to bottom.
            segState[dot].on = (columnBits & (1U << (row + 1))) != 0;
        }
    }

    return vfd->display->setSegments(pinG, segState, ARRAYSIZE(segState));
};
