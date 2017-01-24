#ifndef GENERIC_INTERNAL_PULLUP_PIN_H
#define GENERIC_INTERNAL_PULLUP_PIN_H

class GpioDriver;

class InternalPullupPin
{
public:
    InternalPullupPin(GpioDriver* pinDriver);
    virtual ~InternalPullupPin();

    bool isLogicHigh() const;
    bool isLogicLow() const;

protected:
    GpioDriver* _pinDriver;

private:
    void pinSetup();
};

#endif
