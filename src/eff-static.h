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

#ifndef eff_static_H
#define eff_static_H

#include "light-effect.h"

/**
 * @brief Static color
 *
 * Fill all the pixels with `color`.
 * The fill is performed in the first call then only if the color changes.
 */
class StaticEffect : public LightEffect
{
public:
    StaticEffect(void) {}
    virtual ~StaticEffect() {}

    ColorWRGB color;

    bool Step(uint32_t timeMS) {
        cycleCompleted = true;
        if (stepIdx == 0) {
            prevColor = color;
            Fill(prevColor);
            ++stepIdx;
            return true;
        }

        if (color == prevColor)
            return false;

        prevColor = color;
        Fill(prevColor);
        return true;
    }

protected:
    ColorWRGB prevColor;
};

#endif
