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

    void setPinHigh(int pin);
    void setPinLow(int pin);

    bool isPinHigh(int pin);
    bool isPinLow(int pin);

private:
    std::set<int> outputPins;
    std::set<int> inputPins;
    std::set<int> highPins;
};

#endif
