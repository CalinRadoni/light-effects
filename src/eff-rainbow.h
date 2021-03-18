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

#ifndef eff_rainbow_H
#define eff_rainbow_H

#include "light-effect.h"
#include "color-hsv.h"

class RainbowEffect : public LightEffect
{
public:
    RainbowEffect(void) {}
    virtual ~RainbowEffect() {}

    bool rainbow_ce = true; // rainbow vs rainbow_ce. See ColorHSV class for details.
    bool increaseHue = true;
    uint8_t saturation = 0xFF;
    uint8_t value = 0xFF;
    uint8_t pixelStep = 1;
    uint32_t delay = 100;

    bool Step(uint32_t timeMS) {
        ColorHSV color;
        ColorWRGB rgb;
        uint32_t rainbowMod;

        cycleCompleted = false;
        if (stepIdx == 0) {
            elapsedTime = delay;
            lastCallTime = timeMS;
        }

        elapsedTime += timeMS - lastCallTime;
        lastCallTime = timeMS;

        if (elapsedTime < delay) return false;

        elapsedTime -= delay;

        rainbowMod = rainbow_ce ? 765 : 1530;
        color.s = saturation;
        color.v = value;
        color.h = stepIdx % rainbowMod;

        uint8_t *pixel = data;
        for (uint16_t i = 0; i < stripLen; ++i) {
            if (rainbow_ce) color.ToRGB_raw_ce(rgb);
            else            color.ToRGB_raw(rgb);
            *pixel = rgb.w; ++pixel;
            *pixel = rgb.r; ++pixel;
            *pixel = rgb.g; ++pixel;
            *pixel = rgb.b; ++pixel;

            if (increaseHue) color.h = (color.h + pixelStep) % rainbowMod;
            else             color.h = (color.h + rainbowMod - pixelStep) % rainbowMod;
        }

        ++stepIdx;
        if ((stepIdx % rainbowMod) == 0)
            cycleCompleted = true;
        return true;
    }
};

#endif
