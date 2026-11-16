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


// Correlated setting for number of segments in the segment group for this character to display.
static const UINT8 s_numSegments = 17;

//
// Display group for 14 segment display characters.
//
// true = segment on.
//
typedef struct _DisplayGroup14Seg
{
    UINT8 a  : 1;
    UINT8 b  : 1;
    UINT8 c  : 1;
    UINT8 d  : 1;
    UINT8 e  : 1;
    UINT8 f  : 1;
    UINT8 g1 : 1;
    UINT8 g2 : 1;
    UINT8 h  : 1;
    UINT8 i  : 1;
    UINT8 j  : 1;
    UINT8 k  : 1;
    UINT8 l  : 1;
    UINT8 m  : 1;
    UINT8 gc : 1;
    UINT8 ac : 1;
    UINT8 dc : 1;

} DisplayGroup14Seg;

static_assert(sizeof(DisplayGroup14Seg) == 3, "14-segment glyphs must use 3 bytes");

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
//   val,  a  b  c  d  e  f g1 g2  h  i  j  k  l  m gc ac dc
    {' ',  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {'*',  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {'+',  0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0},
    {'-',  0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {'/',  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0},
    {'=',  0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
    {'\\', 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0},
    {'_',  0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {'{',  1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
    {'|',  0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0},
    {'}',  1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0}
//
};

// Numbers don't use the ac & dc corner dots.
static const DisplayGroup14Seg s_displayGroup14SegNumbers[] PROGMEM =
{
//   a  b  c  d  e  f g1 g2  h  i  j  k  l  m gc
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

// Took a guess at the full map for the corner dots.
static const DisplayGroup14Seg s_displayGroup14SegLetters[] PROGMEM =
{
//   a  b  c  d  e  f g1 g2  h  i  j  k  l  m gc ac dc
    {1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1}, // A
    {1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0}, // B
    {1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // C
    {1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0}, // D
    {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1}, // E
    {1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0}, // F
    {1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // G
    {0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1}, // H
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0}, // I
    {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // J
    {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1}, // K
    {0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, // L
    {0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1}, // M
    {0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1}, // N
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // O
    {1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // P
    {1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // Q
    {1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1}, // R
    {1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // S
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0}, // T
    {0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, // U
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0}, // V
    {0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1}, // W
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1}, // X
    {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0}, // Y
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1}  // Z
//
};


bool Char14Seg::print(
    Vfd  *vfd,
    UINT8  regionId,
    UINT8  col,
    UINT8  ascii)
{
    UINT8 numEntriesSegmentGroup14Seg;
    const SegmentGroup14Seg *p_segmentGroup14Seg;
    bool success;

    success = vfd->layout->getSegmentGroup14Seg(
        regionId,
        &p_segmentGroup14Seg,
        &numEntriesSegmentGroup14Seg);

    if (!success || (col >= numEntriesSegmentGroup14Seg))
    {
        return false;
    }

    const DisplayGroup14Seg *p_on = NULL;

    // Convert all to upper case
    ascii = toupper(ascii);

    if ((ascii >= '0') && (ascii <= '9'))
    {
        UINT8 index = ascii - '0';
        p_on = &s_displayGroup14SegNumbers[index];
    }
    else if ((ascii >= 'A') && (ascii <= 'Z'))
    {
        UINT8 index = ascii - 'A';
        p_on = &s_displayGroup14SegLetters[index];
    }
    else
    {
        for (UCHAR x = 0 ; x < ARRAYSIZE(s_symbolDisplayGroup14Seg) ; x++)
        {
            UCHAR value = pgm_read_byte_near(&s_symbolDisplayGroup14Seg[x].value);

            if (ascii == value)
            {
                p_on = &s_symbolDisplayGroup14Seg[x].group;
                break;
            }
        }
    }

    // Nothing found
    if (p_on == NULL)
    {
        return false;
    }

    SegmentState segState[s_numSegments];

    SegmentGroup14Seg *p_seg = (SegmentGroup14Seg *) &p_segmentGroup14Seg[col];

    UINT8  pinG = pgm_read_byte_near(&p_seg->pinG);
    UINT8* pinS = (UINT8 *) &p_seg->pinS;

    for (UINT8 s = 0; s < s_numSegments; s++)
    {
        segState[s].pinS = pgm_read_byte_near(&pinS[s]);
    }

    {
        DisplayGroup14Seg glyph;
        memcpy_P(&glyph, p_on, sizeof(glyph));

        segState[0].on  = glyph.a;
        segState[1].on  = glyph.b;
        segState[2].on  = glyph.c;
        segState[3].on  = glyph.d;
        segState[4].on  = glyph.e;
        segState[5].on  = glyph.f;
        segState[6].on  = glyph.g1;
        segState[7].on  = glyph.g2;
        segState[8].on  = glyph.h;
        segState[9].on  = glyph.i;
        segState[10].on = glyph.j;
        segState[11].on = glyph.k;
        segState[12].on = glyph.l;
        segState[13].on = glyph.m;
        segState[14].on = glyph.gc;
        segState[15].on = glyph.ac;
        segState[16].on = glyph.dc;
    }

    return vfd->display->setSegments(pinG, segState, ARRAYSIZE(segState));
};
