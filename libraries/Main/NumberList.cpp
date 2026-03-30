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
#include "NumberList.h"


// Correlated setting for number of segments in the segment group.
static const UINT8 s_numGrids    = ARRAYSIZE(SegmentGroupNumberList::grid);
static const UINT8 s_numSegments = ARRAYSIZE(SegmentGroupNumberList::grid[0].list);


bool NumberList::set(
    Vfd  *vfd,
    UINT8 regionId,
    UINT8 instance,
    bool  displayTo,
    UINT8 number
)
{
    UINT8 numEntriesSegmentGroupNumberList;
    const SegmentGroupNumberList *p_segmentGroupNumberList;
    bool success;

    success = vfd->layout->getSegmentGroupNumberList(
        regionId,
        &p_segmentGroupNumberList,
        &numEntriesSegmentGroupNumberList);

    if (!success || (instance >= numEntriesSegmentGroupNumberList))
    {
        return false;
    }

    SegmentGroupNumberList *p_seg = (SegmentGroupNumberList *) &p_segmentGroupNumberList[instance];

    for (UINT8 g = 0 ; g < s_numGrids ; g++)
    {
        UINT8 pinG = pgm_read_byte_near(&p_seg->grid[g].pinG);

        if (pinG == 0)
        {
            break;
        }

        SegmentState segState[s_numSegments];
        UINT8 numSegs = s_numSegments;

        for (UINT8 s = 0 ; s < numSegs ; s++)
        {
            UINT8 value = pgm_read_byte_near(&p_seg->grid[g].list[s].value);

            segState[s].pinS = pgm_read_byte_near(&p_seg->grid[g].list[s].pinS);
            segState[s].on = false;

            if (segState[s].pinS == 0)
            {
                numSegs = s;
                break;
            }

            if (number > 0)
            {
                if (value == number)
                {
                    segState[s].on = true;
                }
                else if (displayTo && (value < number))
                {
                    segState[s].on = true;
                }
            }
        }

        success = vfd->display->setSegments(pinG, segState, numSegs);

        if (!success)
        {
            return success;
        }
    }

    return success;
};
