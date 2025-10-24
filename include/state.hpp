#pragma once

#include <cstdint>

struct State
{
    uint8_t speedDelay = (uint8_t) 1000;
    uint8_t r = 255, g = 0, b = 0;
    bool animationOn = true;
    bool clientConnected = false;
    
    bool first = true;
    
    uint8_t currentLED = 0;
    unsigned long lastUpdate = 0;
    uint8_t static_index = 1;

    char *ssid = "ESP8266_AP";
    char *pswd = "123456789#";
};

extern State state;