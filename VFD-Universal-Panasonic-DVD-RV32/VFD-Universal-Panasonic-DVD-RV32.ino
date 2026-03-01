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

#include "Controller.h"
#include "Char14Seg.h"

#include "PanasonicDVDRV32Pinout.h"
#include "PanasonicDVDRV32Layout.h"

// AN5818 Digital pin mappings
#define AN5818_STROBE (1)  // Rising edge clocked
#define AN5818_BLANK  (9)  // Hi == All outputs disabled

#define BUTTON_PIN_NEXT   (3)
#define BUTTON_PIN_SELECT (2)

static Controller controller;

void setup() {
  // put your setup code here, to run once:

  IVfdPinout *vfdPinout = new PanasonicDVDRV32Pinout();
  IVfdLayout *vfdLayout = new PanasonicDVDRV32Layout();

  ShiftRegisterBitMap *bitMap = new ShiftRegisterBitMap(vfdPinout, NULL);
  ShiftRegisterScan   *scan   = new ShiftRegisterScan(bitMap, AN5818_STROBE, AN5818_BLANK);

  controller.vfd[0][0].layout  = vfdLayout;
  controller.vfd[0][0].display = bitMap->getDisplay(0);

  controller.bitMap[0] = bitMap;
  controller.scan      = scan;

  controller.buttons = new Buttons(BUTTON_PIN_NEXT, BUTTON_PIN_SELECT);

  controller.stdOutVfd = &controller.vfd[0][0];
  controller.stdOutRegionId = 0;

  controller.regionSubTypeMap[0].subChar = RegionSubTypeChar14Seg;
  controller.regionSubTypeMap[0].ichar = new Char14Seg();
}

void loop() {
  // put your main code here, to run repeatedly:
  Main(&controller);
}
