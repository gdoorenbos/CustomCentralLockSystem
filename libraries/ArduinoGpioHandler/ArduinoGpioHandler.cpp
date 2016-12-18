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
