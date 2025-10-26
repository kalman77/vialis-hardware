#include "core/websocket_manager.hpp"
#include <ArduinoJson.h>

using namespace websockets;

WebsocketManager::WebsocketManager(BrightnessController* brightness)
    : brightness(brightness), server() {}

void WebsocketManager::begin() {
    server.listen(81);
    Serial.println("WebSocket server listening on port 81");
}

void WebsocketManager::loop() {
    // Accept new clients if available
    auto newClient = server.accept();
    if (newClient.available()) {
        clients.push_back(newClient);
        Serial.println("New WebSocket client connected");
    }

    // Handle existing clients
    for (auto it = clients.begin(); it != clients.end();) {
        auto& client = *it;
        if (!client.available()) {
            ++it;
            continue;
        }

        auto msg = client.readBlocking(); // ✅ non-blocking
        if (msg.data().length() > 0) {
            handleMessage(client, msg);
        }

        if (!client.available()) { // disconnected?
            it = clients.erase(it);
        } else {
            ++it;
        }
    }
}

void WebsocketManager::handleMessage(WebsocketsClient& client,
                                     WebsocketsMessage msg) {
    String data = msg.data();
    Serial.println("[WS] Received: " + data);

    StaticJsonDocument<256> doc;
    auto err = deserializeJson(doc, data);
    if (err) {
        Serial.println("[WS] JSON parse error");
        return;
    }

    // Example: { "cmd":"setBrightness", "value": 150 }
    if (doc.containsKey("cmd")) {
        String cmd = doc["cmd"].as<String>();
        if (cmd == "setBrightness" && doc.containsKey("value")) {
            int v = doc["value"] | 128;
            if (brightness) brightness->set(v);

            StaticJsonDocument<128> out;
            out["event"] = "brightness";
            out["payload"]["value"] = v;
            String s;
            serializeJson(out, s);
            broadcast("brightness", s); // broadcast to all connected clients
        }
        // Handle other commands similarly...
    }
}

void WebsocketManager::broadcast(const String& event, const String& jsonPayload) {
    // Expect jsonPayload is either JSON object string or simple value string.
    // Wrap with envelope: {"event":"...", "payload": <parsed json or string>}
    StaticJsonDocument<256> doc;
    doc["event"] = event;

    // Try to parse jsonPayload into JSON; if fails, put as string
    StaticJsonDocument<128> payloadDoc;
    DeserializationError perr = deserializeJson(payloadDoc, jsonPayload);
    if (!perr) {
        doc["payload"] = payloadDoc.as<JsonVariant>();
    } else {
        // put raw string
        doc["payload"] = jsonPayload;
    }

    String out;
    serializeJson(doc, out);

    // send to all clients
    for (auto &c : clients) {
        if (c.available()) {
            c.send(out);
        }
    }
}
