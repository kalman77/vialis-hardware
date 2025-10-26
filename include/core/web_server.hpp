#pragma once
#include <ESP8266WebServer.h>
#include "features/animation.hpp"
#include "features/brightness.hpp"
#include "hardware/led_controller.hpp"
#include "config.hpp"
#include "realtime.hpp"

class WebServerManager {
private:
    ESP8266WebServer server;
    IRealtime* realtime;
    LedController* ledController;
    AnimationManager* animations;
    BrightnessController* brightness;

    void setupRoutes();
    void handleRoot();
    void handleStatus();
    void handleToggleAnimation();
    void handleSpeed();
    void handleBrightness();
    void handleColor();

public:
    explicit WebServerManager(LedController* led, AnimationManager* anim, BrightnessController* bright, IRealtime* rt);
    void begin();
    void loop();
};