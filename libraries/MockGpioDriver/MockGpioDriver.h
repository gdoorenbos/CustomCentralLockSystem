#ifndef MOCK_GPIO_DRIVER
#define MOCK_GPIO_DRIVER

#include "GpioDriver.h"
#include <string>

class MockGpioDriver : public GpioDriver
{
public:
    MockGpioDriver();
    ~MockGpioDriver();

    void configureForOutput();
    void configureForInput();
    void configureForInputPullup();

    bool isConfiguredForOutput();
    bool isConfiguredForInput();
    bool isConfiguredForInputPullup();

    void setHigh();
    void setLow();

    bool isHigh() const;
    bool isLow() const;

    // these methods call straight though to isHigh() and isLow() - don't want delays in mock classes
    bool isHighWithDebounce(int debounceTime = 100) const;
    bool isLowWithDebounce(int debounceTime = 100) const;

    std::string getLog();
    void clearLog();

private:
    bool outputConfigFlag;
    bool inputConfigFlag;
    bool inputPullupConfigFlag;
    bool pinIsLow;
    mutable int lastDebounceTime;
    std::string log;

    void resetConfigFlags();
};

#endif
