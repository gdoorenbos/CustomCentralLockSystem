#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

class GpioDriver
{
public:
    GpioDriver();
    virtual ~GpioDriver();

    virtual void configureForOutput() = 0;
    virtual void configureForInput() = 0;
    virtual void configureForInputPullup() = 0;

    virtual void setHigh() = 0;
    virtual void setLow() = 0;

    virtual bool isHigh() const = 0;
    virtual bool isLow() const = 0;

    virtual bool isHighWithDebounce(int debounceTime = 100) const = 0;
    virtual bool isLowWithDebounce(int debounceTime = 100) const = 0;
};

#endif
