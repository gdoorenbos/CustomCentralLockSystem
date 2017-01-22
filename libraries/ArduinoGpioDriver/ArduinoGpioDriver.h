#ifndef ARDUINO_GPIO_DRIVER_H
#define ARDUINO_GPIO_DRIVER_H

#include "GpioDriver.h"

class ArduinoGpioDriver : public GpioDriver
{
public:
    ArduinoGpioDriver(int pin);
    ~ArduinoGpioDriver();

    void configureForOutput();
    void configureForInput();
    void configureForInputPullup();

    void setHigh();
    void setLow();

    bool isHigh();
    bool isLow();

    bool isHighWithDebounce(int debounceTime = 100);
    bool isLowWithDebounce(int debounceTime = 100);

private:
    bool readWithDebounce(int debounceTime, int highOrLow);

    // intentionally not implemented
    ArduinoGpioDriver();
};

#endif
