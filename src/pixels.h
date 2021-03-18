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

#ifndef pixels_H
#define pixels_H

#include <stddef.h>
#include <stdint.h>

/**
 * @brief Pixels keep the info about a memory buffer formatted for LightEffects.
 *
 * Each pixel should be 4 bytes. This is hardcoded here but for clean external acces
 * the BytesPerPixel function should be used by other functions
 *
 * @warning Pixels does not own the data ! The owner of the data should
 *          call Pixels::CleanUp() then destroy the data.
 */
class Pixels
{
public:
    Pixels(void);
    virtual ~Pixels();

    /**
     * @brief Set the memory buffer info
     *
     * @param stripData the buffer
     * @param dataLen the length of the buffer
     * @param stripLen the number of LEDs
     * @return true if correct data was provided
     */
    bool Set(uint8_t *stripData, uint16_t dataLen, uint16_t stripLen);

    /**
     * @brief Remove the info about the memory buffer
     */
    void CleanUp(void);

    /**
     * @brief Return the memory buffer
     */
    uint8_t* Data(void) { return data; }

    /**
     * @brief Return the number of pixels for current memory buffer
     */
    uint16_t StripLength(void) { return stripLength; }

    /**
     * @brief Return the number of bytes allocated per pixel
     */
    uint8_t BytesPerPixel(void) { return bytesPerPixel; }

    /**
     * @brief Set the color from a 32-bit WRGB value
     *
     * @param idx the index of the the pixel
     * @param wrgb MSB is White, followed by R, G and B
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

protected:
    uint8_t *data; // the memory buffer for pixels
    uint16_t stripLength; // the number of pixels

    const uint8_t bytesPerPixel = 4;
};

#endif
