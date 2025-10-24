#pragma once
#include <Arduino.h>

class Logger 
{
public:
    static void info(const String&);
    static void error(const String&);
};