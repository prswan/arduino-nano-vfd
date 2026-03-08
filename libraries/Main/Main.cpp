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


void Main(Controller *controller)
{
    Buttons *buttons = controller->buttons;
    ICharacter *character = controller->regionSubTypeMap[0].ichar; 

    // in case we crash
    if (buttons->isSelectActive())
    {
        return;
    }

    IDisplay *stdOutDisplay = controller->stdOutVfd->display;
    IDisplay *uutDisplay = controller->uutVfd->display;

    // The LayoutFinder app
    IApp *app = new LayoutFinder(
        buttons,
        controller->stdOutVfd,
        controller->stdOutRegionId,
        character,
        controller->uutVfd);

    VfdStdOut *stdOut = new VfdStdOut(controller->regionSubTypeMap,
                                      ARRAYSIZE(controller->regionSubTypeMap),
                                      controller->stdOutVfd,
                                      controller->stdOutRegionId);

    UINT8 currentApp = 0;
    bool newApp = true;

    // Main loop
    while (1)
    {  
        if (controller->scan->run())
        {
            switch (currentApp)
            {
                // The App
                case 0:
                {
                    app->run(newApp);
                    break;
                }

                // Set all the Segment pins active maintaining Grid scan
                case 1:
                {
                    if (newApp)
                    {
                        if (uutDisplay != stdOutDisplay)
                        {
                            stdOut->printf("\f%s", "SEG ON");
                        }

                        uutDisplay->setAllSegmentsOn();
                    }
                    break;
                }

                // Set all the pins on, effectively no scan.
                case 2:
                {
                    if (newApp)
                    {
                        uutDisplay->clear();

                        // Only applicable to the Universal shift register version.
                        if (controller->isShiftRegister)
                        {
                            if (uutDisplay != stdOutDisplay)
                            {
                                stdOut->printf("\f%s", "PIN ON");
                            }

                            //
                            // Only applicable to the ShiftRegister implementation.
                            // The integrated bit map driver IC's don't have pin control.
                            //
                            ShiftRegisterDisplay *shiftRegisterDisplay = (ShiftRegisterDisplay *) uutDisplay;

                            shiftRegisterDisplay->setAllPins(true);
                        }
                        else
                        {
                            stdOut->printf("\f%s", "0123456789");
                        }
                    }

                    if (buttons->isNextShortPressed())
                    {
                        static bool manu = true;
                        const UINT8* p_string;

                        uutDisplay->clear();

                        Properties *p_properties;

                        controller->uutVfd->layout->getProperties(&p_properties);

                        if (manu)
                        {
                            if (uutDisplay != stdOutDisplay)
                            {
                                stdOut->printf("\f%s", "MANUF");
                            }

                            p_string = pgm_read_ptr(&p_properties->manufacturer);
                            manu = false;
                        }
                        else
                        {
                            if (uutDisplay != stdOutDisplay)
                            {
                                stdOut->printf("\f%s", "MODEL");
                            }

                            p_string = pgm_read_ptr(&p_properties->model);
                            manu = true;
                        }

                        stdOut->print(controller->uutVfd, 
                                      controller->uutRegionId,
                                      "\f");

                        stdOut->print_P(controller->uutVfd, 
                                        controller->uutRegionId,
                                        p_string);
                    }

                    break;
                }

                // Clear all the Segments back to off
                case 3:
                {
                    if (newApp)
                    {
                        if (uutDisplay != stdOutDisplay)
                        {
                            stdOut->printf("\f%s", "CLEAR");
                        }

                        uutDisplay->clear();
                    }
                    break;
                }

                // Performance measurment for the scan overhead.
                case 4:
                {
                    if (newApp)
                    {
                        stdOut->printf("\f%s", "PERF");
                    }

                    // This works because the run is only called when the display is scanned
                    static UINT32 previousTimeInUs = 0;

                    UINT32 currentTimeInUs = micros();
                    UINT16 elapsedTimeInUs = (UINT16)(currentTimeInUs - previousTimeInUs);

                    previousTimeInUs = currentTimeInUs;

                    if (buttons->isNextShortPressed())
                    {
                        //
                        // This print appears to be so slow that it glitches the display.
                        // The \f clear is really expensive. Still slight glitch though.
                        // The math parsing must be terrible.
                        //
                        stdOut->printf("\r%4.4d", elapsedTimeInUs);
                    }
                    break;
                }

                // Walk through the ASCII character set
                case 5:
                {
                    static UCHAR currentChar = 0;

                    if (newApp)
                    {
                        currentChar = 0x20;

                        if (uutDisplay != stdOutDisplay)
                        {
                            uutDisplay->clear();
                        }

                        stdOutDisplay->clear();
                        character->print(controller->stdOutVfd, controller->stdOutRegionId, 0, 'A');
                    }

                    if (buttons->isNextShortPressed())
                    {
                        if (++currentChar >= 127)
                        {
                            currentChar = 0x20;
                        }

                        character->print(controller->stdOutVfd, controller->stdOutRegionId, 0, ' ');
                        character->print(controller->stdOutVfd, controller->stdOutRegionId, 0, currentChar);

                        if (uutDisplay != stdOutDisplay)
                        {
                            character->print(controller->uutVfd, controller->uutRegionId, 0, ' ');
                            character->print(controller->uutVfd, controller->uutRegionId, 0, currentChar);
                        }

                        UINT8 charValue = currentChar;
                        character->print(controller->stdOutVfd, controller->stdOutRegionId, 2, '0' + (charValue / 10));
                        charValue = (charValue % 10);
                        character->print(controller->stdOutVfd, controller->stdOutRegionId, 3, '0' + (charValue / 1));
                    }
                    break;
                }

                // Walk through the Bar settings
                case 6:
                {
                    static bool  scale = false;
                    static UINT8 len = 0;

                    if (newApp)
                    {
                        scale = false;
                        len   = 0;

                        if (uutDisplay != stdOutDisplay)
                        {
                            uutDisplay->clear();
                        }

                        stdOutDisplay->clear();
                        character->print(controller->stdOutVfd, controller->stdOutRegionId, 0, 'B');
                    }

                    if (buttons->isNextShortPressed())
                    {
                        UINT8 charValue = len;
                        character->print(controller->stdOutVfd, controller->stdOutRegionId, 2, '0' + (charValue / 10));
                        charValue = (charValue % 10);
                        character->print(controller->stdOutVfd, controller->stdOutRegionId, 3, '0' + (charValue / 1));

                        Bar::set(controller->uutVfd, 0, 0, scale, len);
                        Bar::set(controller->uutVfd, 0, 1, scale, len);

                        if (++len >= (ARRAYSIZE(SegmentGroupBar::pinS) + 2))
                        {
                            len = 0;
                            scale = !scale;
                        }
                    }
                    break;
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
                    }

                    if (buttons->isNextShortPressed())
                    {
                        SegmentGroupSymbol *p_symGroup;
                        UINT8 numSymEntries;

                        if (controller->uutVfd->layout->getSegmentGroupSymbol(&p_symGroup, &numSymEntries))
                        {
                            UINT8 sym  = pgm_read_byte_near(&p_symGroup[symGroupIndex].sym);
                            UINT8 instance = pgm_read_byte_near(&p_symGroup[symGroupIndex].instance);
                            UINT8 pinG = pgm_read_byte_near(&p_symGroup[symGroupIndex].pinG);
                            UINT8 pinS = pgm_read_byte_near(&p_symGroup[symGroupIndex].pinS);

                            if (symGroupIndex == 0)
                            {
                                uutDisplay->clear();
                            }

                            uutDisplay->setSegment(pinG, pinS, true);

                            character->print(controller->stdOutVfd, controller->stdOutRegionId, 0, '0' + instance);

                            UINT8 value = sym;
                            character->print(controller->stdOutVfd, controller->stdOutRegionId, 2, '0' + (value / 10));
                            value = (value % 10);
                            character->print(controller->stdOutVfd, controller->stdOutRegionId, 3, '0' + (value / 1));

                            if (++symGroupIndex >= numSymEntries)
                            {
                                symGroupIndex = 0;
                            }
                        }
                    }
                    break;
                }

                // Report free memory
                case 8:
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
                if (++currentApp > 8)
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
