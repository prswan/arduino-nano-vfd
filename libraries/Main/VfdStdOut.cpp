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
#include "VfdStdOut.h"
//#include "cstdio.h"

// Not much in the wild that has more than 20 characters.
static const UINT8 s_bufferSize = 32;

VfdStdOut::VfdStdOut(
    ICharacter *ichar) : m_char(ichar)
{
    m_currentRow = 0;
    m_currentCol = 0;
};

bool VfdStdOut::printf(
        const UINT8 *format, 
        ...)
{
    UINT8 buffer[s_bufferSize];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
 
    bool success = true;
    for (UINT8 x = 0 ; x < sizeof(buffer) ; x++)
    {
        UINT8 ascii = buffer[x];

        // CR - carriage return, to col 0
        if (ascii == '\r')
        {
            m_currentCol = 0;
            continue;
        }

        // LF - line feed, new line
        if (ascii == '\n')
        {
            m_currentRow++;
            continue;
        }

        // FF - Form Feed, reset back to 0,0
        if (ascii == '\f')
        {
            m_currentCol = 0;
            m_currentRow = 0;
            m_char->clear();
            continue;
        }

        success = m_char->print(
            m_currentRow,
            m_currentCol,
            buffer[x]
        );

        if (!success)
            break;

        m_currentCol++;
    }

    return success;
};
