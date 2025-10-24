#include "state.hpp"
#include "hardware/joystick.hpp"
#include "config.hpp"
#include <Arduino.h>

void Joystick::begin() {
    pinMode(JOY_SW, INPUT_PULLUP);
}

int Joystick::readX() { return analogRead(JOY_X); }
int Joystick::readY() { return analogRead(JOY_Y); }
bool Joystick::pressed() { return digitalRead(JOY_SW) == LOW; }

void Joystick::loop() {
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck < 50) return; // check every 50ms
    lastCheck = millis();

    int xValue = analogRead(JOY_X);

    // --- LEFT / RIGHT handling ---
    static bool moved = false;  

    if (xValue < 400 && !moved) {       // LEFT
        state.speedDelay = min(state.speedDelay * 2, 2000); 
        // Serial.println("Joystick LEFT → Slower speed: " + String(speedDelay));
        moved = true;
    } 
    else if (xValue > 600 && !moved) {  // RIGHT
        state.speedDelay = max(state.speedDelay / 2, 100);
        // Serial.println("Joystick RIGHT → Faster speed: " + String(speedDelay));
        moved = true;
    } 
    else if (xValue >= 400 && xValue <= 600) {
        moved = false; 
    }

    // --- Joystick Button ---
    static unsigned long lastPress = 0;
    if (digitalRead(JOY_SW) == LOW && millis() - lastPress > 200) {
        state.animationOn = !state.animationOn;
        // Serial.println(animationOn ? "Animation ON" : "Animation OFF");
        lastPress = millis(); // debounce via millis
    }

    yield(); // let WiFi handle its stuff
}