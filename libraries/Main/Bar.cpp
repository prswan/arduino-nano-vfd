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
#include "Bar.h"


// Correlated etting for number of segments in the segment group.
static const UINT8 s_numSegments = ARRAYSIZE(SegmentGroupBar::pinS);


bool Bar::set(
    Vfd  *vfd,
    UINT8 regionId,
    UINT8 instance,
    bool  scale,
    UINT8 len
)
{
    UINT8 numEntriesSegmentGroupBar;
    const SegmentGroupBar *p_segmentGroupBar;
    bool success;

    success = vfd->layout->getSegmentGroupBar(
        regionId,
        &p_segmentGroupBar,
        &numEntriesSegmentGroupBar);

    if (!success || (instance >= numEntriesSegmentGroupBar))
    {
        return false;
    }

    SegmentState segState[s_numSegments];
    SegmentGroupBar *p_seg = (SegmentGroupBar *) &p_segmentGroupBar[instance];

    bool veritcal   = pgm_read_byte_near(&p_seg->vertical);
    bool seg1Symbol = pgm_read_byte_near(&p_seg->seg1Symbol);

    UINT8  pinG = pgm_read_byte_near(&p_seg->pinG);
    UINT8* pinS = (UINT8 *) &p_seg->pinS;

    for (UINT8 s = 0 ; s < s_numSegments ; s++)
    {
        segState[s].pinS = pgm_read_byte_near(&pinS[s]);
        bool on = false;

        // There is a seg 1 symbol/scale but don't display it
        if ((s == 0) && seg1Symbol && !scale)
        {
            on = false;

            // Add 1 to the length as we're skipping the first segment.
            if (len != 0)
            {
                len++;
            }
        }
        else if (s < len)
        {
            on = true;
        }
        else
        {
            on = false;
        }

        segState[s].on = on;
    }

    return vfd->display->setSegments(pinG, segState, ARRAYSIZE(segState));
};
