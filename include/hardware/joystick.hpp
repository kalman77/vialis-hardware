#pragma once

class Joystick {
public:
    void begin();
    void loop();
    int readX();
    int readY();
    bool pressed();
};