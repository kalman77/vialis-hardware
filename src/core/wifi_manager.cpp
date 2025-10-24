#include "core/wifi_manager.hpp"
#include "utils/logger.hpp"

void WifiManager::begin(const char* ssid, const char* password) {
    Logger::info("Connecting to Wi-Fi...");
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, password);
    Logger::info("Access Point started: " + String(ssid));
}

void WifiManager::loop() {
    // nothing for now
}