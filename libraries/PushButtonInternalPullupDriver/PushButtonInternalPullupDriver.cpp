#include "PushButtonInternalPullupDriver.h"
#include <Arduino.h>

PushButtonInternalPullupDriver::PushButtonInternalPullupDriver(int pin)
    : buttonPin(pin)
{
    pinMode(buttonPin, INPUT_PULLUP);
}

PushButtonInternalPullupDriver::~PushButtonInternalPullupDriver()
{
}

bool PushButtonInternalPullupDriver::isPressed() const
{
    if( digitalRead(buttonPin) == LOW)
    {
        delay(100); // debounce
        return (digitalRead(buttonPin) == LOW);
    }
    return false;
}
