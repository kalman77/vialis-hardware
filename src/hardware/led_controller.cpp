#include "state.hpp"
#include "hardware/led_controller.hpp"

LedController::LedController() : 
    strip(NUM_LEDS, PIN_WS2812B, NEO_GRB + NEO_KHZ800) {}

void LedController::begin()
{
    strip.begin();
    strip.show();
}

void LedController::setColor(int r, int g, int b)
{
    strip.clear();
    strip.setPixelColor(state.currentLED, strip.Color(r, g, b));
    strip.show();
    state.r = r;
    state.g = g;
    state.b = b;
}

void LedController::setBrightness(uint8_t value)
{
    strip.setBrightness(value);
    strip.show();
}

uint32_t LedController::getColor() const 
{
    return strip.getPixelColor(0);
}

uint8_t LedController::getBrightness() const
{
    return strip.getBrightness();
}