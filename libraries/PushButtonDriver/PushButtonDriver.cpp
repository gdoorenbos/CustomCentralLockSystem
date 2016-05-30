#include "PushButtonDriver.h"
#include <Arduino.h>

PushButtonDriver::PushButtonDriver(int pin, bool isPullDown)
    : buttonPin(pin)
    , isPullDown(isPullDown)
{
}

PushButtonDriver::~PushButtonDriver()
{
}

bool PushButtonDriver::isButtonPressed()
{
    if( isPullDown )
        return (digitalRead(buttonPin) == LOW);
    else
        return (digitalRead(buttonPin) == HIGH);
}
