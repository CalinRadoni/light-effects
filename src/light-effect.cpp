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

// -----------------------------------------------------------------------------

LightEffect::LightEffect(void)
{
    //
}

LightEffect::~LightEffect(void)
{
    //
}

void LightEffect::SetDataBuffer(uint8_t *buffer, uint16_t buffLen)
{
    data = buffer;
    stripLen = buffLen / bytesPerPixel;
}

void LightEffect::Initialize(Effect eff)
{
    effect = eff;
    stepIdx = 0;
    lastCallTime = 0;
    elapsedTime = 0;
    running = true;
}

bool LightEffect::IsRunning(void)
{
    return running;
}

void LightEffect::Stop(void)
{
    running = false;
}

void LightEffect::RebuildGammaTable(float factor)
{
    gamma.BuildTable(factor);
}

// -----------------------------------------------------------------------------

void LightEffect::SetColor(uint16_t idx, uint32_t wrgb)
{
    if (idx >= stripLen) return;

    uint8_t *pixel = data;
    pixel += idx * bytesPerPixel;

    uint8_t w, r, g, b;

    b = (uint8_t)(wrgb & 0xFF); wrgb = wrgb >> 8;
    g = (uint8_t)(wrgb & 0xFF); wrgb = wrgb >> 8;
    r = (uint8_t)(wrgb & 0xFF); wrgb = wrgb >> 8;
    w = (uint8_t)(wrgb & 0xFF);

    if (useGammaCorrection) {
        uint8_t *gt = gamma.GetTable();
        *pixel = gt[w]; ++pixel;
        *pixel = gt[r]; ++pixel;
        *pixel = gt[g]; ++pixel;
        *pixel = gt[b];
    }
    else {
        *pixel = w; ++pixel;
        *pixel = r; ++pixel;
        *pixel = g; ++pixel;
        *pixel = b;
    }
}

void LightEffect::SetColor(uint16_t idx, uint8_t r, uint8_t g, uint8_t b)
{
    if (idx >= stripLen) return;

    uint8_t *pixel = data;
    pixel += idx * bytesPerPixel;

    if (useGammaCorrection) {
        uint8_t *gt = gamma.GetTable();
        *pixel = 0; ++pixel;
        *pixel = gt[r]; ++pixel;
        *pixel = gt[g]; ++pixel;
        *pixel = gt[b];
    }
    else {
        *pixel = 0; ++pixel;
        *pixel = r; ++pixel;
        *pixel = g; ++pixel;
        *pixel = b;
    }
}

void LightEffect::SetColor(uint16_t idx, uint8_t w, uint8_t r, uint8_t g, uint8_t b)
{
    if (idx >= stripLen) return;

    uint8_t *pixel = data;
    pixel += idx * bytesPerPixel;

    if (useGammaCorrection) {
        uint8_t *gt = gamma.GetTable();
        *pixel = gt[w]; ++pixel;
        *pixel = gt[r]; ++pixel;
        *pixel = gt[g]; ++pixel;
        *pixel = gt[b];
    }
    else {
        *pixel = w; ++pixel;
        *pixel = r; ++pixel;
        *pixel = g; ++pixel;
        *pixel = b;
    }
}

// -----------------------------------------------------------------------------

void LightEffect::Fill(uint8_t r, uint8_t g, uint8_t b)
{
    if (data == nullptr) return;

    ColorWRGB rgb(r, g, b);
    if (useGammaCorrection) gamma.Apply(rgb);

    uint8_t *pixel = data;
    for (uint16_t i = 0; i < stripLen; ++i) {
        *pixel = 0; ++pixel;
        *pixel = rgb.r; ++pixel;
        *pixel = rgb.g; ++pixel;
        *pixel = rgb.b; ++pixel;
    }
}

