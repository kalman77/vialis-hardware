#include "core/web_server.hpp"
#include "utils/logger.hpp"
#include <ArduinoJson.h>

WebServerManager::WebServerManager(
    LedController* led,
    AnimationManager* anim,
    BrightnessController* bright
) : server(80), ledController(led), animations(anim), brightness(bright) {}

void WebServerManager::begin() {
    setupRoutes();
    server.begin();
    Logger::info("Web server started on port 80");
}

void WebServerManager::loop() {
    server.handleClient();
}

void WebServerManager::setupRoutes() {
    server.on("/", [this]() { handleRoot(); });
    server.on("/status", [this]() { handleStatus(); });
    server.on("/toggle-animation", [this]() { handleToggleAnimation(); });
    server.on("/set-speed", [this]() { handleSpeed(); });
    server.on("/set-brightness", [this]() { handleBrightness(); });
    server.on("/set-color", [this]() { handleColor(); });

    server.onNotFound([this]() {
        server.send(404, "application/json", "{\"error\":\"Not found\"}");
    });
}

void WebServerManager::handleRoot() {
    server.send(200, "text/plain", "ESP32 LED Controller is online!");
}

void WebServerManager::handleStatus() {
    DynamicJsonDocument doc(256);
    doc["animation"] = animations->isRunning();
    doc["brightness"] = brightness->get();
    doc["speed"] = "controlled";
    String json;
    serializeJson(doc, json);
    server.send(200, "application/json", json);
}

void WebServerManager::handleToggleAnimation() {
    animations->toggle();
    server.send(200, "application/json",
        String("{\"animation\":") + (animations->isRunning() ? "true" : "false") + "}");
}

void WebServerManager::handleSpeed() {
    if (server.hasArg("value")) {
        int speed = server.arg("value").toInt();
        animations->setSpeed(speed);
        server.send(200, "application/json", "{\"status\":\"speed updated\"}");
    } else {
        server.send(400, "application/json", "{\"error\":\"missing value\"}");
    }
}

void WebServerManager::handleBrightness() {
    if (server.hasArg("value")) {
        int value = server.arg("value").toInt();
        brightness->set(value);
        server.send(200, "application/json", "{\"status\":\"brightness updated\"}");
    } else {
        server.send(400, "application/json", "{\"error\":\"missing value\"}");
    }
}

void WebServerManager::handleColor() {
    if (server.hasArg("r") && server.hasArg("g") && server.hasArg("b")) {
        int R = server.arg("r").toInt();
        int G = server.arg("g").toInt();
        int B = server.arg("b").toInt();
        ledController->setColor(R, G, B);
        server.send(200, "application/json", "{\"status\":\"color updated\"}");
    } else {
        server.send(400, "application/json", "{\"error\":\"missing RGB values\"}");
    }
}
