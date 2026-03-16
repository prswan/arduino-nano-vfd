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
#include "PT631xDriverIC.h"


PT631xDriverIC::PT631xDriverIC(
    MuxSpi *muxSpi) : m_muxSpi(muxSpi)
{
    // Strobe is active low so set on/high to start disabled.
    muxSpi->setStrobe(true);
};


bool PT631xDriverIC::setDisplayMode(
    UINT8 port,
    UINT8 numGrids,
    UINT8 numSegments)
{
    // TODO: The encoding is diffrerent for PT6311.

    if ((numGrids < 4) || (numGrids > 12))
    {
        return false;
    }

    UINT8 displayModeSetting = numGrids - 4;

    // Send display mode setting command
    writeCommandData(port, displayModeSetting, NULL, 0);

    // Send display control command, ON with full brightness
    writeCommandData(port, (0x80 | 0x0F), NULL, 0);

    return true;
};


bool PT631xDriverIC::write(
    UINT8 port,
    UINT8 gridAddress,
    const UINT8 *segData,
    UINT8 segDataLenInBytes)
{
    // Send data setting command
    writeCommandData(port, 0x40, NULL, 0);

    // Up to 24-bits of segment, 8 bytes.
    UINT8 address = (gridAddress * 3) & 0x3F;

    // Send address & data command, auto increment.
    writeCommandData(port, (0xC0 | address), segData, segDataLenInBytes);

    return true;
};


void PT631xDriverIC::writeCommandData(
    UINT8 port,
    UINT8 command,
    const UINT8 *data,
    UINT8 dataLenInBytes)
{
    // Activate chip select
    m_muxSpi->setStrobe(false);

    // Send command
    m_muxSpi->writeData(port, &command, 1);

    if ((data != NULL) && (dataLenInBytes != 0))
    {
        // Send data
        m_muxSpi->writeData(port, data, dataLenInBytes);
    }

    // Clear chip select
    m_muxSpi->setStrobe(true);
};
