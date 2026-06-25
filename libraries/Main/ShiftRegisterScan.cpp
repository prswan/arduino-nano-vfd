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
// 450uS per grid.
// Manuals suggest to use something not a multiple of mains 50Hz
// to avoid alias flickering with the filament AC.
//
static const UINT32 s_scanPeriodInHz = 2222;

// Keep a global copy for the ISR
static ShiftRegisterScan *s_thisScan = NULL;

/*
 Performance Considerations
 --------------------------
 1 Shift Register , 2 Displays : DVP-NS725 + DVD-RV32 (64-bit)                     : 156uS
 2 Shift Registers, 2 Displays : DVP-NS725 (64-bit) + KR-V77R (96-bit)             : 276uS
 2 Shift Registers, 3 Displays : DVD-RV32 + DVP-NS725 (64-bit) + KR-V77R (96-bit)  : 280uS
  - now seeing significant visible foreground slowdown.
  - 3333 Hz === 300uS per grid so we've reached a limit
  - 2222 Hz === 450uS per grid and the foreground slowdown is gone.
  - 1111 Hz === 900uS per grid but the 13 grid DVD-RV32 has visible flicker

  Moving to 450uS for now, but further performance analsyis needed.

  Given the limited impact of adding a display versus a shift register, the main bottleneck
  is the shift register.

  - At 1MHz SPI clock, 96-bits would take 1uS x 96 == 96uS, consistent with the measurements above.
  - The lack of DMA for more than a byte at a time is a problem.
  - According to the SN75518 datasheet, CLK is 1MHz at 4.5V Vcc2 or 5MHz at 10V-15V Vcc2.
    - but Vih at 12V is ~9.5V. Vil is still 0.8V.
  - A quick test using 2MHz SPI clock with 2 shift registers and 3 displays : 200uS
    - and there were no visible artifacts indicating an issue at 2MHz.
    - 4MHz SPI clock : Artifacts on KR-V77R, perf 160uS, UCN5818 seems OK (datasheet Fclk max is 3.3 MHz)

  Ideas
  -----
   1) 2MHz SPI clock would give a maximum total SPI cost of 96 x 8 x 500ns == 384uS.
   2) Set the grid scan time between 450uS and perceptable flicker (900uS)
   3) Interleave the SPI transfers with bitmap composition, maybe up to 28uS per display to save.
      - Send a byte, calculate the next byte, wait for transfer, send the next byte.
      ** OR **
      - Batch per display, calculate register d+1 interleaved with the transfer of register d.
*/

ShiftRegisterScan::ShiftRegisterScan(
    MuxSpi* muxSpi,
    ShiftRegisterBitMap** bitMap,
    UINT8 numBitMaps) : m_muxSpi(muxSpi),
                        m_bitMap(bitMap),
                        m_numBitMaps(numBitMaps)
{
    m_maxRegisterLenInBytes = 0;
    m_scanTimeInUs = 0;

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
    static UINT32 s_entryScanTimeStampInUs;

    if (m_scanTimeInUs == 0)
    {
        s_entryScanTimeStampInUs = micros();
    }

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

    if (m_scanTimeInUs == 0)
    {
        m_scanTimeInUs = micros() - s_entryScanTimeStampInUs;
    }
};


ISR(TIMER1_COMPA_vect)
{
    s_thisScan->scan();
}