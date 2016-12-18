#include "MockGpioHandler.h"

MockGpioHandler::MockGpioHandler()
{
}

MockGpioHandler::~MockGpioHandler()
{
}

void MockGpioHandler::configurePinForOutput(int pin)
{
    outputPins.insert(pin);
}

void MockGpioHandler::configurePinForInput(int pin)
{
    inputPins.insert(pin);
}

bool MockGpioHandler::isPinConfiguredForOutput(int pin)
{
    return outputPins.find(pin) != outputPins.end();
}

bool MockGpioHandler::isPinConfiguredForInput(int pin)
{
    return inputPins.find(pin) != inputPins.end();
}
