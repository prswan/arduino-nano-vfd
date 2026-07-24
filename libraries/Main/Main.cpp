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
#include "ShiftRegisterDisplay.h"
#include "Char7Seg.h"
#include "LayoutFinder.h"
#include "VfdStdOut.h"
#include "Bar.h"
#include "NumberList.h"
#include "Symbol.h"
#include "AppEngine.h"
#include "TestUtils.h"

//
// I don't remember needing to use an external library in the ICT project for this.
// Source: https://github.com/mpflaga/Arduino-MemoryFree, Commit Hash: 0083982
//
// Unzip To: C:\Users\<user>>\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6\libraries\MemoryFree
//
#include <MemoryFree.h>


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
    {"Pin On ", NULL, PinOn::onSelect,        NULL, NULL,                           NULL},
    {"LayFind", NULL, LayoutFinder::onSelect, NULL, LayoutFinder::onNextShortPress, LayoutFinder::onNextLongPress},
    {"Seg On ", NULL, SegOn::onSelect,        NULL, NULL,                           NULL},
    {"Manu   ", NULL, Manufacturer::onSelect, NULL, Manufacturer::onNextShortPress, NULL},
    {"Perf   ", NULL, Performance::onSelect,  NULL, Performance::onNextShortPress , NULL},
    {"ASCII  ", NULL, TestAscii::onSelect,    NULL, TestAscii::onNextShortPress,    NULL},
    {"Bar    ", NULL, TestBar::onSelect,      NULL, TestBar::onNextShortPress,      NULL},
    {0}
};

void Main(Controller *controller)
{
    Buttons *buttons = controller->buttons;

    //
    // TODO: This doesn't work if stdOutVfd and uutVfd use different character encodings
    // e.g. using the Pana-Sony as stdOut and TEAC as uut means uut character prints don't work.
    // printf works OK.
    // 
    ICharacter *character = controller->regionSubTypeMap[0].ichar; 

    // in case we crash
    if (buttons->isSelectActive())
    {
        return;
    }

    IDisplay *stdOutDisplay = controller->stdOutVfd->display;
    IDisplay *uutDisplay = controller->uutVfd->display;

    VfdStdOut *stdOut = new VfdStdOut(controller->regionSubTypeMap,
                                      ARRAYSIZE(controller->regionSubTypeMap),
                                      controller->stdOutVfd,
                                      controller->stdOutRegionId);

    controller->stdOut = stdOut;

    if (!buttons->isNextActive())
    {
        if (controller->appEngineVfd == NULL)
        {
            controller->appEngineVfd      = controller->stdOutVfd;
            controller->appEngineRegionId = controller->stdOutRegionId;
        }

        AppEngine(controller, s_appEngineMenu);
    }

    UINT8 currentApp = 0;
    bool newApp = true;

    // Main loop
    while (1)
    {  
        if (controller->timer->run())
        {
            switch (currentApp)
            {
                // Moved to the AppEngine or deprecated
                case 0:
                case 1:
                case 2:
                case 3: // Clear rolled into Manu
                case 4:
                case 5:
                case 6:
                {
                    if (newApp)
                    {
                        stdOut->printf("\f%s", "UNUSED");
                        break;
                    }
                }

                // Walk through the symbol group
                case 7:
                {
                    static UINT8 symGroupIndex = 0;

                    if (newApp)
                    {
                        symGroupIndex = 0;

                        if (uutDisplay != stdOutDisplay)
                        {
                            uutDisplay->clear();
                        }

                        stdOutDisplay->clear();
                        character->print(controller->stdOutVfd, controller->stdOutRegionId, 0, 'S');

                        // Blind symbol set to test out this API, at least 1 activated for each supported display.
                        Symbol::set(controller->uutVfd, 0, SymPlayForward, true);
                        Symbol::set(controller->uutVfd, 0, SymPause, true);
                        Symbol::set(controller->uutVfd, 1, SymPause, true);
                        Symbol::set(controller->uutVfd, 0, SymText_CD, true);
                    }

                    if (buttons->isNextShortPressed())
                    {
                        if (symGroupIndex == 0)
                        {
                            uutDisplay->clear();
                        }

                        Sym sym = SymNone;
                        UINT8 instance = 0;

                        bool success = Symbol::set(controller->uutVfd, symGroupIndex, true, &sym, &instance);

                        if (success)
                        {
                            character->print(controller->stdOutVfd, controller->stdOutRegionId, 0, '0' + instance);

                            UINT8 value = sym;
                            character->print(controller->stdOutVfd, controller->stdOutRegionId, 2, '0' + (value / 10));
                            value = (value % 10);
                            character->print(controller->stdOutVfd, controller->stdOutRegionId, 3, '0' + (value / 1));

                            symGroupIndex++;
                        }
                        else
                        {
                            symGroupIndex = 0;
                        }
                    }
                    break;
                }

                // Walk through the number list
                case 8:
                {
                    static bool  displayTo = false;
                    static UINT8 number = 0;

                    if (newApp)
                    {
                        displayTo = false;
                        number    = 0;

                        if (uutDisplay != stdOutDisplay)
                        {
                            uutDisplay->clear();
                        }

                        stdOutDisplay->clear();
                        character->print(controller->stdOutVfd, controller->stdOutRegionId, 0, 'L');
                    }

                    if (buttons->isNextShortPressed())
                    {
                        UINT8 charValue = number;
                        character->print(controller->stdOutVfd, controller->stdOutRegionId, 2, '0' + (charValue / 10));
                        charValue = (charValue % 10);
                        character->print(controller->stdOutVfd, controller->stdOutRegionId, 3, '0' + (charValue / 1));

                        NumberList::set(controller->uutVfd, 0, 0, displayTo, number);

                        if (++number >= (ARRAYSIZE(SegmentGroupNumberList::grid[0].list) + 2))
                        {
                            number = 0;
                            displayTo = !displayTo;
                        }
                    }
                    break;
                }

                // Report free memory
                case 9:
                {
                    if (newApp)
                    {
                        stdOut->printf("\f%s", "FREE");
                    }

                    if (buttons->isNextShortPressed())
                    {
                        stdOut->printf("\r%4.4d", freeMemory());
                    }
                    break;
                }

                default:
                    break;
            }

            if (buttons->isSelectShortPressed())
            {
                if (++currentApp > 9)
                {
                    currentApp = 0;
                }
                newApp = true;
            }
            else
            {
                newApp = false;
            }
        }
    }
};
