#pragma once

#include "hardware/led_controller.hpp"

class AnimationManager
{
    LedController* ledController;
    uint8_t currentR = 255, currentG = 0, currentB = 0;
    bool running = true;

public:
    explicit AnimationManager(LedController* controller);

    void toggle();
    void loop();
    void stop();
    void start();
    void setSpeed(int ms);
    void setCurrentColor(uint8_t, uint8_t, uint8_t);
    bool isRunning() const;
};