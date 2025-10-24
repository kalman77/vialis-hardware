#pragma once
#include <ESP8266WiFi.h>

class WifiManager {
public:
    void begin(const char* ssid, const char* password);
    void loop();
};