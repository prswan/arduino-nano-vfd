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
#include "Display.h"

/* TODO

 * Grid scan controls
   - The total brightness is effectively divided accross each grid scan.
     e.g. 10 grids means 10% of total brightness results.

     - If we skip grids with no active segments, the remaining grids will display brighter.
       Can be done automatically as segments are turned on or off by ref counting the grid.

 * Efficiency optimizations
   - Using FastPin for the pin drive.
   - See also the note in the scan function about keeping the pins all on one port.
   - Theoretically, it may be possible to drive using SPI
     - However, the SPI block does not support DMA and therefore the efficiency
       saving is moving from 1-bit clocked transfers to 8-bit direct transfers.
     - There is only one SPI block, so only 1 display could be driven this way.
       - There was a related idea to use up to 4 displays per Nano with a parallel
         scan (common CLOCK, STOBE, BLANK but D0,D1,D2,D3 data pins).


 Design Notes for supporting 2 displays on 1 serial chain
 --------------------------------------------------------
 
 * Each pinout identifies the full chain length
   - e.g. 64-bits even if only 32 bits are used.
 * Each pinout defines only it's own, leaving the rest undefined.
 * The scan double buffers, OR-ing in the individual bitMap registers into a single line
 * The line is shifted out and latched as normal.
 * Each display grid line is incremented & wrapped individually
    - Treated independently, there is no loss of brightness due to missing grid lines and
      the display characteristics don't matter (e.g. how many grids or segments each has). 

*/

//
// 0.3mS per grid. Manuals suggest to use something not a multiple of mains 50Hz
// to avoid alias flickering with the filament AC.
//
// SPI @ 1MHz versus pin drive efficiency (32-bit register)
// --------------------------------------------------------
// - SPI - 340uS -> 348uS total cycle time
// - Pin - 620uS -> 624uS total cycle time
// i.e. pin drive scan period is SW limied to ~624uS minimum versus 15uS for SPI.
//
static const UINT32 s_scanPeriodInUS = 333;

Display::Display(
    IVfdPinout *vfd,
    int pinStrobe,
    int pinBlank) : m_vfd(vfd),
                    m_pinStrobe(pinStrobe),
                    m_pinBlank(pinBlank)
{
    vfd->getScanConfig(
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
    m_bitMapSizeInBytes = m_registerLenInBytes * m_numGrids;

    m_bitMap = malloc(m_bitMapSizeInBytes);

    pinMode(pinStrobe, OUTPUT);
    pinMode(pinBlank, OUTPUT);

    pinMode(MOSI, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(SS, OUTPUT);

    SPIClass::beginTransaction(m_spiSettings);

    m_nextUpdateTimeInUS = micros() + s_scanPeriodInUS;
    m_currentGridRegister = 0;

    clear();
};

Display::~Display()
{
    free(m_bitMap);
    m_bitMap = NULL;

    SPIClass::endTransaction();
};

void Display::setGrids()
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

void Display::setAllSegmentsOn()
{
    for (UINT8 pinG = 1; pinG < m_numEntriesPinMapGrid; pinG++)
    {
        for (UINT8 pinS = 1; pinS < m_numEntriesPinMapSegment; pinS++)
        {
            setSegment(pinG, pinS, true);
        }
    }
};

void Display::setAllPinsOn()
{
    memset(m_bitMap, 0xFF, m_bitMapSizeInBytes);
};

void Display::clear()
{
    memset(m_bitMap, 0, m_bitMapSizeInBytes);

    setGrids();
};

bool Display::setSegment(
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

bool Display::scan()
{
    UINT32 currentTimeInUS = micros();

    if (currentTimeInUS < m_nextUpdateTimeInUS)
    {
        return false;
    }

    m_nextUpdateTimeInUS = currentTimeInUS + s_scanPeriodInUS;

    // Blank and strobe out the previous scan data
    {
        digitalWrite(m_pinBlank, HIGH); // Blanked

        // Pulse strobe
        digitalWrite(m_pinStrobe, HIGH);
        digitalWrite(m_pinStrobe, LOW);

        digitalWrite(m_pinBlank, LOW); // Display
    }

    UINT8 reg = m_currentGridRegister * m_registerLenInBytes;

    //
    // We don't use the SPI library implementation because it clobbers
    // the input buffer by reading the input register.
    // For the shift register pin driver we don't need the read back data.
    //
    {
        void *buf = &m_bitMap[reg];
        size_t count = m_registerLenInBytes;

        uint8_t *p = (uint8_t *)buf;
        SPDR = *p++;

        while (--count > 0)
        {
            uint8_t out = *p++;
            while (!(SPSR & _BV(SPIF)))
                ;
            SPDR = out;
        }

        while (!(SPSR & _BV(SPIF)))
            ;
    }

    if (++m_currentGridRegister >= m_numGrids)
    {
        m_currentGridRegister = 0;
    }

    return true;
};