void LightEffect::Fill(uint8_t w, uint8_t r, uint8_t g, uint8_t b)
{
    if (data == nullptr) return;

    ColorWRGB rgb(w, r, g, b);
    if (useGammaCorrection) gamma.Apply(rgb);

    uint8_t *pixel = data;
    for (uint16_t i = 0; i < stripLen; ++i) {
        *pixel = rgb.w; ++pixel;
        *pixel = rgb.r; ++pixel;
        *pixel = rgb.g; ++pixel;
        *pixel = rgb.b; ++pixel;
    }
}

void LightEffect::Fill(ColorWRGB &rgbIn)
{
    if (data == nullptr) return;

    ColorWRGB rgb = rgbIn;
    if (useGammaCorrection) gamma.Apply(rgb);

    uint8_t *pixel = data;
    for (uint16_t i = 0; i < stripLen; ++i) {
        *pixel = rgb.w; ++pixel;
        *pixel = rgb.r; ++pixel;
        *pixel = rgb.g; ++pixel;
        *pixel = rgb.b; ++pixel;
    }
}

// -----------------------------------------------------------------------------

bool LightEffect::Step(uint32_t timeMS)
{
    if (data == nullptr) return false;

    if (!running) return false;

    if (stepIdx == 0) {
        elapsedTime = 0;
    }
    else {
        elapsedTime += timeMS - lastCallTime;
    }
    lastCallTime = timeMS;

    switch (effect) {
        case Effect::delay:   return StepDelay();
        case Effect::color:   return StepColor();
        case Effect::blink:   return StepBlink();
        case Effect::rainbow: return StepRainbow();
        default: break;
    }
    return false;
}

bool LightEffect::StepDelay(void)
{
    if (stepIdx == 0) {
        ++stepIdx;
    }
    if (elapsedTime >= delay0) {
        running = false;
    }
    return false;
}

bool LightEffect::StepColor(void)
{
    if (stepIdx == 0) {
        prevColor = color0;
        Fill(prevColor);
        ++stepIdx;
        return true;
    }

    if (color0 == prevColor)
        return false;

    prevColor = color0;
    Fill(prevColor);
    return true;
}

bool LightEffect::StepBlink(void)
{
    if (stepIdx == 0) {
        ++stepIdx;
        Fill(color0);
        return true;
    }

    if (stepIdx & 1) {
        if (elapsedTime >= delay0) {
            elapsedTime -= delay0;
            ++stepIdx;
            Fill(color1);
            return true;
        }
    }
    else {
        if (elapsedTime >= delay1) {
            elapsedTime -= delay1;
            if (stopWhenCycleCompleted) {
                running = false;
                return false;
            }
            else {
                ++stepIdx;
                Fill(color0);
                return true;
            }
        }
    }
    return false;
}

bool LightEffect::StepRainbow(void)
{
    ColorWRGB rgb;
    uint32_t rainbowMod;

    rainbowMod = constantEnergy ? 765 : 1530;
    hsvBase.h = stepIdx % rainbowMod;

    if (stepIdx > 0) {
        if (elapsedTime < delay0)
            return false;
        elapsedTime -= delay0;
    }

    uint8_t *pixel = data;
    for (uint16_t i = 0; i < stripLen; ++i) {
        if (constantEnergy) hsvBase.ToRGB_raw_ce(rgb);
        else                hsvBase.ToRGB_raw(rgb);

        if (useGammaCorrection) gamma.Apply(rgb);

        *pixel = rgb.w; ++pixel;
        *pixel = rgb.r; ++pixel;
        *pixel = rgb.g; ++pixel;
        *pixel = rgb.b; ++pixel;

        if (hueInc) hsvBase.h = (hsvBase.h + hueStep) % rainbowMod;
        else        hsvBase.h = (rainbowMod + hsvBase.h - hueStep) % rainbowMod;
    }

    ++stepIdx;
    if (stepIdx >= rainbowMod) {
        if (stopWhenCycleCompleted)
            running = false;
    }

    return true;
}
