#pragma once
#include <Arduino.h>
#include <functional>

// Minimal interface for realtime notifications (ESP -> clients)
// Implementations must provide connect/init, loop, send.
class IRealtime {
public:
    virtual ~IRealtime() = default;
    virtual void broadcast(const String&, const String&) = 0;
};