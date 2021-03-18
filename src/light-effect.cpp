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

#include "light-effect.h"

LightEffect::LightEffect(void)
{
    pixels = nullptr;
    stepIdx = 0;
    cycleCompleted = false;
    lastCallTime = 0;
    elapsedTime = 0;
}

LightEffect::~LightEffect(void)
{
    //
}

void LightEffect::Fill(uint8_t r, uint8_t g, uint8_t b)
{
    if (pixels == nullptr) return;

    uint16_t len = pixels->StripLength();
    uint8_t *data = pixels->Data();
    while (len > 0) {
        *data = 0; ++data;
        *data = r; ++data;
        *data = g; ++data;
        *data = b; ++data;
        --len;
    }
}

void LightEffect::Fill(uint8_t w, uint8_t r, uint8_t g, uint8_t b)
{
    if (pixels == nullptr) return;

    uint16_t len = pixels->StripLength();
    uint8_t *data = pixels->Data();
    while (len > 0) {
        *data = w; ++data;
        *data = r; ++data;
        *data = g; ++data;
        *data = b; ++data;
        --len;
    }
}

void LightEffect::Fill(ColorWRGB &rgb)
{
    if (pixels == nullptr) return;

    uint16_t len = pixels->StripLength();
    uint8_t *data = pixels->Data();
    while (len > 0) {
        *data = rgb.w; ++data;
        *data = rgb.r; ++data;
        *data = rgb.g; ++data;
        *data = rgb.b; ++data;
        --len;
    }
}
