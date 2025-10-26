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
    state.animationOn = !state.animationOn;
}

void AnimationManager::loop()
{
    if (!state.animationOn)
        return;

    unsigned long now = millis();
    if (now - state.lastUpdate >= (unsigned long)state.speedDelay)
    {
        Serial.print("SpeedDelay=");
        Serial.println(state.speedDelay);
        Serial.print("Delta=");
        Serial.println(now - state.lastUpdate);
        Serial.println(state.lastUpdate);
        state.lastUpdate = now;

        AnimationManager::ledController->strip.clear();
        AnimationManager::ledController->strip.setPixelColor(state.currentLED, AnimationManager::ledController->strip.Color(state.r, state.g, state.b));
        AnimationManager::ledController->strip.show();

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

bool AnimationManager::isRunning() const 
{ 
    return running; 
}