#pragma once

#include "core/realtime.hpp"

class Joystick {
private:
    IRealtime* realtime;
public:
    Joystick(IRealtime* rt);
    void begin();
    void loop();
    int readX();
    int readY();
    bool pressed();
};