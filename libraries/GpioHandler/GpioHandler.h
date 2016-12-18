#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

class GpioHandler
{
public:
    GpioHandler();
    virtual ~GpioHandler();

    virtual void configurePinForOutput(int pin) = 0;
    virtual void configurePinForInput(int pin) = 0;

    virtual void setPinHigh(int pin) = 0;
    virtual void setPinLow(int pin) = 0;
    void setPin(int pin, bool value);

    virtual bool isPinHigh(int pin) = 0;
    virtual bool isPinLow(int pin) = 0;
};

#endif
