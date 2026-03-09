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
#include "Symbol.h"


// Correlated setting for number of segments in the segment group for this graphic symbol to display.
static const UINT8 s_numSegments = ARRAYSIZE(SegmentGroupGraphicSymbol::pinS);


bool Symbol::set(
    Vfd  *vfd,
    UINT8 instance,
    Sym   sym,
    bool  on)
{
    UINT8 numEntriesSegmentGroupSymbol;
    const SegmentGroupSymbol *p_segmentGroupSymbol;
    bool success;

    success = vfd->layout->getSegmentGroupSymbol(
        &p_segmentGroupSymbol,
        &numEntriesSegmentGroupSymbol);

    if (!success)
    {
        return false;
    }

    UINT8 pinG = 0;
    UINT8 pinS = 0;

    for (UINT8 i = 0 ; i < numEntriesSegmentGroupSymbol ; i++)
    {
        Sym curSym = pgm_read_byte_near(&p_segmentGroupSymbol[i].sym);
        UINT8 curInstance = pgm_read_byte_near(&p_segmentGroupSymbol[i].instance);

        if ((sym == curSym) && (instance == curInstance))
        {
            pinG = pgm_read_byte_near(&p_segmentGroupSymbol[i].pinG);
            pinS = pgm_read_byte_near(&p_segmentGroupSymbol[i].pinS);

            break;
        }
    }

    if ((pinG == 0) || (pinS == 0))
    {
        // We may have graphic symbols as well so try those
        return setGraphicSymbol(vfd, instance, sym, on);
    }

    return vfd->display->setSegment(pinG, pinS, on);
};


bool Symbol::set(
    Vfd   *vfd,
    UINT8  index,
    bool   on,
    Sym   *sym,
    UINT8 *instance)
{
    UINT8 numEntriesSegmentGroupSymbol;
    const SegmentGroupSymbol *p_segmentGroupSymbol;
    bool success;

    success = vfd->layout->getSegmentGroupSymbol(
        &p_segmentGroupSymbol,
        &numEntriesSegmentGroupSymbol);

    if (!success)
    {
        return false;
    }

    if (index >= numEntriesSegmentGroupSymbol)
    {
        // We may have graphic symbols as well so try those
        return setGraphicSymbol(vfd, (index - numEntriesSegmentGroupSymbol), on, sym, instance);
    }

    UINT8 pinG = pgm_read_byte_near(&p_segmentGroupSymbol[index].pinG);
    UINT8 pinS = pgm_read_byte_near(&p_segmentGroupSymbol[index].pinS);

    success = vfd->display->setSegment(pinG, pinS, on);

    if (success)
    {
        *sym = pgm_read_byte_near(&p_segmentGroupSymbol[index].sym);
        *instance = pgm_read_byte_near(&p_segmentGroupSymbol[index].instance);    
    }

    return success;
}


bool Symbol::setGraphicSymbol(
    Vfd  *vfd,
    UINT8 instance,
    Sym   sym,
    bool  on)
{
    const SegmentGroupGraphicSymbol *p_segmentGroupGraphicSymbol;
    UINT8 numEntriesSegmentGroupGraphicSymbol;
    const DisplayGroupGraphicSymbol *p_displayGroupGraphicSymbol;
    UINT8 numEntriesDisplayGroupGraphicSymbol;
    bool success;

    success = vfd->layout->getSegmentGroupGraphicSymbol(
        &p_segmentGroupGraphicSymbol,
        &numEntriesSegmentGroupGraphicSymbol,
        &p_displayGroupGraphicSymbol,
        &numEntriesDisplayGroupGraphicSymbol);

    if (!success)
    {
        return false;
    }

    UINT8 *p_on = NULL;
    SegmentGroupGraphicSymbol *p_seg = NULL;

    for (UINT8 i = 0 ; i < numEntriesDisplayGroupGraphicSymbol ; i++)
    {
        Sym curSym = pgm_read_byte_near(&p_displayGroupGraphicSymbol[i].sym);
        UINT8 curInstance = pgm_read_byte_near(&p_displayGroupGraphicSymbol[i].instance);

        if ((sym == curSym) && (instance == curInstance))
        {
            UINT8 segGroupIndex = pgm_read_byte_near(&p_displayGroupGraphicSymbol[i].segGroupIndex);

            p_on = (UINT8 *) &p_displayGroupGraphicSymbol[i].on;
            p_seg = &p_segmentGroupGraphicSymbol[segGroupIndex];

            break;
        }
    }

    if ((p_on == NULL) || (p_seg == NULL))
    {
        return false;
    }

    SegmentState segState[s_numSegments];

    UINT8  pinG = pgm_read_byte_near(&p_seg->pinG);
    UINT8* pinS = (UINT8 *) &p_seg->pinS;

    for (int s = 0; s < s_numSegments; s++)
    {
        segState[s].pinS = pgm_read_byte_near(&pinS[s]);
        segState[s].on = pgm_read_byte_near(&p_on[s]);
    }

    return vfd->display->setSegments(pinG, segState, ARRAYSIZE(segState));
};


bool Symbol::setGraphicSymbol(
    Vfd   *vfd,
    UINT8  index,
    bool   on,
    Sym   *sym,
    UINT8 *instance)
{
    const SegmentGroupGraphicSymbol *p_segmentGroupGraphicSymbol;
    UINT8 numEntriesSegmentGroupGraphicSymbol;
    const DisplayGroupGraphicSymbol *p_displayGroupGraphicSymbol;
    UINT8 numEntriesDisplayGroupGraphicSymbol;
    bool success;

    success = vfd->layout->getSegmentGroupGraphicSymbol(
        &p_segmentGroupGraphicSymbol,
        &numEntriesSegmentGroupGraphicSymbol,
        &p_displayGroupGraphicSymbol,
        &numEntriesDisplayGroupGraphicSymbol);

    if (!success || (index >= numEntriesDisplayGroupGraphicSymbol))
    {
        return false;
    }

    UINT8  segGroupIndex = pgm_read_byte_near(&p_displayGroupGraphicSymbol[index].segGroupIndex);
    UINT8* p_on = (UINT8 *) &p_displayGroupGraphicSymbol[index].on;

    SegmentGroupGraphicSymbol *p_seg = &p_segmentGroupGraphicSymbol[segGroupIndex];

    SegmentState segState[s_numSegments];

    UINT8  pinG = pgm_read_byte_near(&p_seg->pinG);
    UINT8* pinS = (UINT8 *) &p_seg->pinS;

    for (int s = 0; s < s_numSegments; s++)
    {
        segState[s].pinS = pgm_read_byte_near(&pinS[s]);
        segState[s].on = pgm_read_byte_near(&p_on[s]);
    }

    success = vfd->display->setSegments(pinG, segState, ARRAYSIZE(segState));

    if (success)
    {
        *sym = pgm_read_byte_near(&p_displayGroupGraphicSymbol[index].sym);
        *instance = pgm_read_byte_near(&p_displayGroupGraphicSymbol[index].instance);    
    }

    return success;
}
