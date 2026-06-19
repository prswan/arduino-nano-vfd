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

//
// This is used in the critical performance path & ISR and
// the built-in Arduino pin functions are very slow.
// The implementation is hard coded for the Ardino Nano
// and Controller V1.00 PCB pinout.
//
// When the digitalWrites for Strobe & Blank were removed, scan time
// was reduced from 280uS to 260us, a saving of 20uS.
//
#define CONTROLLER_PIN_SEL0   (5)  // PD5
#define CONTROLLER_PIN_SEL1   (6)  // PD6
#define CONTROLLER_PIN_SEL2   (7)  // PD7

#define CONTROLLER_PIN_STROBE (8)  // PB0 - Rising edge clocked
#define CONTROLLER_PIN_BLANK  (9)  // PB1 - Hi == All outputs disabled
//


MuxSpi::MuxSpi(UINT8 bitOrder)
{
    pinMode(CONTROLLER_PIN_STROBE, OUTPUT);
    pinMode(CONTROLLER_PIN_BLANK, OUTPUT);

    pinMode(CONTROLLER_PIN_SEL0, OUTPUT);
    pinMode(CONTROLLER_PIN_SEL1, OUTPUT);
    pinMode(CONTROLLER_PIN_SEL2, OUTPUT);

    pinMode(MOSI, OUTPUT);
    pinMode(SCK, OUTPUT);
    pinMode(SS, OUTPUT);

    // Small optimization to cache the port setting and skip NO-OP
    m_currentPort = 0xFF;
    setPort(0);

    //
    // Mode 3: CLK Rising Edge data latch, CLK idle state high.
    // This is need to esnure that there is no spurious CLK when the
    // port mux is changed because the port mux is idle high.
    //
    SPIClass::beginTransaction(SPISettings(1000000, bitOrder, SPI_MODE3));
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

    // SEL[0..2] === [PD5..PD7]
    PORTD = (PORTD & ~(0x07 << 5)) | (m_currentPort << 5);
};

void MuxSpi::writeData(
        UINT8 port,
        const UINT8 *data,
        UINT8 dataLenInBytes)
{
    setPort(port);

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
