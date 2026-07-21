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

//
// Development configuration for Controller V1.00 Serial No.: CTR20260701
//

#include "Main.h"

#include "Controller.h"
#include "Char7Seg.h"
#include "Char14Seg.h"

#include "KenwoodKRV77RPinout.h"
#include "KenwoodKRV77RLayout.h"

#include "PanasonicDVDRV32Pinout.h"
#include "PanasonicDVDRV32Layout.h"

#include "SonyDVPNS725PPinout.h"
#include "SonyDVPNS725PLayout.h"

#include "SonyCDPC305Pinout.h"
#include "SonyCDPC305Layout.h"

#include "PhilipsFC40Pinout.h"
#include "PhilipsFC40Layout.h"

// Controller Digital pin mappings
#define CONTROLLER_PIN_NEXT   (2)
#define CONTROLLER_PIN_SELECT (3)

static Controller controller;

void setup() {
  // put your setup code here, to run once:

  controller.muxSpi = new MuxSpi(MSBFIRST);

  controller.timer = new Timer();

  controller.buttons = new Buttons(CONTROLLER_PIN_NEXT, 
                                   CONTROLLER_PIN_SELECT);

  controller.regionSubTypeMap[0].subChar = RegionSubTypeChar14Seg;
  controller.regionSubTypeMap[0].ichar = new Char14Seg();

  controller.regionSubTypeMap[1].subChar = RegionSubTypeChar7Seg;
  controller.regionSubTypeMap[1].ichar = new Char7Seg();

  IVfdPinout *vfdPinout0 = new KenwoodKRV77RPinout();
  IVfdLayout *vfdLayout0 = new KenwoodKRV77RLayout();

  IVfdPinout *vfdPinout1 = new PanasonicDVDRV32Pinout();
  IVfdLayout *vfdLayout1 = new PanasonicDVDRV32Layout();

  IVfdPinout *vfdPinout2 = new SonyDVPNS725PPinout();
  IVfdLayout *vfdLayout2 = new SonyDVPNS725PLayout();

  IVfdPinout *vfdPinout3 = new SonyCDPC305Pinout();
  IVfdLayout *vfdLayout3 = new SonyCDPC305Layout();

  IVfdPinout *vfdPinout4 = new PhilipsFC40Pinout();
  IVfdLayout *vfdLayout4 = new PhilipsFC40Layout();

  ShiftRegisterBitMap *bitMap0 = new ShiftRegisterBitMap(vfdPinout0, 
                                                         NULL);

  ShiftRegisterBitMap *bitMap1 = new ShiftRegisterBitMap(vfdPinout1, 
                                                         vfdPinout2);

  ShiftRegisterBitMap *bitMap2 = new ShiftRegisterBitMap(vfdPinout3,
                                                         vfdPinout4);

  controller.vfd[0][0].layout  = vfdLayout0;
  controller.vfd[0][0].display = bitMap0->getDisplay(0);

  controller.vfd[1][0].layout  = vfdLayout1;
  controller.vfd[1][0].display = bitMap1->getDisplay(0);

  controller.vfd[1][1].layout  = vfdLayout2;
  controller.vfd[1][1].display = bitMap1->getDisplay(1);

  controller.vfd[2][0].layout  = vfdLayout3;
  controller.vfd[2][0].display = bitMap2->getDisplay(0);

  controller.vfd[2][1].layout  = vfdLayout4;
  controller.vfd[2][1].display = bitMap2->getDisplay(1);

  controller.isShiftRegister = true;

  controller.sys.sr.bitMap[0] = bitMap0; // Port Address 0, PL1
  controller.sys.sr.bitMap[7] = bitMap1; // Port Address 7, PL8
  controller.sys.sr.bitMap[4] = bitMap2; // Port Address 4, PL5

  controller.sys.sr.scan = new ShiftRegisterScan(controller.muxSpi, 
                                                 &(controller.sys.sr.bitMap[0]), 
                                                 ARRAYSIZE(controller.sys.sr.bitMap));

  controller.appEngineVfd = &controller.vfd[1][1]; // Sony for AppEngine menu
  controller.appEngineRegionId = 0;

  controller.stdOutVfd = &controller.vfd[1][0]; // Panasonic for StdOut
  controller.stdOutRegionId = 0;

  controller.uutVfd = &controller.vfd[0][0]; // KR-V77R as the UUT
  controller.uutRegionId = 0; // 5x 14-seg region
}

void loop() {
  // put your main code here, to run repeatedly:
  Main(&controller);
}
