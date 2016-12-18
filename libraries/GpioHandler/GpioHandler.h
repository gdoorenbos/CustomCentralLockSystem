#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

class GpioHandler
{
public:
    GpioHandler();
    ~GpioHandler();

    virtual void configurePinForOutput(int pin) = 0;
    virtual void configurePinForInput(int pin) = 0;
};

#endif
