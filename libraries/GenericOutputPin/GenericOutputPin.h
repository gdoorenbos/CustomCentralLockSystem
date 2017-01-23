#ifndef GENERIC_OUTPUT_PIN_H
#define GENERIC_OUTPUT_PIN_H

class GpioDriver;

class GenericOutputPin
{
public:
    GenericOutputPin(GpioDriver* pinDriver);
    virtual ~GenericOutputPin();

    void setLow();
    void setHigh();

private:
    GpioDriver* _pinDriver;

    // intentionally not implemented
    GenericOutputPin();
};

#endif
