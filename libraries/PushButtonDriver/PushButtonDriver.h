#ifndef PUSH_BUTTON_DRIVER_H
#define PUSH_BUTTON_DRIVER_H

class PushButtonDriver
{
protected:
    // don't instantiate this class directly
    PushButtonDriver();

public:
    virtual ~PushButtonDriver();
    virtual bool isPressed() const = 0;
};

#endif
