#include "PushButtonDriver.h"
#include <Arduino.h>

PushButtonDriver::PushButtonDriver(int pin)
    : buttonPin(pin)
{
    pinMode(buttonPin, INPUT_PULLUP);
}

PushButtonDriver::~PushButtonDriver()
{
}

bool PushButtonDriver::isPressed() const
{
    if( digitalRead(buttonPin) == LOW)
    {
        delay(100); // debounce
        return (digitalRead(buttonPin) == LOW);
    }
    return false;
}
