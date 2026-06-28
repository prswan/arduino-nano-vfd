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
#include "ShiftRegisterBitMap.h"


ShiftRegisterBitMap::ShiftRegisterBitMap(
    IVfdPinout *vfd1,
    IVfdPinout *vfd2)
{
    m_registerLenInBits = 0;
    m_maxNumGrids = 0;

    for (int d = 0 ; d < ARRAYSIZE(m_display) ; d++)
    {
        IVfdPinout *vfd;

        m_display[d] = NULL;

        if (d == 0)
        {
            vfd = vfd1;
        }
        else
        {
            vfd = vfd2;
        }

        if (vfd == NULL)
        {
            continue;
        }

        DriverType driverType;
        UINT8 *p_registerMask;
        UINT8  registerLenInBits;
        UINT8  numGrids;

        // Check dimensions parameters
        vfd->getScanConfig(
            &driverType,
            &p_registerMask,
            &registerLenInBits,
            &numGrids);

        // We need the maximum grid count for the maximal BitMap
        if (numGrids > m_maxNumGrids)
        {
            m_maxNumGrids = numGrids;
        }

        // They *should* be the same definition for each display. If not, bad things...
        if (registerLenInBits > m_registerLenInBits)
        {
            m_registerLenInBits = registerLenInBits;
        }
    }

    // TODO is to handle any display driver that is not 8-bit aligned.
    m_registerLenInBytes = m_registerLenInBits / 8;
    m_bitMapSizeInBytes = m_registerLenInBytes * m_maxNumGrids;

    m_bitMap = malloc(m_bitMapSizeInBytes);
    memset(m_bitMap, 0, m_bitMapSizeInBytes);

    // Construct the display objects
    if (vfd1 != NULL)
    {
        m_display[0] = new ShiftRegisterDisplay(vfd1, m_bitMap, m_bitMapSizeInBytes);
        m_display[0]->clear();
    }

    if (vfd2 != NULL)
    {
        m_display[1] = new ShiftRegisterDisplay(vfd2, m_bitMap, m_bitMapSizeInBytes);
        m_display[1]->clear();
    }
};

ShiftRegisterBitMap::~ShiftRegisterBitMap()
{
    for (int d = 0 ; d < ARRAYSIZE(m_display) ; d++)
    {
        if (m_display[d] == NULL)
        {
            continue;
        }

        delete m_display;
        m_display[d] = NULL;
    };

    free(m_bitMap);
    m_bitMap = NULL;
};

void ShiftRegisterBitMap::writeCurrentRegisterData(
    MuxSpi *muxSpi,
    UINT8   port)
{
    UINT8  reg[ARRAYSIZE(m_display)];
    UINT8* mask[ARRAYSIZE(m_display)];

    // Cache the grid information
    for (int d = 0 ; d < ARRAYSIZE(m_display) ; d++)
    {
        if (m_display[d] == NULL)
        {
            continue;
        }

        reg[d]  = m_display[d]->getScanCurrentGrid() * m_registerLenInBytes;
        mask[d] = m_display[d]->getScanRegisterMask();
    }

    // Set the port
    muxSpi->setPort(port);

    // Compose the register and transfer byte-by-byte
    for (UINT8 byte = 0 ; byte < m_registerLenInBytes ; byte++)
    {
        UINT8 data = 0;

        for (int d = 0 ; d < ARRAYSIZE(m_display) ; d++)
        {
            if (m_display[d] == NULL)
            {
                continue;
            }

            UINT8 maskByte = pgm_read_byte_near(&(mask[d])[byte]);

            UINT8 mapByte = reg[d] + byte;

            data |= (m_bitMap[mapByte] & maskByte);
        }

        muxSpi->writeByteAsync(data);
    }

    // After all the data is is written, increment the grid pointers for the displays
    for (int d = 0 ; d < ARRAYSIZE(m_display) ; d++)
    {
        if (m_display[d] == NULL)
        {
            continue;
        }

        m_display[d]->incScanGrid();
    }
};
