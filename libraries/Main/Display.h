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
#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include "SPI.h"
#include "Types.h"
#include "IVfdPinout.h"

//
// VFD serial bitmap display driver class.
//
class Display
{
public:
    Display(
        IVfdPinout *vfd,
        int pinStrobe,
        int pinBlank);

    ~Display();

    //
    // Clear the display bitmap back to blank
    //
    void clear();

    //
    // Set all the segments of every grid scan to on.
    // This is a test function to easily see if a grid or segment pin was missed.
    //
    void setAllSegmentsOn();

    //
    // Set all the pins on.
    // This is a test function to show full brightness with all girds and segments active.
    //
    void setAllPinsOn();

    //
    // Turn on/off the segment pinS on grid pinG where the pins are the
    // display logical pins G1..Gx and S1..Sx. The function will translate
    // the logical pins to physical pins driven by the driver IC shift register.
    //
    bool setSegment(
        UINT8 pinG,
        UINT8 pinS,
        bool on);

    //
    // Update the display with the bitmap content.
    // scan should be spin-called and will return immediately if no update
    // is needed.
    //
    // The return value can be used to synchronize other operations to the start of
    // a new grid.
    // - false - No action.
    // - true  - Grid update was performed
    //
    bool scan();

private:
    void setGrids();

private:
    IVfdPinout *m_vfd;

    SPISettings m_spiSettings{1000000, MSBFIRST, SPI_MODE0};

    int m_pinStrobe;
    int m_pinBlank;

    UINT8 m_numGrids;
    UINT8 m_registerLenInBits;

    UINT8 m_numEntriesPinMapGrid;
    UINT8 m_numEntriesPinMapSegment;

    const PinMap *p_pinMapGrid;
    const PinMap *p_pinMapSegment;

    UINT8 m_registerLenInBytes;
    UINT8 m_bitMapSizeInBytes;

    UINT8 *m_bitMap;

    UINT32 m_nextUpdateTimeInUS;
    UINT8 m_currentGridRegister;
};

#endif
