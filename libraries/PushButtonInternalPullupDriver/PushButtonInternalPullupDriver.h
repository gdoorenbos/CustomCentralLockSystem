#ifndef PUSH_BUTTON_INTERNAL_PULLUP_DRIVER_H
#define PUSH_BUTTON_INTERNAL_PULLUP_DRIVER_H

#include <PushButtonDriver.h>

class PushButtonInternalPullupDriver : public PushButtonDriver
{
public:
    PushButtonInternalPullupDriver(int pin);
    ~PushButtonInternalPullupDriver();

    bool isPressed() const;

private:
    PushButtonInternalPullupDriver(); // intentionally not implemented

    const int buttonPin;
};

#endif
