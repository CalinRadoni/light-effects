#include <iostream>
#include <string>
#include <fstream>

#include "../src/color-wrgb.h"
#include "../src/color-hsv.h"
#include "../src/color-gamma.h"

int main()
{
    ColorWRGB rgb;
    ColorHSV color;
    Gamma gamma;
    uint16_t hue;
    uint8_t i;

    std::string ccc[13];

    uint8_t *gammaTable = gamma.GetTable();

    ccc[12] = "gg = [ ";
    i = 0;
    do {
        if (i != 0)
            ccc[12] += ", ";
        ccc[12] += std::to_string(gammaTable[i]);
        ++i;
    }
    while (i != 0);

    color.s = 255;
    color.v = 255;
    ccc[0] = "r1 = [ ";
    ccc[1] = "g1 = [ ";
    ccc[2] = "b1 = [ ";
    ccc[3] = "r2 = [ ";
    ccc[4] = "g2 = [ ";
    ccc[5] = "b2 = [ ";
    ccc[6] = "r3 = [ ";
    ccc[7] = "g3 = [ ";
    ccc[8] = "b3 = [ ";
    ccc[9] = "r4 = [ ";
    ccc[10] = "g4 = [ ";
    ccc[11] = "b4 = [ ";
    for (hue = 0; hue < 765; hue++) {
        if (hue != 0) {
            for (i = 0; i < 12; ++i)
                ccc[i] += ", ";
        }

        color.h = hue * 2 + 1;
        color.ToRGB_raw(rgb);
        ccc[0] += std::to_string(rgb.r);
        ccc[1] += std::to_string(rgb.g);
        ccc[2] += std::to_string(rgb.b);

        gamma.Apply(rgb);
        ccc[3] += std::to_string(rgb.r);
        ccc[4] += std::to_string(rgb.g);
        ccc[5] += std::to_string(rgb.b);

        color.h = hue;
        color.ToRGB_raw_cl(rgb);
        ccc[6] += std::to_string(rgb.r);
        ccc[7] += std::to_string(rgb.g);
        ccc[8] += std::to_string(rgb.b);

        gamma.Apply(rgb);
        ccc[9] += std::to_string(rgb.r);
        ccc[10] += std::to_string(rgb.g);
        ccc[11] += std::to_string(rgb.b);
    }

    std::ofstream file;
    file.open("hsvRainbow.py");
    for (i = 0; i < 13; ++i) {
        ccc[i] += " ]";
        file << ccc[i] << std::endl;
    }
    file.close();

    return 0;
}
