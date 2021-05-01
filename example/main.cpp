#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

#include "../src/color-wrgb.h"
#include "../src/color-hsv.h"
#include "../src/color-gamma.h"

#include "../src/light-effect.h"

const uint16_t virtualLEDcount = 32;
const uint16_t bufferLen = virtualLEDcount * 4;
uint8_t buffer[bufferLen] = {0};

const uint32_t hexRed   = 0x00200000;
const uint32_t hexGreen = 0x00002000;
const uint32_t hexBlue  = 0x00000020;

LightEffect effect;

void PrintVirtualLEDs(void)
{
    uint16_t i =0;

    std::cout << std::setbase(16);
    while (i < virtualLEDcount) {
        uint32_t val = (buffer[4 * i] << 24) |
                       (buffer[4 * i + 1] << 16) |
                       (buffer[4 * i + 2] << 8) |
                        buffer[4 * i + 3];
        std::cout << std::setfill('0') << std::setw(8) << val;
        ++i;
        if (i % 8) std::cout << " ";
        else std::cout << std::endl;
    }
    std::cout << std::setbase(0);
}

void BuildBlinkAnimation(void)
{
    uint32_t elapsedTime = 0;
    uint32_t idx = 0;

    std::cout << "Blink animation" << std::endl;
    effect.Stop();
    effect.Initialize(Effect::blink);
    effect.color0.Set(hexRed);  effect.delay0 = 4;
    effect.color1.Set(hexBlue); effect.delay1 = 4;
    effect.useGammaCorrection = true;
    effect.stopWhenCycleCompleted = true;
    while (effect.IsRunning()) {
        if (effect.Step(elapsedTime)) {
            std::cout << "Time " << elapsedTime << " step " << idx++ << std::endl;
            PrintVirtualLEDs();
        }
        else {
            std::cout << "Time " << elapsedTime << std::endl;
        }
        ++elapsedTime;
    }
    std::cout << std::endl;
}

void BuildRainbowAnimation(void)
{
    uint32_t elapsedTime = 0;
    uint32_t idx = 0;

    std::cout << "Rainbow animation" << std::endl;
    effect.Stop();
    effect.Initialize(Effect::rainbow);
    effect.hsvBase.s = 0xFF;
    effect.hsvBase.v = 0xFF;
    effect.delay0 = 4;
    effect.useGammaCorrection = true;
    while (idx < 4) {
        if (effect.Step(elapsedTime)) {
            std::cout << "Time " << elapsedTime << " step " << idx++ << std::endl;
            PrintVirtualLEDs();
        }
        else {
            std::cout << "Time " << elapsedTime << std::endl;
        }
        ++elapsedTime;
    }
    std::cout << std::endl;
}

void BuildRainbowFiles(void)
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
        color.ToRGB_raw_ce(rgb);
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
}

int main()
{
    effect.SetDataBuffer(buffer, bufferLen);

    // BuildRainbowFiles();
    BuildBlinkAnimation();
    BuildRainbowAnimation();

    return 0;
}
