#pragma once

#include "hardware/led_controller.hpp"

class AnimationManager
{
    LedController* ledController;
    bool running = true;

public:
    explicit AnimationManager(LedController* controller);

    void toggle();
    void loop();
    void stop();
    void start();
    void setSpeed(int ms);
    bool isRunning() const;
};