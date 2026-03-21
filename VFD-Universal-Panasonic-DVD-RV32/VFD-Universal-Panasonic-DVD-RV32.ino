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

#include "SonyDVPNS725PPinout.h"
#include "SonyDVPNS725PLayout.h"

// Controller Digital pin mappings
#define CONTROLLER_PIN_STROBE (8)  // Rising edge clocked
#define CONTROLLER_PIN_BLANK  (9)  // Hi == All outputs disabled

#define CONTROLLER_PIN_NEXT   (2)
#define CONTROLLER_PIN_SELECT (3)

#define CONTROLLER_PIN_SEL0   (5)
#define CONTROLLER_PIN_SEL1   (6)
#define CONTROLLER_PIN_SEL2   (7)

static Controller controller;

void setup() {
  // put your setup code here, to run once:

  IVfdPinout *vfdPinout0 = new PanasonicDVDRV32Pinout();
  IVfdLayout *vfdLayout0 = new PanasonicDVDRV32Layout();

  IVfdPinout *vfdPinout1 = new SonyDVPNS725PPinout();
  IVfdLayout *vfdLayout1 = new SonyDVPNS725PLayout();

  MuxSpi *muxSpi = new MuxSpi(CONTROLLER_PIN_STROBE,
                              CONTROLLER_PIN_BLANK,
                              CONTROLLER_PIN_SEL0,
                              CONTROLLER_PIN_SEL1,
                              CONTROLLER_PIN_SEL2,
                              MSBFIRST);

  ShiftRegisterBitMap *bitMap = new ShiftRegisterBitMap(vfdPinout0, vfdPinout1);

  controller.isShiftRegister = true;

  controller.sys.sr.bitMap[0] = bitMap; // Port Address 0, PL1

  ShiftRegisterScan   *scan   = new ShiftRegisterScan(muxSpi, 
                                                      &(controller.sys.sr.bitMap[0]), 
                                                      ARRAYSIZE(controller.sys.sr.bitMap));

  controller.vfd[0][0].layout  = vfdLayout0;
  controller.vfd[0][0].display = bitMap->getDisplay(0);

  controller.vfd[0][1].layout  = vfdLayout1;
  controller.vfd[0][1].display = bitMap->getDisplay(1);

  controller.muxSpi = muxSpi;

  controller.buttons = new Buttons(CONTROLLER_PIN_NEXT, CONTROLLER_PIN_SELECT);

  controller.scan = scan;

  controller.stdOutVfd = &controller.vfd[0][1]; // Sony for StdOut
  controller.stdOutRegionId = 0;

  controller.regionSubTypeMap[0].subChar = RegionSubTypeChar14Seg;
  controller.regionSubTypeMap[0].ichar = new Char14Seg();

  controller.uutVfd = &controller.vfd[0][0]; // Panasonic as the UUT 
  controller.uutRegionId = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  Main(&controller);
}
