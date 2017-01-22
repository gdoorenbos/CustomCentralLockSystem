#ifndef GENERIC_INTERNAL_PULLUP_PIN_H
#define GENERIC_INTERNAL_PULLUP_PIN_H

class GpioDriver;

class GenericInternalPullupPin
{
public:
    GenericInternalPullupPin(GpioDriver* pinDriver);
    virtual ~GenericInternalPullupPin();

    bool isLogicHigh();
    bool isLogicLow();

private:
    GpioDriver* _pinDriver;

    void pinSetup();
};

#endif
