#ifndef MOCK_INTERNAL_PULLUP_PIN_H
#define MOCK_INTERNAL_PULLUP_PIN_H

#include "InternalPullupPin.h"

class MockGpioDriver;

class MockInternalPullupPin : public InternalPullupPin
{
public:
    MockInternalPullupPin(MockGpioDriver* pinDriver);
    MockInternalPullupPin();
    ~MockInternalPullupPin();

    // mock method for testing
    void setLogicHigh();
    void setLogicLow();
};

#endif
