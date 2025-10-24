#include "features/brightness.hpp"
#include "utils/logger.hpp"
#include <Arduino.h>

BrightnessController::BrightnessController(LedController* controller)
    : ledController(controller) {}

void BrightnessController::begin() {
    ledController->setBrightness(brightness);
    Logger::info("Brightness initialized: " + String(brightness));
}

void BrightnessController::increase() {
    if (brightness < 250) brightness += 5;
    ledController->setBrightness(brightness);
}

void BrightnessController::decrease() {
    if (brightness > 5) brightness -= 5;
    ledController->setBrightness(brightness);
}

void BrightnessController::set(uint8_t value) {
    brightness = constrain(value, 0, 255);
    ledController->setBrightness(brightness);
}

uint8_t BrightnessController::get() const {
    return brightness;
}