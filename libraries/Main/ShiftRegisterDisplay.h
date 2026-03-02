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
#ifndef ShiftRegisterDisplay_h
#define ShiftRegisterDisplay_h

#include "Arduino.h"
#include "Types.h"
#include "IVfdPinout.h"
#include "IDisplay.h"

//
// VFD shift register display class.
//
class ShiftRegisterDisplay : public IDisplay
{
public:

    //
    // bitMap is supplied and owned by the caller.
    //
    ShiftRegisterDisplay(
        IVfdPinout *vfd,
        UINT8 *bitMap,
        UINT8 bitMapSizeInBytes
    );

    ~ShiftRegisterDisplay();

    // IDisplay

    void clear();

    void setAllSegmentsOn();

    bool setSegment(
        UINT8 pinG,
        UINT8 pinS,
        bool on
    );

    //
    // Set all the pins for display "d" on.
    // This is a test function to show full brightness with all girds and segments active.
    //
    void setAllPins(bool on);

    //
    // Return the current grid for the scan, incremented and wrapped around by incGrid()
    //
    const UINT8* getScanRegisterMask()
    {
        return p_registerMask;
    };

    //
    // Return the current grid for the scan, incremented and wrapped around by incGrid()
    //
    UINT8 getScanCurrentGrid()
    {
        return m_currentGrid;
    };

    //
    // Increment the grid pointer to the next register data line.
    //
    void incScanGrid();

private:
    void setGrids();

private:

    IVfdPinout *m_vfd;

    UINT8 m_numGrids;

    UINT8 m_registerLenInBits;
    UINT8 m_numEntriesPinMapGrid;
    UINT8 m_numEntriesPinMapSegment;

    const UINT8  *p_registerMask;
    const PinMap *p_pinMapGrid;
    const PinMap *p_pinMapSegment;

    UINT8 m_registerLenInBytes;

    UINT8 m_currentGrid; // 0 based.

    UINT8 *m_bitMap;
};

#endif
