# Light Effects

Platform independent implementation of light effects for LEDs.

This component was tested with [ESP-IDF](https://github.com/espressif/esp-idf) **v4.1**.

This is a *work-in-progress* and should be tested before use.

## Example app

To build the example application you need a working `make` and `g++` environment.

Compile and run the example application with the `build-and-run-example` script.

**Note**: this script will create a virtual environment and will install `Pillow` module for `python3`.

- `example/app` will create the file `hsvRainbow.py`
- using data from `hsvRainbow.py`, `example/buildImages.py` will create the files:
  - `example/hsvRainbow.png`, the rainbow as described in https://en.wikipedia.org/wiki/HSL_and_HSV (similar to Adafruit_NeoPixel::ColorHSV) - *only half the colors, 765, are used to provide a 1:1 visual comparison with* `example/hsvRainbowCL.png`
  - `example/hsvRainbowCL.png`, the rainbow with constant LED luminosity (similar to hsv2rgb_raw_C from FastLED)
  - `example/hsvRainbowGamma`, the two rainbows and their versions with gamma applied

## Tests

I will use it with `pax-LampD1`

## Development Environment

Currently uses the latest stable version of [Espressif IoT Development Framework](https://github.com/espressif/esp-idf), v4.1 as of December 2020.

Editing was done in [Visual Studio Code](https://code.visualstudio.com).

Version control with [Git](https://git-scm.com).

## License

This software and its documentation are released under the [GNU GPLv3](http://www.gnu.org/licenses/gpl-3.0.html) License. See the `LICENSE-GPLv3.txt` file.
