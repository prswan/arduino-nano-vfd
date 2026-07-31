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
#include "KronosSystem55Layout.h"

/*
Data
----
This was a used front panel PCB bought from Surplusgizmos, Hilsboro, OR. They had a box of them.

*****************************************************************
******** !! The panel is not compatible with 2MHz SPI !! ********
*****************************************************************

Temp Hack: MuxSpi.cpp: SPIClass::beginTransaction(SPISettings(1000000, bitOrder, SPI_MODE3));

TODO: Investigate dynamic SPI clock per serial chain. Would also allow the UCN5818 to be run at 4MHz.

According to the datasheets for the SN75512C 12-bit driver & SN75518 32-bit driver:
 - Both 12-bit & 32-bit parts have a 1MHz max clock at 5V, though the 32-bit part seems OK @ 2MHz.
 - 12-bit part max clock frequency is 4MHz @ 15V versus 5MHz @ 10V for the 32-bit part.
 - DATA IN setup and hold times are min 250ns for the 12-bit part versus 150ns for the 32-bit part.
 Thus, it appears the 32-bit part is slightly faster.

Onkyo HT-R340 NPT-1516D Transformer
-----------------------------------
 - VFIL @ Controller PCB Input  : 5.33 VAC
 - VFIL @ Controller PL4 2x 15R : 4.28 VAC
 - VFIL @ VFD                   : 4.27 VAC
 Display looks good. 
 Very low current with such a small voltage drop accross quite high Fil resistance. 
 Glass is barely warm.
 */

static const UINT8 s_manufacturer[] PROGMEM = "KRONOS";
static const UINT8 s_model[]        PROGMEM = "SYSTEM 55";

static const Properties s_properties PROGMEM =
{
    s_manufacturer,
    s_model,
};

//
// 16x 5x7 matrix
//
static const Region s_region[] PROGMEM =
{
    // type,          subType,                 id, len
    {RegionTypeChar,  RegionSubTypeChar5x7,     0,  16}
};

void KronosSystem55Layout::getProperties(
    const Properties **p_properties)
{
    *p_properties = &s_properties;
}

void KronosSystem55Layout::getRegionMap(
    const Region **p_region,
    UINT8 *numEntries)
{
    *p_region = s_region;
    *numEntries = ARRAYSIZE(s_region);
};
