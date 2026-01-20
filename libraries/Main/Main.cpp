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
#include "Display.h"
#include "Char7Seg.h"
#include "LayoutFinder.h"

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

#define BUTTON_PIN_1 (2)
#define BUTTON_PIN_2 (3)
#define BUTTON_PIN_3 (7)

// AN5818 Digital pin mappings

#define AN5818_STROBE (1) // Rising edge clocked
#define AN5818_BLANK (9)  // Hi == All outputs disabled

// On board LED

#define LED_BUILTIN (13)

void Main(IVfdPinout *vfdPinout, IVfdLayout7Seg *vfdLayout7Seg)
{
    Buttons *buttons = new Buttons(
        BUTTON_PIN_1,
        BUTTON_PIN_2,
        BUTTON_PIN_3);

    // in case we crash
    if (buttons->isB1Pressed())
    {
        return;
    }

    Display *display = new Display(
        vfdPinout,
        AN5818_STROBE,
        AN5818_BLANK);

    ICharacter *char7seg = new Char7Seg(
        vfdLayout7Seg,
        display);

    // The LayoutFinder app
    IApp *app = new LayoutFinder(
        buttons,
        display,
        char7seg);

    // Main loop
    while (1)
    {
        if (display->scan())
        {
            app->run();
        }
    }
};
