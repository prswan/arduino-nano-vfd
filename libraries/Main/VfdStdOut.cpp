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
    RegionSubTypeCharMap *regionTypeCharMap,
    UINT8  numRegionTypeCharMapEntries,
    Vfd   *stdOutVfd,
    UINT8  stdOutRegionId) : m_regionTypeCharMap(regionTypeCharMap),
                             m_numRegionTypeCharMapEntries(numRegionTypeCharMapEntries),
                             m_stdOutVfd(stdOutVfd),
                             m_stdOutRegionId(stdOutRegionId)
{
    m_currentCol = 0;
};


bool VfdStdOut::print(
        Vfd   *vfd,
        UINT8  regionId,
        const UINT8 *string)
{
    const Region *p_region;
    UINT8 numRegions;
    Region region;

    bool success = false;
    ICharacter *ichar = NULL;

    // 
    // Step 1 - Get the region map and find the matching Char region.
    //
    vfd->layout->getRegionMap(&p_region, &numRegions);

    for (UINT8 i = 0 ; i < numRegions ; i++)
    {
        memcpy_P(&region, &p_region[i], sizeof(region));

        if ((RegionTypeChar == region.type) && (regionId == region.id))
        {
            success = true;
        }
    }

    if (!success)
    {
        return false;
    }

    //
    // Step 2 - Find the matching character implementation
    //
    for (UINT8 i = 0 ; i < m_numRegionTypeCharMapEntries ; i++)
    {
        if (m_regionTypeCharMap[i].subChar == region.subType.subChar)
        {
            ichar = m_regionTypeCharMap[i].ichar;
        }
    }

    if (ichar == NULL)
    {
        return false;
    }
 
    for (UINT8 x = 0 ; string[x] != 0 ; x++)
    {
        UINT8 ascii = string[x];

        // CR - carriage return, to col 0
        if (ascii == '\r')
        {
            m_currentCol = 0;
            continue;
        }

        // FF - Form Feed, reset back to 0 & clear. NOTE: this is quite slow.
        if (ascii == '\f')
        {
            m_currentCol = 0;

            // Loop through writing space characters.
            for (int i = 0 ; i < region.len ; i++)
            {
                ichar->print(
                    vfd,
                    regionId,
                    i,
                    ' ');
            }
            continue;
        }

        success = ichar->print(
            vfd,
            regionId,
            m_currentCol,
            ascii);

        if (!success)
        {
            break;
        }

        m_currentCol++;
    }

    return success;
};


bool VfdStdOut::printf(
        const UINT8 *format, 
        ...)
{
    UINT8 buffer[s_bufferSize];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
 
    return print(m_stdOutVfd, m_stdOutRegionId, buffer);
};    


bool VfdStdOut::printf(
        Vfd   *vfd,
        UINT8  regionId,
        const UINT8 *format, 
        ...)
{
    UINT8 buffer[s_bufferSize];

    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
 
    return print(vfd, regionId, buffer);
};    
