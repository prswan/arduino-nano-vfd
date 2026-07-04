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

// ----------------------------------------------------------------------------
// NOTE: This is a none-functional sketch used to perform a build check of all
// the display implementations!
//-----------------------------------------------------------------------------

#include "Controller.h"
#include "Char14Seg.h"
#include "Char7Seg.h"

// Universal Shift Register system

#include "SonyTCWR775Pinout.h"
#include "SonyTCWR775Layout.h"

#include "SonyDVPNS725PPinout.h"
#include "SonyDVPNS725PLayout.h"

#include "PanasonicDVDRV32Pinout.h"
#include "PanasonicDVDRV32Layout.h"

#include "TeacPDD1200Pinout.h"
#include "TeacPDD1200Layout.h"

#include "KenwoodKRV77RPinout.h"
#include "KenwoodKRV77RLayout.h"

#include "SonyCDPC305Pinout.h"
#include "SonyCDPC305Layout.h"

#include "PhilipsFC40Pinout.h"
#include "PhilipsFC40Layout.h"

// Integrated Driver IC Front Panel system
#include "PT631xDriverIC.h"
#include "Timer.h"
#include "DriverICDisplay.h"

#include "SamsungBDP1590Pinout.h"
#include "SamsungBDP1590Layout.h"

#include "PioneerDVR220Pinout.h"
#include "PioneerDVR220Layout.h"

#include "KossWMS1100Pinout.h"
#include "KossWMS1100Layout.h"

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

  IVfdPinout *vfdPinoutU0 = new SonyTCWR775Pinout();
  IVfdLayout *vfdLayoutU0 = new SonyTCWR775Layout();

  IVfdPinout *vfdPinoutU1 = new SonyDVPNS725PPinout();
  IVfdLayout *vfdLayoutU1 = new SonyDVPNS725PLayout();

  IVfdPinout *vfdPinoutU2 = new PanasonicDVDRV32Pinout();
  IVfdLayout *vfdLayoutU2 = new PanasonicDVDRV32Layout();

  IVfdPinout *vfdPinoutU3 = new TeacPDD1200Pinout();
  IVfdLayout *vfdLayoutU3 = new TeacPDD1200Layout();

  IVfdPinout *vfdPinoutU4 = new KenwoodKRV77RPinout();
  IVfdLayout *vfdLayoutU4 = new KenwoodKRV77RLayout();

  IVfdPinout *vfdPinoutU5 = new SonyCDPC305Pinout();
  IVfdLayout *vfdLayoutU5 = new SonyCDPC305Layout();

  IVfdPinout *vfdPinoutU6 = new PhilipsFC40Pinout();
  IVfdLayout *vfdLayoutU6 = new PhilipsFC40Layout();

  IVfdPinout *vfdPinoutF0 = new SamsungBDP1590Pinout();
  IVfdLayout *vfdLayoutF0 = new SamsungBDP1590Layout();

  IVfdPinout *vfdPinoutF1 = new PioneerDVR220Pinout();
  IVfdLayout *vfdLayoutF1 = new PioneerDVR220Layout();

  IVfdPinout *vfdPinoutF2 = new KossWMS1100Pinout();
  IVfdLayout *vfdLayoutF2 = new KossWMS1100Layout();

  ShiftRegisterBitMap *bitMap0 = new ShiftRegisterBitMap(vfdPinoutU0, vfdPinoutU1);
  ShiftRegisterBitMap *bitMap1 = new ShiftRegisterBitMap(vfdPinoutU2, NULL);
  ShiftRegisterBitMap *bitMap2 = new ShiftRegisterBitMap(vfdPinoutU3, NULL);
  ShiftRegisterBitMap *bitMap3 = new ShiftRegisterBitMap(vfdPinoutU4, NULL);
  ShiftRegisterBitMap *bitMap4 = new ShiftRegisterBitMap(vfdPinoutU5, vfdPinoutU6);
  
  controller.vfd[0][0].layout  = vfdLayoutU0;
  controller.vfd[0][0].display = bitMap0->getDisplay(0);

  controller.vfd[0][1].layout  = vfdLayoutU1;
  controller.vfd[0][1].display = bitMap0->getDisplay(1);

  controller.vfd[1][0].layout  = vfdLayoutU2;
  controller.vfd[1][0].display = bitMap1->getDisplay(0);

  controller.vfd[2][0].layout  = vfdLayoutU3;
  controller.vfd[2][0].display = bitMap2->getDisplay(0);

  controller.vfd[3][0].layout  = vfdLayoutU4;
  controller.vfd[3][0].display = bitMap3->getDisplay(0);

  controller.vfd[4][0].layout  = vfdLayoutU5;
  controller.vfd[4][0].display = bitMap4->getDisplay(0);

  controller.vfd[4][1].layout  = vfdLayoutU6;
  controller.vfd[4][1].display = bitMap4->getDisplay(1);

  controller.isShiftRegister = true;

  controller.sys.sr.bitMap[0] = bitMap0; // Port Address 0, PL1
  controller.sys.sr.bitMap[1] = bitMap1; // Port Address 1, PL2
  controller.sys.sr.bitMap[2] = bitMap2; // Port Address 2, PL3
  controller.sys.sr.bitMap[3] = bitMap3; // Port Address 3, PL4
  controller.sys.sr.bitMap[4] = bitMap4; // Port Address 4, PL5

  controller.sys.sr.scan = new ShiftRegisterScan(controller.muxSpi, 
                                                 &(controller.sys.sr.bitMap[0]), 
                                                 ARRAYSIZE(controller.sys.sr.bitMap));

  IDriverIC *idic = new PT631xDriverIC(controller.muxSpi);

  controller.stdOutVfd = &controller.vfd[0][1]; // Sony for StdOut
  controller.stdOutRegionId = 0;

  controller.uutVfd = &controller.vfd[2][0]; // Kenwood as the UUT
  controller.uutRegionId = 1;
}

void loop() {
  // put your main code here, to run repeatedly:
  Main(&controller);
}
