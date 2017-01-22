#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

class GpioDriver
{
public:
    GpioDriver(int pin);
    virtual ~GpioDriver();

    virtual void configureForOutput() = 0;
    virtual void configureForInput() = 0;
    virtual void configureForInputPullup() = 0;

    virtual void setHigh() = 0;
    virtual void setLow() = 0;

    virtual bool isHigh() = 0;
    virtual bool isLow() = 0;

    virtual bool isHighWithDebounce(int debounceTime = 100) = 0;
    virtual bool isLowWithDebounce(int debounceTime = 100) = 0;

protected:
    int _pin;

private:
    // intentionally not implemented
    GpioDriver();
};

#endif
