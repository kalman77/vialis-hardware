#pragma once
#include "hardware/led_controller.hpp"

class BrightnessController {
private:
    LedController* ledController;
    uint8_t brightness = 128; // 0–255

public:
    explicit BrightnessController(LedController* controller);

    void begin();
    void increase();
    void decrease();
    void set(uint8_t value);
    uint8_t get() const;
};