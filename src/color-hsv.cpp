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

ColorHSV::ColorHSV(uint32_t val)
{
    v = (uint8_t) (val & 0x00FF); val = val >> 8;
    s = (uint8_t) (val & 0x00FF); val = val >> 8;
    h = (uint16_t)(val & 0xFFFF);
}

void ColorHSV::ToRGB_raw(ColorWRGB &rgb)
{
    uint8_t r, g, b;
    uint16_t hue = h;

    // 1530 values for hue

    if (hue < 255){         // Red to Yellow-1
        r = 255;
        g = hue;            // 0 -> 254
        b = 0;
    }
    else if (hue < 510) {   // Yellow to Green-1
        r = 510 - hue;      // 255 -> 1
        g = 255;
        b = 0;
    }
    else if (hue < 765) {   // Green to Cyan-1
        r = 0;
        g = 255;
        b = hue - 510;      // 0 -> 254
    }
    else if (hue < 1020) {  // Cyan to Blue-1
        r = 0;
        g = 1020 - hue;     // 255 -> 1
        b = 255;
    }
    else if (hue < 1275) {  // Blue to Magenta-1
        r = hue - 1020;     // 0 -> 254
        g = 0;
        b = 255;
    }
    else if (hue < 1530) {  // Magenta to Red-1
        r = 255;
        g = 0;
        b = 1530 - hue;     // 255 -> 1
    }
    else {
        r = 0; g = 0; b = 0;
    }

    ApplySV(r, g, b, rgb);
}

void ColorHSV::ToRGB_raw_cl(ColorWRGB &rgb)
{
    uint8_t r, g, b;
    uint16_t hue = h;

    // 765 values for hue

    if(hue < 255) {         // Red to Green-1
        r = 255 - hue;      // r: 255 -> 1
        g = hue;            // g: 0 -> 254
        b = 0;              // b: 0
    } else if(hue < 510) {  // Green to Blue-1
        r = 0;              // r: 0
        g = 510 - hue;      // g: 255 -> 1
        b = hue - 255;      // b: 0 -> 254
    } else if(hue < 765) {  // Blue to Red-1
        r = hue - 510;      // r: 0 -> 254
        g = 0;              // g: 0
        b = 765 - hue;      // b: 255 -> 1
    } else {
        r = 0; g = 0; b = 0;
    }

    ApplySV(r, g, b, rgb);

}

void ColorHSV::ApplySV(uint8_t rr, uint8_t gg, uint8_t bb, ColorWRGB &rgb)
{
    /**
     * Math things:
     *
     * let say b = 255
     *
     * V and S are [0..1] but v and s are [0..255]
     * chroma = V * S = v * s / b^2
     *
     * computed component is [0..255] but need to be [0..1]
     * so r is actually r / b
     *
     * m = V - C = v / b - v * s / b^2
     *
     * final r should be r + m then scaled from [0..1] to [0..255]
     *
     * 1. computed r scaled to [0..1]:
     *      r / b
     * 2. then scaled to [0..chroma]:
     *      r * v * s / b^3
     * 3. add m:
     *      r * v * s / b^3 + v / b - v * s / b^2
     *      = v * ( r * s / b^2 + 1 - s / b) / b
     * 4. scaled back to [0..255]:
     *      v * ( r * s / b^2 + 1 - s / b)
     *      = v * ( r * s / b + b - s ) / b
     *      = v * ( r * s + b * b - b * s) / b^2
     */

    uint16_t bms = 65025 - 255 * s;
    uint32_t res;
    res = rr * s + bms; res *= v; res /= 65025;
    rgb.r = (uint8_t) res;
    res = gg * s + bms; res *= v; res /= 65025;
    rgb.g = (uint8_t) res;
    res = bb * s + bms; res *= v; res /= 65025;
    rgb.b = (uint8_t) res;
}
