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
#include "DriverICDisplay.h"


DriverICDisplay::DriverICDisplay(
    IVfdPinout *vfd,
    IDriverIC *idic)
{
    m_vfd = vfd;
    m_idic = idic;

    // Cache the display information we need to manage it.
    vfd->getScanConfig(
        &p_registerMask,
        &m_registerLenInBits,
        &m_numGrids);

    vfd->getPinMapGrid(
        &p_pinMapGrid,
        &m_numEntriesPinMapGrid);

    vfd->getPinMapSegment(
        &p_pinMapSegment,
        &m_numEntriesPinMapSegment);

    m_idic->setDisplayMode(m_numGrids, (m_numEntriesPinMapSegment - 1));

    // TODO is to handle any display driver that is not 8-bit aligned.
    m_registerLenInBytes = m_registerLenInBits / 8;
    m_bitMapSizeInBytes = m_registerLenInBytes * m_numGrids;

    m_bitMap = malloc(m_bitMapSizeInBytes);

    clear();
};


DriverICDisplay::~DriverICDisplay()
{
    free(m_bitMap);
    m_bitMap = NULL;
};


void DriverICDisplay::clear()
{
    memset(m_bitMap, 0x00, m_bitMapSizeInBytes);

    for (UINT8 gridAddress = 0; gridAddress < (m_numEntriesPinMapGrid - 1); gridAddress++)
    {
        m_idic->write(gridAddress, &m_bitMap[gridAddress * m_registerLenInBytes], m_registerLenInBytes);
    }
};


void DriverICDisplay::setAllSegmentsOn()
{
    memset(m_bitMap, 0xFF, m_bitMapSizeInBytes);

    for (UINT8 gridAddress = 0; gridAddress < (m_numEntriesPinMapGrid - 1); gridAddress++)
    {
        m_idic->write(gridAddress, &m_bitMap[gridAddress * m_registerLenInBytes], m_registerLenInBytes);
    }
};


bool DriverICDisplay::setSegment(
    UINT8 pinG,
    UINT8 pinS,
    bool on)
{
    SegmentState segState = {pinS, on};

    return setSegments(pinG, &segState, 1);
};


bool DriverICDisplay::setSegments(
    UINT8 pinG,
    SegmentState *segState,
    UINT8 segStateLen)
{
    if (pinG >= m_numEntriesPinMapGrid)
    {
        return false;
    }

    UINT8 gridAddress = pinG - 1;
    UINT8 reg = gridAddress * m_registerLenInBytes;

    for (int i = 0 ; i < segStateLen ; i++)
    {
        UINT8 pinS = segState[i].pinS;
        bool on = segState[i].on;

        if (pinS >= m_numEntriesPinMapSegment)
        {
            return false;
        }

        // Legal to skip missing segments.
        if (pinS != 0)
        {
            UINT8 bitS = pgm_read_byte_near(&p_pinMapSegment[pinS].bit);

            // Set shift out first
            UINT8 mapByte = reg + ((m_registerLenInBytes - 1) - (bitS / 8));
            UINT8 mapBit = (bitS % 8);

            if (on)
            {
                m_bitMap[mapByte] |= (1 << mapBit);
            }
            else
            {
                m_bitMap[mapByte] &= ~(1 << mapBit);
            }
        }
    }

    m_idic->write(gridAddress, &m_bitMap[reg], m_registerLenInBytes);

    return true;
};
