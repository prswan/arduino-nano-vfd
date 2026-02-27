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

/* TODO

 Print (Character ?) class (similar concepts Bar and Circle).
  - print
   - print7Seg::print
   - print5x7Matrix::print
   - print14Seg::print
  - takes the segment group map for columns (and rows if >1 row)
  There are other primatives that build on this - Numbers, Hex, Strings etc.
  - Those all build on single character print => separate class for string ops?

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

// Button Digitial pin mappings

#define BUTTON_PIN_NEXT   (3) // Increment
#define BUTTON_PIN_SELECT (2) // App Select

void Main(Controller *controller, ICharacter *character)
{
    Buttons *buttons = controller->buttons;

    // in case we crash
    if (buttons->isSelectActive())
    {
        return;
    }

    IDisplay *display = controller->vfd[0][0].display;

    // The LayoutFinder app
    IApp *app = new LayoutFinder(
        buttons,
        display,
        character);

    VfdStdOut *stdOut = new VfdStdOut(character);

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
                        display->setAllSegmentsOn();
                    }
                    break;
                }

                // Set all the pins on, effectively no scan.
                case 2:
                {
                    if (newApp)
                    {
                        //
                        // Only applicable to the ShiftRegister implementation.
                        // The integrated bit map driver IC's don't have pin control.
                        //
                        ShiftRegisterDisplay *shiftRegisterDisplay = (ShiftRegisterDisplay *) display;

                        shiftRegisterDisplay->clear();
                        shiftRegisterDisplay->setAllPins(true);
                    }
                    break;
                }

                // Clear all the Segments back to off
                case 3:
                {
                    if (newApp)
                    {
                        display->clear();
                    }
                    break;
                }

                // Performance measurment for the scan overhead.
                case 4:
                {
                    if (newApp)
                    {
                        display->clear();

                        stdOut->printf("\f%s", "TIME");
                    }

                    // This works because the run is only called when the display is scanned
                    static UINT32 previousTimeInUs = 0;

                    UINT32 currentTimeInUs = micros();
                    UINT16 elapsedTimeInUs = (UINT16)(currentTimeInUs - previousTimeInUs);

                    previousTimeInUs = currentTimeInUs;

                    if (buttons->isNextShortPressed())
                    {
                        elapsedTimeInUs = (elapsedTimeInUs % 10000);
                        character->print(0, 0, '0' + (elapsedTimeInUs / 1000));
                        elapsedTimeInUs = (elapsedTimeInUs % 1000);
                        character->print(0, 1, '0' + (elapsedTimeInUs / 100));
                        elapsedTimeInUs = (elapsedTimeInUs % 100);
                        character->print(0, 2, '0' + (elapsedTimeInUs / 10));
                        elapsedTimeInUs = (elapsedTimeInUs % 10);
                        character->print(0, 3, '0' + (elapsedTimeInUs / 1));
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

                        display->clear();
                        character->print(0, 0, '*');
                    }

                    if (buttons->isNextShortPressed())
                    {
                        if (++currentChar >= 0x60)
                        {
                            currentChar = 0x20;
                        }

                        character->print(0, 0, ' ');
                        character->print(0, 0, currentChar);

                        UINT8 charValue = currentChar;
                        character->print(0, 2, '0' + (charValue / 10));
                        charValue = (charValue % 10);
                        character->print(0, 3, '0' + (charValue / 1));
                    }
                    break;
                }

                default:
                break;
            }

            if (buttons->isSelectShortPressed())
            {
                if (++currentApp > 5)
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
