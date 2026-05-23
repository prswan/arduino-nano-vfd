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
#include "ShiftRegisterScan.h"


//
// 0.3mS per grid. Manuals suggest to use something not a multiple of mains 50Hz
// to avoid alias flickering with the filament AC.
//
static const UINT32 s_scanPeriodInHz = 3333;

// Keep a global copy for the ISR
static ShiftRegisterScan *s_thisScan = NULL;

/* TODO
* ShiftRegisterScan
  * Remove polling support
* ShiftRegisterBitMap
  * DONE: Remove this from the loop: UINT8 *mask = m_display[d]->getScanRegisterMask();
* TimerScan
  * Rename to Timer
  * Remove inheritance from IScan
  * Update IDIC & Shift Register recipes to both use Timer
  * Add single global Timer to Controller.h
  * Update Main.cpp to use Timer for polling
*/

ShiftRegisterScan::ShiftRegisterScan(
    MuxSpi* muxSpi,
    ShiftRegisterBitMap** bitMap,
    UINT8 numBitMaps) : m_muxSpi(muxSpi),
                        m_bitMap(bitMap),
                        m_numBitMaps(numBitMaps)
{
    m_maxRegisterLenInBytes = 0;

    // Find the largest register
    for (UINT8 i = 0 ; i < numBitMaps ; i++)
    {
        ShiftRegisterBitMap *thisBitMap = bitMap[i];

        if (thisBitMap == NULL)
        {
            continue;
        }

        UINT8 curRegLen = thisBitMap->getRegisterLenInBytes();

        if (curRegLen > m_maxRegisterLenInBytes)
        {
            m_maxRegisterLenInBytes = curRegLen;
        }
    }

    m_register = malloc(m_maxRegisterLenInBytes);

    muxSpi->setBlank(true);
    muxSpi->setStrobe(false);

    // Setup a timer ISR for the scan
    {
        s_thisScan = this;

        // Stop interrupts while configuring
        cli(); 

        // Reset Timer 1 Control Registers
        TCCR1A = 0;
        TCCR1B = 0;
        TCNT1  = 0; // Initialize counter to 0

        // Set compare match register frequency based on 16MHz clock
        // Formula: (16,000,000 / (prescaler * frequency)) - 1
        // Using 256 prescaler for 1Hz: (16,000,000 / (256 * 1)) - 1 = 62499
        OCR1A = (16000000 / (256 * s_scanPeriodInHz)) - 1;

        // Set CTC (Clear Timer on Compare Match) mode
        TCCR1B |= (1 << WGM12);

        // Set prescaler to 256
        TCCR1B |= (1 << CS12);

        // Enable timer compare interrupt
        TIMSK1 |= (1 << OCIE1A);

        // Enable interrupts
        sei();
    }
};


ShiftRegisterScan::~ShiftRegisterScan()
{
    free(m_register);
    m_register = NULL;
};


void ShiftRegisterScan::scan()
{
    // Blank & strobe out the previous scan data
    {
        m_muxSpi->setBlank(true);

        // Pulse strobe
        m_muxSpi->setStrobe(true);
        m_muxSpi->setStrobe(false);

        m_muxSpi->setBlank(false);
    }

    for (UINT8 i = 0 ; i < m_numBitMaps ; i++)
    {
        ShiftRegisterBitMap *thisBitMap = m_bitMap[i];

        if (thisBitMap == NULL)
        {
            continue;
        }

        UINT8 curRegLen = thisBitMap->getRegisterLenInBytes();

        thisBitMap->getCurrentRegisterData(m_register, curRegLen);

        m_muxSpi->writeData(i, m_register, curRegLen);

        thisBitMap->incGrids();
    }
};


ISR(TIMER1_COMPA_vect)
{
    s_thisScan->scan();
}