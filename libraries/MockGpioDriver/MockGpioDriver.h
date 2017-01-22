#ifndef MOCK_GPIO_DRIVER
#define MOCK_GPIO_DRIVER

#include "GpioDriver.h"

class MockGpioDriver : public GpioDriver
{
public:
    MockGpioDriver(int pin);
    ~MockGpioDriver();

    void configureForOutput();
    void configureForInput();
    void configureForInputPullup();

    bool isConfiguredForOutput();
    bool isConfiguredForInput();
    bool isConfiguredForInputPullup();

    void setHigh();
    void setLow();

    bool isHigh();
    bool isLow();

    // these methods call straight though to isHigh() and isLow() - don't want delays in mock classes
    bool isHighWithDebounce(int debounceTime = 100);
    bool isLowWithDebounce(int debounceTime = 100);

private:
    bool outputConfigFlag;
    bool inputConfigFlag;
    bool inputPullupConfigFlag;
    bool pinIsLow;
    int lastDebounceTime;

    void resetConfigFlags();

    // intentionally not implemented
    MockGpioDriver();
};

#endif
