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

#ifndef color_wrgb_H
#define color_wrgb_H

#include <stddef.h>
#include <stdint.h>

class ColorHSV;

class ColorWRGB
{
public:
    uint8_t w = 0;
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    // constructors

    ColorWRGB(void) {}

    ColorWRGB(uint8_t iw, uint8_t ir, uint8_t ig, uint8_t ib) : w(iw), r(ir), g(ig), b(ib) {}

    ColorWRGB(uint8_t ir, uint8_t ig, uint8_t ib) : r(ir), g(ig), b(ib) {}

    ColorWRGB(uint32_t val);

    ColorWRGB(uint8_t *val);

    ColorWRGB(ColorHSV&);

    // operators

    ColorWRGB& operator=(const ColorWRGB &rhs) {
        w = rhs.w; r = rhs.r; g = rhs.g; b = rhs.b;
        return *this;
    }

    bool operator==(const ColorWRGB &rgb) {
        return ((w == rgb.w) && (r == rgb.r) && (g == rgb.g) && (b == rgb.b));
    }
    bool operator!=(const ColorWRGB &rgb) {
        return ((w != rgb.w) || (r != rgb.r) || (g != rgb.g) || (b != rgb.b));
    }

    // functions to set the values

    void Set(uint8_t iw, uint8_t ir, uint8_t ig, uint8_t ib) {
        w = iw; r = ir; g = ig; b = ib;
    }

    void Set(uint8_t ir, uint8_t ig, uint8_t ib) {
        w = 0; r = ir; g = ig; b = ib;
    }

    void Set(uint32_t val);

    void Set(uint8_t *val);

    void Set(ColorHSV&);

    // functions to output values

    void ToBytePtr(uint8_t *val);
};

#endif
