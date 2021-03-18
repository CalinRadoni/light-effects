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

#include "pixels.h"

#include <new>

Pixels::Pixels(void)
{
    data = nullptr;
    stripLength = 0;
}

Pixels::~Pixels(void)
{
    //
}

bool Pixels::Set(uint8_t *stripData, uint16_t dataLen, uint16_t stripLen)
{
    data = stripData;
    stripLength = stripLen;

    if (data == nullptr) {
        CleanUp();
        return false;
    }

    if (stripLength == 0) {
        CleanUp();
        return false;
    }

    if (dataLen != stripLength * bytesPerPixel) {
        CleanUp();
        return false;
    }

    return true;
}

void Pixels::CleanUp(void)
{
    data = nullptr;
    stripLength = 0;
}

void Pixels::SetColor(uint16_t idx, uint32_t wrgb)
{
    if (idx >= stripLength) return;

    uint8_t *pixel = data;
    pixel += idx * bytesPerPixel;
    pixel += bytesPerPixel;

    --pixel;
    *pixel = (uint8_t)(wrgb & 0xFF);

    wrgb = wrgb >> 8;
    --pixel;
    *pixel = (uint8_t)(wrgb & 0xFF);

    wrgb = wrgb >> 8;
    --pixel;
    *pixel = (uint8_t)(wrgb & 0xFF);

    wrgb = wrgb >> 8;
    --pixel;
    *pixel = (uint8_t)(wrgb & 0xFF);
}

void Pixels::SetColor(uint16_t idx, uint8_t r, uint8_t g, uint8_t b)
{
    if (idx >= stripLength) return;

    uint8_t *pixel = data;
    pixel += idx * bytesPerPixel;

    *pixel = 0; ++pixel;
    *pixel = r; ++pixel;
    *pixel = g; ++pixel;
    *pixel = b;
}

void Pixels::SetColor(uint16_t idx, uint8_t w, uint8_t r, uint8_t g, uint8_t b)
{
    if (idx >= stripLength) return;

    uint8_t *pixel = data;
    pixel += idx * bytesPerPixel;

    *pixel = w; ++pixel;
    *pixel = r; ++pixel;
    *pixel = g; ++pixel;
    *pixel = b;
}
