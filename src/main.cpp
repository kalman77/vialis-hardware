#include <Arduino.h>
#include "core/wifi_manager.hpp"
#include "core/web_server.hpp"
#include "hardware/led_controller.hpp"
#include "hardware/joystick.hpp"
#include "features/animation.hpp"
#include "features/brightness.hpp"
#include "utils/logger.hpp"
#include "config.hpp"
#include "state.hpp"
#include "config.hpp"

WifiManager wifi;
LedController leds;
Joystick joystick;
AnimationManager animations(&leds);
BrightnessController brightness(&leds);
WebServerManager webServer(&leds, &animations, &brightness);

void setup() {
    Serial.begin(115200);
    Logger::info("System boot...");

    wifi.begin(state.ssid, state.pswd);
    webServer.begin();

    leds.begin();
    joystick.begin();

    Logger::info("Setup complete.");
}

void loop() {
    wifi.loop();
    webServer.loop();
    joystick.loop();
    animations.loop();
}
