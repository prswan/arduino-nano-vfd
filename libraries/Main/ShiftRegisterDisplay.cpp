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
#include "ShiftRegisterDisplay.h"


ShiftRegisterDisplay::ShiftRegisterDisplay(
    IVfdPinout *vfd,
    UINT8 *bitMap,
    UINT8 bitMapSizeInBytes)
{
    m_vfd = vfd;
    m_bitMap = bitMap;

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

    // TODO is to handle any display driver that is not 8-bit aligned.
    m_registerLenInBytes = m_registerLenInBits / 8;

    // If there is a misconfig then stop here.
    if ((m_registerLenInBytes * m_numGrids) > bitMapSizeInBytes)
    {
        // Freeze here
        while(1);
    }

    // 0 based counter for the grid scan.
    m_currentGrid = 0;
};


ShiftRegisterDisplay::~ShiftRegisterDisplay()
{
};


void ShiftRegisterDisplay::setGrids()
{
    for (UINT8 pinG = 1; pinG <= m_numGrids; pinG++)
    {
        UINT8 bitG = pgm_read_byte_near(&p_pinMapGrid[pinG].bit);
        UINT8 reg = (pinG - 1) * m_registerLenInBytes;

        // Set shift out first
        UINT8 mapByte = reg + ((m_registerLenInBytes - 1) - (bitG / 8));
        UINT8 mapBit = (bitG % 8);

        m_bitMap[mapByte] |= (1 << mapBit);
    }
};


void ShiftRegisterDisplay::setAllSegmentsOn()
{
    for (UINT8 pinG = 1; pinG < m_numEntriesPinMapGrid; pinG++)
    {
        for (UINT8 pinS = 1; pinS < m_numEntriesPinMapSegment; pinS++)
        {
            setSegment(pinG, pinS, true);
        }
    }
};


void ShiftRegisterDisplay::setAllPins(
    bool on)
{
    for (UINT8 grid = 0; grid < m_numGrids; grid++)
    {
        UINT8 reg = grid * m_registerLenInBytes;

        //
        // We'll use the mask for this as it's quicker. 
        // We can also check we got the mask correct. 
        //
        for (UINT8 byte = 0 ; byte < m_registerLenInBytes ; byte++)
        {
            UINT8 mapByte = reg + byte;
            UINT8 maskByte = pgm_read_byte_near(&p_registerMask[byte]);

            if (on)
            {
                m_bitMap[mapByte] |= maskByte;
            }
            else
            {
                m_bitMap[mapByte] &= ~maskByte;
            } 
        }
    }
};


void ShiftRegisterDisplay::clear()
{
    setAllPins(false);
    setGrids();
};


bool ShiftRegisterDisplay::setSegment(
    UINT8 pinG,
    UINT8 pinS,
    bool on)
{
    if ((pinG >= m_numEntriesPinMapGrid) || (pinS >= m_numEntriesPinMapSegment))
    {
        return false;
    }

    UINT8 bitS = pgm_read_byte_near(&p_pinMapSegment[pinS].bit);
    UINT8 reg = (pinG - 1) * m_registerLenInBytes;

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

    return true;
};


void ShiftRegisterDisplay::incScanGrid()
{
    if (++m_currentGrid >= m_numGrids)
    {
        m_currentGrid = 0;
    }
};