#include "MockGpioHandler.h"

MockGpioHandler::MockGpioHandler()
{
}

MockGpioHandler::~MockGpioHandler()
{
}

void MockGpioHandler::configurePinForOutput(int pin)
{
    // can't be both input and output
    if( isPinConfiguredForInput(pin) )
        inputPins.erase(pin);

    outputPins.insert(pin);
}

void MockGpioHandler::configurePinForInput(int pin)
{
    // can't be both input and output
    if( isPinConfiguredForOutput(pin) )
        outputPins.erase(pin);

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

void MockGpioHandler::setPinHigh(int pin)
{
    highPins.insert(pin);
}

void MockGpioHandler::setPinLow(int pin)
{
    if( isPinHigh(pin) )
        highPins.erase(pin);
}

bool MockGpioHandler::isPinHigh(int pin)
{
    return highPins.find(pin) != highPins.end();
}

bool MockGpioHandler::isPinLow(int pin)
{
    return highPins.find(pin) == highPins.end();
}
