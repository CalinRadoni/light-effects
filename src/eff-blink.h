/**
This file is part of CalinRadoni/light-effects component
(https://github.com/CalinRadoni/light-effects)
Copyright (C) 2021 by Calin Radoni

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef eff_blink_H
#define eff_blink_H

#include "light-effect.h"

/**
 * @brief Blink between two colors
 *
 * Fill all the pixels with `color1` for `delay1` ms then with `color2` for `delay2` ms.
 */
class BlinkEffect : public LightEffect
{
public:
    BlinkEffect(void) {}
    virtual ~BlinkEffect() {}

    ColorWRGB color1, color2;
    uint32_t delay1, delay2;

    bool Step(uint32_t timeMS) {
        cycleCompleted = false;
        if (stepIdx == 0) {
            elapsedTime = delay1;
            lastCallTime = timeMS;
        }

        elapsedTime += timeMS - lastCallTime;
        lastCallTime = timeMS;

        if (stepIdx & 1) {
            if (elapsedTime >= delay2) {
                elapsedTime -= delay2;
                Fill(color2);
                ++stepIdx;
                cycleCompleted = true;
                return true;
            }
        }
        else {
            if (elapsedTime >= delay1) {
                elapsedTime -= delay1;
                Fill(color1);
                ++stepIdx;
                return true;
            }
        }

        return false;
    }
};

#endif
