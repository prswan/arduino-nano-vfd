//
// Copyright (c) 2025, Paul R. Swan
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
#include "Buttons.h"
#include "VfdStdOut.h"
#include "AppEngine.h"
#include "LayoutFinder.h"
#include "TestUtils.h"

/* TODO

How to Find an Undocumented VFD Pinout
--------------------------------------

We can utlize a few typical configuration hints:
1) Since the number of grids defines the length of a scan and therefore the maximum brightness,
   typically grid pin counts fall in the 8 to 20 range. On many displays the grid pin count
   can be visually estimated.
2) For large complex displays, the limitation of grid pin count results in a much larger segment
   pin count, falling in the 18 to 80 range.
3) Grid and segment pins are usually in separate groups or in long runs of grid and segment pins.

Step 1
------
 - Divide the VFD pins in half and define a PinMap of grids for one half and segments for the other.
 - Use the Layout applet to walk through the grid and pin activations to see what lights up.
   - If an increment of 1 results in a segment in a new grid, that pin was a grid.
   - If an increment of 1 results in a different segment in the same grid, that pin was a segment.
   - If nothing lights, the pin pair were not connected, two grids or two segments.
 - This will identify some confirmed grid and segment pins
   - Revise the grid and segment PinMaps to assign the identified pins correctly to grid or segment.
   - Review based on typical co-location
     - A grid pin is likely to be next to other grids.
     - Group elements (hex digits, bars etc.) are usually on the same grid and their segment pins grouped.
   - Repeat to identify more pins.
*/

/*
 - Cannot pass a direct pointer to a constructor so a creator stub is needed:
   IApp* createLayoutFinderApp(Controller *controller) { return new LayoutFinderApp(controller); }
   - The object should take care of it's own lifetime management w.r.t. background function support
   - Engine calls "createLayoutFinderApp" on new select and delete on deslect?
 - It's natural to make this an IApp class BUT each IApp oject will burn RAM with vtable pointers. 
   - And because background is supported, they all need to remain in existance.
 - Alternate option is a static function table in PROGMEM and let the app manage durable state. 
   Many Apps won't have any state.
   - In this case, create() and delete() are rolled into onSelect(), onDeSelect() and thus implied.
   - run() will need to take care of it's own state and may be called before any select.
     - Engine will call all the run() of all apps on every timer tick. Needs to be fast enough for visual effects.
     - Can allow NULL to skip any unused.

   - run()
   - onSelect()
   - onDeSelect()
   - onNextShortPress()
   - onNextLongPress()

   Based on select description display 7 char "AppEngine" and StdOut 11 char. All PROGMEM like the ICT.
   //1234567
   {"LayFind", LayoutFinderRun, LayoutFinderOnSelect, LayoutFinderOnDeSelect, LayoutFinderOnNextShortPress, LayoutFinderOnNextLongPress }

   What we have so far (should be 7-seg compat unique still for first letter or two): 
   - "LAYFIND","SEG ON","PIN ON","PERF","ALPHA","BAR","SYM","NUMLIST","FREE"

   At some point we'll need to define some sort of common display features for apps to use
   e.g. 7 char select, 11 char stdout, 4 digit hex, 2-bar horizontal, 5-bar EQ, number list, 2 digit hex etc.
*/

static AppEngineMenu s_appEngineMenu[] =
{
//   "1234567"
    {"Pin On ", NULL,         PinOn::onSelect,           NULL, NULL,                              NULL},
    {"LayFind", NULL,         LayoutFinder::onSelect,    NULL, LayoutFinder::onNextShortPress,    LayoutFinder::onNextLongPress},
    {"Seg On ", NULL,         SegOn::onSelect,           NULL, NULL,                              NULL},
    {"ASCII  ", NULL,         TestAscii::onSelect,       NULL, TestAscii::onNextShortPress,       NULL},
    {"Symbol ", NULL,         TestSymbol::onSelect,      NULL, TestSymbol::onNextShortPress,      NULL},
    {"Bar    ", TestBar::run, TestBar::onSelect,         NULL, TestBar::onNextShortPress,         TestBar::onNextLongPress},
    {"List   ", NULL,         TestNumberList::onSelect,  NULL, TestNumberList::onNextShortPress,  NULL},
    {"Manu   ", NULL,         Manufacturer::onSelect,    NULL, Manufacturer::onNextShortPress,    NULL},
    {"Perf   ", NULL,         Performance::onSelect,     NULL, Performance::onNextShortPress ,    NULL},
    {"FreeMem", NULL,         Memory::onSelect,          NULL, Memory::onNextShortPress ,         NULL},
    {0}
};

void Main(Controller *controller)
{
    // in case we crash
    if (controller->buttons->isSelectActive())
    {
        return;
    }

    VfdStdOut *stdOut = new VfdStdOut(controller->regionSubTypeMap,
                                      ARRAYSIZE(controller->regionSubTypeMap),
                                      controller->stdOutVfd,
                                      controller->stdOutRegionId);

    controller->stdOut = stdOut;

    if (controller->appEngineVfd == NULL)
    {
        controller->appEngineVfd      = controller->stdOutVfd;
        controller->appEngineRegionId = controller->stdOutRegionId;
    }

    AppEngine(controller, s_appEngineMenu);
};
