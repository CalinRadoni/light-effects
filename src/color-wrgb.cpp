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

#include "color-wrgb.h"
#include "color-hsv.h"

ColorWRGB::ColorWRGB(uint32_t val)
{
    b = (uint8_t)(val & 0xFF); val = val >> 8;
    g = (uint8_t)(val & 0xFF); val = val >> 8;
    r = (uint8_t)(val & 0xFF); val = val >> 8;
    w = (uint8_t)(val & 0xFF);
}

ColorWRGB::ColorWRGB(uint8_t *val)
{
    if (val == nullptr) return;
    uint8_t *ptr = val;
    w = *ptr++; r = *ptr++; g = *ptr++; b = *ptr;
}

ColorWRGB::ColorWRGB(ColorHSV &hsv)
{
    hsv.ToRGB_raw(*this);
}

void ColorWRGB::Set(uint32_t val) {
    b = (uint8_t)(val & 0xFF); val = val >> 8;
    g = (uint8_t)(val & 0xFF); val = val >> 8;
    r = (uint8_t)(val & 0xFF); val = val >> 8;
    w = (uint8_t)(val & 0xFF);
}

void ColorWRGB::Set(uint8_t *val) {
    if (val == nullptr) return;
    uint8_t *ptr = val;
    w = *ptr++; r = *ptr++; g = *ptr++; b = *ptr;
}

void ColorWRGB::Set(ColorHSV &hsv) {
    hsv.ToRGB_raw(*this);
}

void ColorWRGB::ToBytePtr(uint8_t *val) {
    if (val == nullptr) return;
    uint8_t *ptr = val;
    *ptr++ = w; *ptr++ = r; *ptr++ = g; *ptr = b;
}

uint32_t ColorWRGB::Get(void) {
    uint32_t val = w;
    val = val << 8; val |= r;
    val = val << 8; val |= g;
    val = val << 8; val |= b;
    return val;
}
