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

    bool isHigh() const;
    bool isLow() const;

    bool isHighWithDebounce(int debounceTime = 100) const;
    bool isLowWithDebounce(int debounceTime = 100) const;

private:
    int _pin;

    bool readWithDebounce(int debounceTime, int highOrLow) const;

    // intentionally not implemented
    ArduinoGpioDriver();
};

#endif
