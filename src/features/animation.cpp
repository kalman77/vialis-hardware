#include "state.hpp"
#include "features/animation.hpp"
#include "utils/logger.hpp"
#include "config.hpp"
#include <Arduino.h>
#include <hardware/led_controller.hpp>

AnimationManager::AnimationManager(LedController* controller)
    : ledController(controller) {}

void AnimationManager::toggle()
{
    running = !running;
}

void AnimationManager::loop()
{
    if (!state.animationOn)
        return;

    unsigned long now = millis();
    if (now - state.lastUpdate >= (unsigned long)state.speedDelay)
    {
        state.lastUpdate = now;

        ledController->setColor(currentR, currentG, currentB);

        if (state.currentLED >= NUM_LEDS - 1 && state.static_index != -1)
        {
            state.static_index = -1;
        }

        if (state.currentLED == 0 && state.static_index != 1)
        {
            state.static_index = 1;
        }

        state.currentLED += state.static_index;
    }
}

void AnimationManager::stop() 
{ 
    running = false;
}

void AnimationManager::start() 
{ 
    running = true; 
}

void AnimationManager::setSpeed(int ms)
{
    state.speedDelay = ms;
}

void AnimationManager::setCurrentColor(uint8_t r, uint8_t g, uint8_t b)
{
    currentR = r;
    currentG = g;
    currentB = b;
}

bool AnimationManager::isRunning() const 
{ 
    return running; 
}