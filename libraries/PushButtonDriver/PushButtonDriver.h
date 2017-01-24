#ifndef PUSH_BUTTON_DRIVER_H
#define PUSH_BUTTON_DRIVER_H

#include "InternalPullupPin.h"

class PushButtonDriver : public InternalPullupPin
{
public:
    PushButtonDriver(GpioDriver* pinDriver);
    virtual ~PushButtonDriver();
    
    bool isPressed() const;
};

#endif
