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
typedef struct _DisplayGroup14Seg
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

//
// Symbols include various but not all ASCII punctuation
//
typedef struct _SymbolDisplayGroup14Seg
{
    UINT8 value;
    DisplayGroup14Seg group;

} SymbolDisplayGroup14Seg;

static const SymbolDisplayGroup14Seg s_symbolDisplayGroup14Seg[] PROGMEM =
{
//   val,  a  b  c  d  e  f g1 g2  h  i  j  k  l  m  s
    {' ',  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {'*',  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
    {'+',  0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1},
    {'-',  0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {'/',  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1},
    {'=',  0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1},
    {'\\', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1},
    {'_',  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {'{',  1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0},
    {'|',  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1},
    {'}',  1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0}
//
};

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

static const DisplayGroup14Seg s_displayGroup14SegLetters[] PROGMEM =
{
//   a  b  c  d  e  f g1 g2  h  i  j  k  l  m  s
    {1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // A
    {1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1}, // B
    {1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // C
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0}, // D
    {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // E
    {1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // F
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // G
    {0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // H
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1}, // I
    {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // J
    {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1}, // K
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // L
    {0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1}, // M
    {0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1}, // N
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // O
    {1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // P
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // Q
    {1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1}, // R
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1}, // S
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1}, // T
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // U
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1}, // V
    {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1}, // W
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1}, // X
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1}, // Y
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1}  // Z
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

void Char14Seg::clear()
{
    m_display->clear();
}

bool Char14Seg::print(
    UINT8 row,
    UINT8 col,
    UINT8 ascii)
{
    UINT8 *p_on = NULL;

    if ((row > 0) || (col >= m_numEntriesSegmentGroup14Seg))
    {
        return false;
    }

    if ((ascii >= '0') && (ascii <= '9'))
    {
        UINT8 index = ascii - '0';
        p_on = (UINT8 *) &s_displayGroup14SegNumbers[index];
    }
    else if ((ascii >= 'A') && (ascii <= 'Z'))
    {
        UINT8 index = ascii - 'A';
        p_on = (UINT8 *) &s_displayGroup14SegLetters[index];
    }
    else
    {
        for (UCHAR x = 0 ; x < ARRAYSIZE(s_symbolDisplayGroup14Seg) ; x++)
        {
            UCHAR value = pgm_read_byte_near(&s_symbolDisplayGroup14Seg[x].value);

            if (ascii == value)
            {
                p_on = (UINT8 *) &s_symbolDisplayGroup14Seg[x].group;
                break;
            }
        }
    }

    // Nothing found
    if (p_on == NULL)
    {
        return false;
    }

    SegmentMap *p_seg = (SegmentMap *)&p_segmentGroup14Seg[col];

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
