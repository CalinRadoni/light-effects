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

// do not change this value ! There are no checks is code !
const uint8_t bytesPerPixel = 4;

Pixels::Pixels(void)
{
    length = 0;
    data = nullptr;
}

Pixels::~Pixels(void)
{
    Destroy();
}

bool Pixels::Create(uint16_t numberOfPixels)
{
    Destroy();

    if (numberOfPixels == 0) return true;

    uint32_t reqLen = length * bytesPerPixel;
    data = new (std::nothrow) uint8_t[reqLen];
    if (data == nullptr) {
        return false;
    }

    length = numberOfPixels;
    return true;
}

void Pixels::Destroy(void)
{
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    length = 0;
}

uint16_t Pixels::Length(void)
{
    return length;
}

uint8_t* Pixels::Data(void)
{
    return data;
}

uint8_t Pixels::BytesPerPixel(void)
{
    return bytesPerPixel;
}

void Pixels::SetColor(uint16_t idx, uint32_t components)
{
    if (idx >= length) return;

    uint8_t *pixel = data;
    pixel += idx * bytesPerPixel;
    pixel += bytesPerPixel - 1;

    *pixel = (uint8_t)(components & 0xFF);
    --pixel;
    components = components >> 8;
    *pixel = (uint8_t)(components & 0xFF);
    --pixel;
    components = components >> 8;
    *pixel = (uint8_t)(components & 0xFF);
    --pixel;
    components = components >> 8;
    *pixel = (uint8_t)(components & 0xFF);
}

void Pixels::SetColor(uint16_t idx, uint8_t r, uint8_t g, uint8_t b)
{
    if (idx >= length) return;

    uint8_t *pixel = data;
    pixel += idx * bytesPerPixel;

    *pixel = 0; ++pixel;
    *pixel = r; ++pixel;
    *pixel = g; ++pixel;
    *pixel = b;
}

void Pixels::SetColor(uint16_t idx, uint8_t w, uint8_t r, uint8_t g, uint8_t b)
{
    if (idx >= length) return;

    uint8_t *pixel = data;
    pixel += idx * bytesPerPixel;

    *pixel = w; ++pixel;
    *pixel = r; ++pixel;
    *pixel = g; ++pixel;
    *pixel = b;
}
