#include "ArduinoGpioHandler.h"
#include "Arduino.h"

ArduinoGpioHandler::ArduinoGpioHandler()
{
}

ArduinoGpioHandler::~ArduinoGpioHandler()
{
}

void ArduinoGpioHandler::configurePinForOutput(int pin)
{
    pinMode(pin, OUTPUT);
}

void ArduinoGpioHandler::configurePinForInput(int pin)
{
    pinMode(pin, INPUT);
}

void ArduinoGpioHandler::setPinHigh(int pin)
{
    digitalWrite(pin, HIGH);
}

void ArduinoGpioHandler::setPinLow(int pin)
{
    digitalWrite(pin, LOW);
}

bool ArduinoGpioHandler::isPinHigh(int pin)
{
    return digitalRead(pin) == HIGH;
}

bool ArduinoGpioHandler::isPinLow(int pin)
{
    return digitalRead(pin) == LOW;
}
