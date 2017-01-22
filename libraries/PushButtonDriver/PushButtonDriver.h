#ifndef PUSH_BUTTON_DRIVER_H
#define PUSH_BUTTON_DRIVER_H

#include "GenericInternalPullupPin.h"

class PushButtonDriver : public GenericInternalPullupPin
{
public:
    PushButtonDriver(GpioDriver* pinDriver);
    virtual ~PushButtonDriver();
    
    bool isPressed() const;
};

#endif
