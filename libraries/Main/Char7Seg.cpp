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

//
// Symbols include various but not all ASCII punctuation
//
typedef struct _SymbolDisplayGroup7Seg
{
    UINT8 value;
    DisplayGroup7Seg group;

} SymbolDisplayGroup14Seg;

static const SymbolDisplayGroup14Seg s_symbolDisplayGroup7Seg[] PROGMEM =
{
//   val,  a  b  c  d  e  f  g 
    {' ',  0, 0, 0, 0, 0, 0, 0},
    {'-',  0, 0, 0, 0, 0, 0, 1},
    {'=',  0, 0, 0, 1, 0, 0, 1},
    {'_',  0, 0, 0, 1, 0, 0, 0},
// Limited choice for letters, small selection with enough for hex.
    {'A',  1, 1, 1, 0, 1, 1, 1}, // A
    {'b',  0, 0, 1, 1, 1, 1, 1}, // b
    {'C',  1, 0, 0, 1, 1, 1, 0}, // C
    {'d',  0, 1, 1, 1, 1, 0, 1}, // d
    {'E',  1, 0, 0, 1, 1, 1, 1}, // E
    {'F',  1, 0, 0, 0, 1, 1, 1}, // F
    {'H',  0, 1, 1, 0, 1, 1, 1}, // H
    {'J',  0, 1, 1, 1, 1, 0, 0}, // J
    {'L',  0, 0, 0, 1, 1, 1, 0}, // L
    {'O',  1, 1, 1, 1, 1, 1, 0}, // O
    {'P',  1, 1, 0, 0, 1, 1, 1}, // P
    {'S',  1, 0, 1, 1, 0, 1, 1}, // S
    {'U',  0, 1, 1, 1, 1, 1, 0}  // U
//
};

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


bool Char7Seg::print(
    Vfd *vfd,
    UINT8 regionId,
    UINT8 col,
    UINT8 ascii)
{
    UINT8 numEntriesSegmentGroup7Seg;
    const SegmentGroup7Seg *p_segmentGroup7Seg;
    bool success;

    success = vfd->layout->getSegmentGroup7Seg(
        regionId,
        &p_segmentGroup7Seg,
        &numEntriesSegmentGroup7Seg);

    if (!success || (col >= numEntriesSegmentGroup7Seg))
    {
        return false;
    }

    UINT8 *p_on = NULL;

    if ((ascii >= '0') && (ascii <= '9'))
    {
        UINT8 index = ascii - '0';
        p_on = (UINT8 *) &s_displayGroup7SegNumbers[index];
    }
    else
    {
        for (UCHAR x = 0 ; x < ARRAYSIZE(s_symbolDisplayGroup7Seg) ; x++)
        {
            UCHAR value = pgm_read_byte_near(&s_symbolDisplayGroup7Seg[x].value);

            // Limited choice for letters, small selection with enough for hex.
            if ((ascii == value) || (toupper(ascii) == value) || (tolower(ascii) == value))
            {
                p_on = (UINT8 *) &s_symbolDisplayGroup7Seg[x].group;
                break;
            }
        }
    }

    // Nothing found
    if (p_on == NULL)
    {
        return false;
    }

    SegmentMap *p_seg = (SegmentMap *)&p_segmentGroup7Seg[col];

    for (int s = 0; s < 7; s++)
    {
        UINT8 pinG = pgm_read_byte_near(&p_seg[s].pinG);
        UINT8 pinS = pgm_read_byte_near(&p_seg[s].pinS);
        UINT8 on = pgm_read_byte_near(&p_on[s]);

        success = vfd->display->setSegment(pinG, pinS, on);

        if (!success)
        {
            break;
        }
    }

    return true;
};
