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
#ifndef VfdStdOut_h
#define VfdStdOut_h

#include "IVfdLayout.h"
#include "ICharacter.h"

//
// Provide the object with a mapping between the character sub type and
// the implementation to print using that specific sub type.
//
typedef struct _RegionSubTypeCharMap
{
    RegionSubTypeChar  subChar;
    ICharacter        *ichar;

} RegionSubTypeCharMap;


//
// Standard output functions.
//
class VfdStdOut
{
public:

    VfdStdOut(
        RegionSubTypeCharMap *regionTypeCharMap,
        UINT8  numRegionTypeCharMapEntries,
        Vfd   *stdOutVfd,
        UINT8  stdOutRegionId
    );

    ~VfdStdOut() {};

    //
    // Print a simple unformatted NULL terminated string to the Vfd region.
    // This is faster that the formatted string print.
    //
    bool print(
        Vfd   *vfd,
        UINT8  regionId,
        const UINT8 *string
    );

    //
    // Print a formatted string to the Vfd display region regionId.
    //
    bool printf(
        Vfd   *vfd,
        UINT8  regionId,
        const UINT8 *format, 
        ...
    );

    //
    // Default formatted string print to the primary display region defined as StdOut.
    //
    bool printf(
        const UINT8 *format, 
        ...
    );

private:

private:

    RegionSubTypeCharMap *m_regionTypeCharMap;
    UINT8 m_numRegionTypeCharMapEntries;

    Vfd   *m_stdOutVfd;
    UINT8  m_stdOutRegionId;

    UINT8 m_currentCol;
};

#endif
