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
    data = nullptr;
    stripLen = 0;
    gamma = nullptr;
    stepIdx = 0;
    cycleCompleted = false;
    lastCallTime = 0;
    elapsedTime = 0;

    applyGammaCorrection = false;
}

LightEffect::~LightEffect(void)
{
    //
}

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

    if (applyGammaCorrection && (gamma != nullptr)) {
        uint8_t *gt = gamma->GetTable();
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

    if (applyGammaCorrection && (gamma != nullptr)) {
        uint8_t *gt = gamma->GetTable();
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

    if (applyGammaCorrection && (gamma != nullptr)) {
        uint8_t *gt = gamma->GetTable();
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

void LightEffect::Fill(uint8_t r, uint8_t g, uint8_t b)
{
    if (data == nullptr) return;

    ColorWRGB rgb(r, g, b);
    if (applyGammaCorrection && (gamma != nullptr)) gamma->Apply(rgb);

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
    if (applyGammaCorrection && (gamma != nullptr)) gamma->Apply(rgb);

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
    if (applyGammaCorrection && (gamma != nullptr)) gamma->Apply(rgb);

    uint8_t *pixel = data;
    for (uint16_t i = 0; i < stripLen; ++i) {
        *pixel = rgb.w; ++pixel;
        *pixel = rgb.r; ++pixel;
        *pixel = rgb.g; ++pixel;
        *pixel = rgb.b; ++pixel;
    }
}
