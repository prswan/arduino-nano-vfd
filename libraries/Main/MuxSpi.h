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
#ifndef MuxSpi_h
#define MuxSpi_h

#include "Arduino.h"
#include "SPI.h"
#include "Types.h"

//
// Wrapper for the Arduino SPI port and the additional control pins
// for the display and multiplexor.
//
// bitOrder is pramaterized because:
// - Universal shift register is MSB first
// - PT631x driver IC is LSB first.
//
class MuxSpi
{
public:
    MuxSpi(UINT8 bitOrder);

    ~MuxSpi();

    //
    // Set the strobe pin to the supplied value.
    //
    void setStrobe(
        bool hi
    )
    {
        // Wait for any pending SPI transfers to complete
        while (!(SPSR & _BV(SPIF)));

        PORTB = (PORTB & ~0x01) | (hi ? 0x01 : 0x00);
    };

    //
    // Set the blank pin to the supplied value.
    //
    void setBlank(
        bool hi
    )
    {
        PORTB = (PORTB & ~0x02) | (hi ? 0x02 : 0x00);
    };

    //
    // Set the SPI multiplexor port to use via SEL0,1,2.
    // "port" is 0 to 7 for physical ports 1 to 8.
    //
    void setPort(
        UINT8 port
    );

    //
    // Write "dataLenInBytes" amount of "data" out of the SPI port.
    //
    void writeData(
        UINT8 port,
        const UINT8 *data,
        UINT8 dataLenInBytes
    );

    // Write a byte of data to the current port
    void writeByteAsync(
        UINT8 data
    )
    {
        // Wait for any pending transfer to finish
        while (!(SPSR & _BV(SPIF)));

        // Output the next byte
        SPDR = data;
    };

private:

    UINT8 m_currentPort;
};

#endif
