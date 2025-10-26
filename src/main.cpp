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
#include "core/websocket_manager.hpp"

WifiManager wifi;
LedController leds;
AnimationManager animations(&leds);
BrightnessController brightness(&leds);
WebsocketManager wsManager(&brightness);
WebServerManager webServer(&leds, &animations, &brightness, (IRealtime*)&wsManager);
Joystick joystick((IRealtime*)&wsManager);

void setup() {
    Serial.begin(9600);
    Logger::info("System boot...");

    wifi.begin(state.ssid, state.pswd);
    webServer.begin();
    wsManager.begin();

    leds.begin();
    joystick.begin();

    Logger::info("Setup complete.");
}

void loop() {
    wifi.loop();
    webServer.loop();
    //wsManager.loop();
    joystick.loop();
    animations.loop();
}
