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

#include "color-wrgb.h"

class LightEffect
{
public:
    LightEffect(void);
    virtual ~LightEffect();

    /**
     * @brief Initialize the effect.
     *
     * @param buffer is the memory buffer
     * @param buffLen is the size in bytes of the memory buffer
     *
     * @return true on success
     */
    virtual bool Initialize(uint8_t *buffer, uint16_t buffLen) {
        data = buffer;
        stripLen = buffLen / bytesPerPixel;
        stepIdx = 0;
        cycleCompleted = false;
        return data != nullptr;
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
        if (data == nullptr) return false;
        if (timeMS > 1) ++stepIdx;
        return true;
    }

    /**
     * @brief Check if a cycle is completed
     *
     * Returns true if the last computed step was the last step of a cycle.
     */
    bool CycleCompleted(void) { return cycleCompleted; }

    /**
     * @brief Clean up
     */
    virtual void CleanUp(void) {
        data = nullptr;
        stripLen = 0;
    }

protected:
    uint8_t *data;
    uint16_t stripLen;

    const uint8_t bytesPerPixel = 4;

    uint32_t stepIdx;
    bool cycleCompleted;
    uint32_t lastCallTime;
    uint32_t elapsedTime;

    /**
     * @brief Set the color from a 32-bit WRGB value
     */
    void SetColor(uint16_t idx, uint32_t wrgb);

    /**
     * @brief Set the color from individual components, white = 0
     */
    void SetColor(uint16_t idx, uint8_t r, uint8_t g, uint8_t b);

    /**
     * @brief Set the color from individual components
     */
    void SetColor(uint16_t idx, uint8_t w, uint8_t r, uint8_t g, uint8_t b);

    void Fill(uint8_t r, uint8_t g, uint8_t b);
    void Fill(uint8_t w, uint8_t r, uint8_t g, uint8_t b);
    void Fill(ColorWRGB&);
};

#endif
