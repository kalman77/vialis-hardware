#pragma once

#include <Adafruit_NeoPixel.h>
<<<<<<< HEAD
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
=======
#include "config.h"

Adafruit_NeoPixel strip(NUM_LEDS, PIN_WS2812B, NEO_GRB + NEO_KHZ800);

void initLEDs();
void updateAnimation(uint8_t, uint8_t, uint8_t);
>>>>>>> dae31fb (commit for switching to new computer)
