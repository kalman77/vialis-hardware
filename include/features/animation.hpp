#pragma once

#include "hardware/led_controller.hpp"

class AnimationManager
{
    LedController* ledController;

public:
    explicit AnimationManager(LedController* controller);

    void toggle();
    void loop();
    void stop();
    void start();
    void setSpeed(int ms);
    bool isRunning() const;
};