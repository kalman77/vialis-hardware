<<<<<<< HEAD
#include "state.hpp"
#include "hardware/led_controller.hpp"

LedController::LedController() : 
    strip(NUM_LEDS, PIN_WS2812B, NEO_GRB + NEO_KHZ800) {}

void LedController::begin()
=======
#include "led_controller.hpp"

void initLEDs()
>>>>>>> dae31fb (commit for switching to new computer)
{
    strip.begin();
    strip.show();
}

<<<<<<< HEAD
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
=======
void updateAnimation(uint8_t r, uint8_t g, uint8_t b)
{
    if (!animationOn)
        return;

    unsigned long now = millis();
    if (now - lastUpdate >= (unsigned long)speedDelay)
    {
        lastUpdate = now;

        strip.clear();
        strip.setPixelColor(currentLED, strip.Color(r, g, b));
        strip.show();

        if (currentLED >= NUM_LEDS - 1 && static_index != -1)
        {
            static_index = -1;
        }

        if (currentLED == 0 && static_index != 1)
        {
            static_index = 1;
        }

        currentLED += static_index;
    }
>>>>>>> dae31fb (commit for switching to new computer)
}