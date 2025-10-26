#pragma once
#include <Arduino.h>
#include <vector>
#include <ArduinoJson.h>
#include <ArduinoWebsockets.h>
#include "realtime.hpp"
#include "features/brightness.hpp"

class WebsocketManager : public IRealtime {
public:
    explicit WebsocketManager(BrightnessController* brightness);

    void begin();
    void loop();

    void broadcast(const String& event, const String& payload) override;

private:
    websockets::WebsocketsServer server;
    std::vector<websockets::WebsocketsClient> clients;
    BrightnessController* brightness;

    void handleMessage(websockets::WebsocketsClient& client,
                       websockets::WebsocketsMessage message);
};
