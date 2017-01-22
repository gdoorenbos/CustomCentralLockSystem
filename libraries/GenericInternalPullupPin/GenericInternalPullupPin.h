#ifndef GENERIC_INTERNAL_PULLUP_PIN_H
#define GENERIC_INTERNAL_PULLUP_PIN_H

class GpioDriver;

class GenericInternalPullupPin
{
public:
    GenericInternalPullupPin(GpioDriver* pinDriver);
    virtual ~GenericInternalPullupPin();

    bool isLogicHigh() const;
    bool isLogicLow() const;

protected:
    GpioDriver* _pinDriver;

private:
    void pinSetup();
};

#endif
