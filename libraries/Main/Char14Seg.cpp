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
#include "Char14Seg.h"

//
// Display group for 14 segment display characters.
//
// true = segment on.
//
typedef struct _DisplaytGroup14Seg
{
    UINT8 a;
    UINT8 b;
    UINT8 c;
    UINT8 d;
    UINT8 e;
    UINT8 f;
    UINT8 g1;
    UINT8 g2;
    UINT8 h;
    UINT8 i;
    UINT8 j;
    UINT8 k;
    UINT8 l;
    UINT8 m;
    UINT8 s;

} DisplayGroup14Seg;

static const DisplayGroup14Seg s_displayGroup14SegNumbers[] PROGMEM =
{
//   a  b  c  d  e  f g1 g2  h  i  j  k  l  m  s
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 0 - same as 7-seg
    {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 1 - same as 7-seg
    {1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // 2 - same as 7-seg
    {1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // 3 - same as 7-seg
    {0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // 4 - same as 7-seg
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // 5 - same as 7-seg
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // 6 - same as 7-seg
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // 7 - same as 7-seg
    {1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // 8 - same as 7-seg
    {1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}  // 9 - same as 7-seg
//
};

Char14Seg::Char14Seg(
    IVfdLayout14Seg *vfd,
    Display *display) : m_vfd(vfd),
                        m_display(display)
{
    vfd->getSegmentGroup14Seg(
        0,
        &p_segmentGroup14Seg,
        &m_numEntriesSegmentGroup14Seg);
};

bool Char14Seg::print(
    UINT8 row,
    UINT8 col,
    UCHAR ascii)
{
    if ((row > 0) || (col >= m_numEntriesSegmentGroup14Seg))
    {
        return false;
    }

    if ((ascii > '9') || (ascii < '0'))
    {
        return false;
    }

    UINT8 index = ascii - '0';

    SegmentMap *p_seg = (SegmentMap *)&p_segmentGroup14Seg[col];

    UINT8 *p_on = (UINT8 *)&s_displayGroup14SegNumbers[index];

    for (int s = 0; s < 15; s++)
    {
        UINT8 pinG = pgm_read_byte_near(&p_seg[s].pinG);
        UINT8 pinS = pgm_read_byte_near(&p_seg[s].pinS);
        UINT8 on = pgm_read_byte_near(&p_on[s]);

        // Check for a defined segment, this accounts for the optional "s" centre dot.
        if (pinS != 0)
        {
            m_display->setSegment(pinG, pinS, on);
        }
    }

    return true;
};
