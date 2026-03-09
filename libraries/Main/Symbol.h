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
#ifndef Symbol_h
#define Symbol_h

#include "IDisplay.h"
#include "Sym.h"


//
// Symbol printing
//
class Symbol
{
public:
    Symbol() {};

    ~Symbol() {};

    //
    // Turn a symbol on or off.
    //
    // returns false if the symbol is not present on the VFD.
    //
    static bool set(
        Vfd  *vfd,
        UINT8 instance,
        Sym   sym,
        bool  on
    );

    //
    // Turn a symbol on or off using the IVfdLayout symbol group index.
    // This form is more convenient to walk through only the symbols
    // that the VFD has.
    // The Sym and instance values for the symbol are returned.
    //
    // returns false if the index is out of bounds (end of group list)
    //
    static bool set(
        Vfd   *vfd,
        UINT8  index,
        bool   on,
        Sym   *sym,
        UINT8 *instance
    );

private:

    //
    // If we're unable to find a matching single segment symbol,
    // try to find a match in the graphic symbols.
    //
    // returns false if the symbol is not present on the VFD.
    //
    static bool setGraphicSymbol(
        Vfd  *vfd,
        UINT8 instance,
        Sym   sym,
        bool  on
    );

    //
    // Tacked onto the end of the index based set to also walk through
    // and graphic symbols that have been defined.
    //
    // returns false if the index is out of bounds (end of group list)
    //
    static bool setGraphicSymbol(
        Vfd   *vfd,
        UINT8  index,
        bool   on,
        Sym   *sym,
        UINT8 *instance
    );

};

#endif
