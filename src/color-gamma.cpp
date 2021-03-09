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

#include <cmath>

#include "color-gamma.h"

Gamma::Gamma(void)
{
    BuildTable(gammaFactor);
}
Gamma::Gamma(float factor)
{
    BuildTable(factor);
}
Gamma::~Gamma()
{
    //
}

void Gamma::Apply(ColorWRGB &rgb)
{
    rgb.w = gammaTable[rgb.w];
    rgb.r = gammaTable[rgb.r];
    rgb.g = gammaTable[rgb.g];
    rgb.b = gammaTable[rgb.b];
}

void Gamma::BuildTable(float factor)
{
    float val;
    gammaFactor = factor;

    uint8_t i = 0;
    do {
        val = 255 * pow((float)i / 255, gammaFactor) + 0.5;
        gammaTable[i++] = (uint8_t)val;
    }
    while (i != 0);
}

uint8_t* Gamma::GetTable(void)
{
    return gammaTable;
}

float Gamma::GetFactor(void)
{
    return gammaFactor;
}
