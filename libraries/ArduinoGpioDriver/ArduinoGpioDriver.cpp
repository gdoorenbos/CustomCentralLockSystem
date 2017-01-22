#include "ArduinoGpioDriver.h"
#include "arduino.h"

ArduinoGpioDriver::ArduinoGpioDriver(int pin)
    : _pin(pin)
{
}

ArduinoGpioDriver::~ArduinoGpioDriver()
{
}

void ArduinoGpioDriver::configureForOutput()
{
    pinMode(_pin, OUTPUT);
}

void ArduinoGpioDriver::configureForInput()
{
    pinMode(_pin, INPUT);
}

void ArduinoGpioDriver::configureForInputPullup()
{
    pinMode(_pin, INPUT_PULLUP);
}

void ArduinoGpioDriver::setHigh()
{
    digitalWrite(_pin, HIGH);
}

void ArduinoGpioDriver::setLow()
{
    digitalWrite(_pin, LOW);
}

bool ArduinoGpioDriver::isHigh() const
{
    return digitalRead(_pin) == HIGH;
}

bool ArduinoGpioDriver::isLow() const
{
    return digitalRead(_pin) == LOW;
}

bool readWithDebounce(int debounceTime, int highOrLow) const
{
    if( digitalRead(_pin) == highOrLow )
    {
        delay(debounceTime);
        return digitalRead(_pin) == highOrLow;
    }
    return false;
}

bool ArduinoGpioDriver::isHighWithDebounce(int debounceTime) const
{
    readWithDebounce(debounceTime, HIGH);
}

bool ArduinoGpioDriver::isLowWithDebounce(int debounceTime) const
{
    readWithDebounce(debounceTime, LOW);
}
