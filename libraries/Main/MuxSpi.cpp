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
#include "MuxSpi.h"


MuxSpi::MuxSpi(
    int pinStrobe,
    int pinBlank,
    int pinSel0,
    int pinSel1,
    int pinSel2,
    UINT8 bitOrder) : m_pinStrobe(pinStrobe),
                      m_pinBlank(pinBlank),
                      m_pinSel0(pinSel0),
                      m_pinSel1(pinSel1),
                      m_pinSel2(pinSel2)
{
    pinMode(pinStrobe, OUTPUT);
    pinMode(pinBlank, OUTPUT);

    pinMode(pinSel0, OUTPUT);
    pinMode(pinSel1, OUTPUT);
    pinMode(pinSel2, OUTPUT);

    pinMode(MOSI, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(SS, OUTPUT);

    // Small optimization to cache the port setting and skip NO-OP
    m_currentPort = 0xFF;
    setPort(0);

    SPIClass::beginTransaction(SPISettings(1000000, bitOrder, SPI_MODE0));
};

MuxSpi::~MuxSpi()
{
    SPIClass::endTransaction();
};

void MuxSpi::setPort(UINT8 port)
{
    if (port == m_currentPort)
    {
        return;
    }

    m_currentPort = port & 0x7;

    digitalWrite(m_pinSel0, ((m_currentPort & 0x1) ? HIGH : LOW));
    digitalWrite(m_pinSel1, ((m_currentPort & 0x2) ? HIGH : LOW));
    digitalWrite(m_pinSel2, ((m_currentPort & 0x4) ? HIGH : LOW));
};

void MuxSpi::writeData(
        const UINT8 *data,
        UINT8 dataLenInBytes)
{
    //
    // We don't use the SPI library implementation because it clobbers
    // the input buffer by reading the input register.
    //
    {
        void *buf = data;
        size_t count = dataLenInBytes;

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
};
