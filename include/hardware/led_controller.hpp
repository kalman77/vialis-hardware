#pragma once

#include <Adafruit_NeoPixel.h>
#include "config.hpp"

class LedController {
private:
    Adafruit_NeoPixel strip;
public:
    LedController();
    void begin();
    void setColor(uint8_t, uint8_t, uint8_t);
    void setBrightness(uint8_t);
    uint32_t getColor() const;
    uint8_t getBrightness() const;
};