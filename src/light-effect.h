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

#ifndef light_effect_H
#define light_effect_H

#include "pixels.h"
#include "color-wrgb.h"

class LightEffect
{
public:
    LightEffect(void);
    virtual ~LightEffect();

    /**
     * @brief Initialize the effect.
     *
     * @return true on success
     */
    virtual bool Initialize(Pixels *data) {
        pixels = data;
        stepIdx = 0;
        cycleCompleted = false;
        return pixels != nullptr;
    }

    /**
     * @brief Compute a new step.
     *
     * Computes a new step if enough miliseconds have passed.
     *
     * @note It should keeps track of elapsed time to allow resynchronization if multiple `Pixel` objects are used.
     *       This is why `lastCallTime` and `elapsedTime` are declared.
     *
     * @return true if a new step was computed
     */
    virtual bool Step(uint32_t timeMS) {
        if (pixels == nullptr) return false;
        if (timeMS > 1) ++stepIdx;
        return true;
    }

    /**
     * @brief Check if a cycle is completed
     *
     * Returns true if the last computed step was the last step of a cycle.
     */
    bool CycleCompleted(void) { return cycleCompleted; }

    virtual void CleanUp(void) { pixels = nullptr; }

protected:
    Pixels *pixels;
    uint32_t stepIdx;
    bool cycleCompleted;
    uint32_t lastCallTime;
    uint32_t elapsedTime;

    void Fill(uint8_t r, uint8_t g, uint8_t b);
    void Fill(uint8_t w, uint8_t r, uint8_t g, uint8_t b);
    void Fill(ColorWRGB&);
};

#endif
