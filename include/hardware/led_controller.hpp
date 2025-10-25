#pragma once

#include <Adafruit_NeoPixel.h>
#include "config.hpp"

class LedController {
private:
public:
    Adafruit_NeoPixel strip;
    LedController();
    void begin();
    void setColor(int, int, int);
    void setBrightness(uint8_t);
    uint32_t getColor() const;
    uint8_t getBrightness() const;
};