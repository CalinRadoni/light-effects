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
#include "color-hsv.h"
#include "color-gamma.h"

enum class Effect : uint8_t {
    delay = 0,
    color = 1,
    blink = 2,
    rainbow = 3
};

class LightEffect
{
public:
    LightEffect(void);
    virtual ~LightEffect();

    /**
     * @brief Set the Data Buffer object
     *
     * @param buffer is the memory buffer
     * @param buffLen is the size in bytes of the memory buffer
     */
    void SetDataBuffer(uint8_t *buffer, uint16_t buffLen);

    /**
     * @brief Initialize the effect.
     */
    void Initialize(Effect);

    ColorWRGB color0, color1, color2;
    uint32_t delay0{0}, delay1{0}, delay2{0};
    ColorHSV hsvBase;
    bool hueInc{true};
    uint8_t hueStep{1};
    bool constantEnergy{false};
    bool useGammaCorrection{false};
    bool stopWhenCycleCompleted{false};

    bool IsRunning(void);

    void Stop(void);

    void RebuildGammaTable(float factor);

    /**
     * @brief Compute a new step.
     *
     * Computes a new step if enough miliseconds have passed.
     *
     * @return true if a new step was computed
     * @return false if data buffer was not changed
     */
    bool Step(uint32_t timeMS);

protected:
    uint8_t *data{nullptr};
    uint16_t stripLen{0};
    Effect effect{Effect::delay};
    Gamma gamma;

    const uint8_t bytesPerPixel = 4;

    uint32_t stepIdx{0};
    uint32_t nextRunTime{0};
    bool cycleCompleted{false};

    bool running{false};

    ColorWRGB prevColor;

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

    bool StepDelay(void);
    bool StepColor(void);
    bool StepBlink(void);
    bool StepRainbow(void);
};

#endif
