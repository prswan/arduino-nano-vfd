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
#include "Char7Seg.h"

/* TODO

 * DisplayGroup7Seg should be a bitfield to save space
   - memcpy out of PROGMEM into DisplayGroup7Seg and bit deref that.

 * Addition of reasonably displayable letters?
   - A,C,E,F,H,L,P,S,U,Y
   - b,c,d,h,o,u
   - At least the hexadecimal letters.
*/

//
// Display group for 7 segment display characters.
// Index is 0 .. 9 direct mapped to 0..9 numerals
//
// true = segment on.
//
typedef struct _DisplayGroup7Seg
{
    UINT8 a;
    UINT8 b;
    UINT8 c;
    UINT8 d;
    UINT8 e;
    UINT8 f;
    UINT8 g;

} DisplayGroup7Seg;

static const DisplayGroup7Seg s_displayGroup7SegNumbers[] PROGMEM =
    {
    //   a  b  c  d  e  f  g
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 1, 0, 1, 1, 0, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1}, // 3
        {0, 1, 1, 0, 0, 1, 1}, // 4
        {1, 0, 1, 1, 0, 1, 1}, // 5
        {1, 0, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9
                               //
};

Char7Seg::Char7Seg(
    IVfdLayout7Seg *vfd,
    Display *display) : m_vfd(vfd),
                        m_display(display)
{
    vfd->getSegmentGroup7Seg(
        0,
        &p_segmentGroup7Seg,
        &m_numEntriesSegmentGroup7Seg);
};

bool Char7Seg::print(
    UINT8 row,
    UINT8 col,
    UCHAR ascii)
{
    if ((row > 0) || (col >= m_numEntriesSegmentGroup7Seg))
    {
        return false;
    }

    if ((ascii > '9') || (ascii < '0'))
    {
        return false;
    }

    UINT8 index = ascii - '0';

    SegmentMap *p_seg = (SegmentMap *)&p_segmentGroup7Seg[col];

    UINT8 *p_on = (UINT8 *)&s_displayGroup7SegNumbers[index];

    for (int s = 0; s < 7; s++)
    {
        UINT8 pinG = pgm_read_byte_near(&p_seg[s].pinG);
        UINT8 pinS = pgm_read_byte_near(&p_seg[s].pinS);
        UINT8 on = pgm_read_byte_near(&p_on[s]);

        m_display->setSegment(pinG, pinS, on);
    }
    /*
        setSegment(&p_segmentGroup7Seg[col].a, (pgm_read_byte_near(&s_displayGroup7Seg[index].a) != 0));
        setSegment(&p_segmentGroup7Seg[col].b, (pgm_read_byte_near(&s_displayGroup7Seg[index].b) != 0));
        setSegment(&p_segmentGroup7Seg[col].c, (pgm_read_byte_near(&s_displayGroup7Seg[index].c) != 0));
        setSegment(&p_segmentGroup7Seg[col].d, (pgm_read_byte_near(&s_displayGroup7Seg[index].d) != 0));
        setSegment(&p_segmentGroup7Seg[col].e, (pgm_read_byte_near(&s_displayGroup7Seg[index].e) != 0));
        setSegment(&p_segmentGroup7Seg[col].f, (pgm_read_byte_near(&s_displayGroup7Seg[index].f) != 0));
        setSegment(&p_segmentGroup7Seg[col].g, (pgm_read_byte_near(&s_displayGroup7Seg[index].g) != 0));
    */
    return true;
};
