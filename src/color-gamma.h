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

#ifndef color_gamma_H
#define color_gamma_H

#include <stddef.h>
#include <stdint.h>

#include "color-wrgb.h"

class Gamma
{
public:
    Gamma(void);
    Gamma(float factor);
    virtual ~Gamma();

    /**
     * @brief Applies gamma correction to a ColorWRGB object
     */
    void Apply(ColorWRGB&);

    void BuildTable(float factor);
    uint8_t* GetTable(void);
    float GetFactor(void);

protected:
    // default gamma correction factor
    float gammaFactor = 2.2;

    /**
     * @brief Gamma correction table
     *
     * This table is built by:
     * - the default constructor using the default gamma correction factor
     * - the parametrized constructor using the user supplied factor
     * - the function BuildTable
     */
    uint8_t gammaTable[256] = {0};
};

#endif
