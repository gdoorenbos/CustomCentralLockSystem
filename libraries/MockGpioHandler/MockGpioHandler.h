#ifndef MOCK_GPIO_HANDLER_H
#define MOCK_GPIO_HANDLER_H

#include "GpioHandler.h"
#include <set>

class MockGpioHandler : public GpioHandler
{
public:
    MockGpioHandler();
    ~MockGpioHandler();

    void configurePinForOutput(int pin);
    void configurePinForInput(int pin);

    bool isPinConfiguredForOutput(int pin);
    bool isPinConfiguredForInput(int pin);

private:
    std::set<int> outputPins;
    std::set<int> inputPins;
};

#endif
