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
#include "Main.h"

#include "PanasonicDVDRV32Pinout.h"
#include "PanasonicDVDRV32Layout.h"
#include "Char14Seg.h"

// AN5818 Digital pin mappings

#define AN5818_STROBE (1)  // Rising edge clocked
#define AN5818_BLANK  (9)  // Hi == All outputs disabled

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

  IVfdPinout *vfdPinout = new PanasonicDVDRV32Pinout();
  IVfdLayout *vfdLayout = new PanasonicDVDRV32Layout();

  ShiftRegisterBitMap *bitMap = new ShiftRegisterBitMap(vfdPinout, NULL);
  ShiftRegisterScan   *scan   = new ShiftRegisterScan(bitMap, AN5818_STROBE, AN5818_BLANK);

  IDisplay *display1 = bitMap->getDisplay(0);

  ICharacter *character = new Char14Seg((IVfdLayout14Seg*) vfdLayout, display1);

  Main(bitMap, scan, character);
}
