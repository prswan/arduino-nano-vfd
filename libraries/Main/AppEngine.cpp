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

#include "AppEngine.h"
#include "VfdStdOut.h"


void AppEngine(Controller *controller, AppEngineMenu *menu)
{
    Buttons*   buttons           = controller->buttons;
    VfdStdOut* stdOut            = controller->stdOut;
    Vfd*       appEngineVfd      = controller->appEngineVfd;
    UINT8      appEngineRegionId = controller->appEngineRegionId;

    UINT8 currentMenuIndex = 0;
    bool firstPass = true;

    // AppEngine loop
    while (1)
    {
        if (!controller->timer->run())
        {
            continue;
        }

        // Invoke any defined background tasks
        for (UINT8 i = 0 ; menu[i].description[0] != 0 ; i++)
        {
            if (menu[i].run != NULL)
            {
                menu[i].run(controller);
            }
        }

        // Select press or it's the first time through after power on
        if (buttons->isSelectShortPressed() || firstPass)
        {
            // Deselect the current app
            if ((menu[currentMenuIndex].onDeSelect != NULL) && !firstPass)
            {
                menu[currentMenuIndex].onDeSelect(controller);
            }

            //
            // Loop through to find the next menu item with an onSelect callback
            // This allows for pure runCallback background only apps.
            //
            do
            {
                if (menu[++currentMenuIndex].description[0] == 0)
                {
                    currentMenuIndex = 0;
                }
            }
            while (menu[currentMenuIndex].onSelect == NULL);

            // Update the display for the App description we're selecting
            stdOut->print(appEngineVfd, 
                          appEngineRegionId,
                          "\f");

            stdOut->print(appEngineVfd, 
                          appEngineRegionId,
                          menu[currentMenuIndex].description);

            menu[currentMenuIndex].onSelect(controller);

            firstPass = false;
        }

        if (buttons->isNextShortPressed())
        {
            if (menu[currentMenuIndex].onNextShortPress != NULL)
            {
                menu[currentMenuIndex].onNextShortPress(controller);
            }
        }

        if (buttons->isNextLongPressed())
        {
            if (menu[currentMenuIndex].onNextLongPress != NULL)
            {
                menu[currentMenuIndex].onNextLongPress(controller);
            }
        }
    }
};
