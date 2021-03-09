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
 * @brief Pixels is a simple memory manager for lights
 *
 * Each pixel is 4 bytes, one for each of WRGB colors.
 */
class Pixels
{
public:
    Pixels(void);
    virtual ~Pixels();

    /**
     * @brief Create the array
     *
     * @param numberOfPixels the number of pixels in this object
     */
    bool Create(uint16_t numberOfPixels);

    /**
     * @brief Destroy the array
     */
    void Destroy(void);

    /**
     * @brief Return the number of pixels
     */
    uint16_t Length(void);

    /**
     * @brief Return a pointer to the allocated memory
     */
    uint8_t* Data(void);

    /**
     * @brief Return the number of bytes per pixel
     */
    uint8_t BytesPerPixel(void);

    /**
     * @brief Set the color from a 32-bit WRGB value
     *
     * MSB is White, followed by R, G and B
     */
    void SetColor(uint16_t idx, uint32_t components);

    /**
     * @brief Set the color from individual components, white = 0
     */
    void SetColor(uint16_t idx, uint8_t r, uint8_t g, uint8_t b);

    /**
     * @brief Set the color from individual components
     */
    void SetColor(uint16_t idx, uint8_t w, uint8_t r, uint8_t g, uint8_t b);

protected:
    uint16_t length; // number of pixels
    uint8_t *data; // the pixels
};

#endif
