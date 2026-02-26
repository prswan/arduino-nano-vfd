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
// SPI @ 1MHz versus pin drive efficiency (32-bit register)
// --------------------------------------------------------
// - SPI - 340uS -> 348uS total cycle time
// - Pin - 620uS -> 624uS total cycle time
// i.e. pin drive scan period is SW limied to ~624uS minimum versus 15uS for SPI.
//
static const UINT32 s_scanPeriodInUS = 333;

ShiftRegisterScan::ShiftRegisterScan(
    ShiftRegisterBitMap *bitMap,
    int pinStrobe,
    int pinBlank) : m_bitMap(bitMap),
                    m_pinStrobe(pinStrobe),
                    m_pinBlank(pinBlank)
{
    m_registerLenInBytes = bitMap->getRegisterLenInBytes();

    m_register = malloc(m_registerLenInBytes);

    pinMode(pinStrobe, OUTPUT);
    pinMode(pinBlank, OUTPUT);

    pinMode(MOSI, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(SS, OUTPUT);

    SPIClass::beginTransaction(m_spiSettings);

    m_nextUpdateTimeInUS = micros() + s_scanPeriodInUS;
};

ShiftRegisterScan::~ShiftRegisterScan()
{
    free(m_register);
    m_register = NULL;

    SPIClass::endTransaction();
};

bool ShiftRegisterScan::run()
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

    m_bitMap->getCurrentRegisterData(m_register, m_registerLenInBytes);

    //
    // We don't use the SPI library implementation because it clobbers
    // the input buffer by reading the input register.
    // For the shift register pin driver we don't need the read back data.
    //
    {
        void *buf = m_register;
        size_t count = m_registerLenInBytes;

        uint8_t *p = (uint8_t *)buf;
        SPDR = *p++;

        while (--count > 0)
        {
            uint8_t out = *p++;
            while (!(SPSR & _BV(SPIF)));

            SPDR = out;
        }

        while (!(SPSR & _BV(SPIF)));
    }

    m_bitMap->incGrids();

    return true;
};
