#ifndef PUSH_BUTTON_DRIVER_H
#define PUSH_BUTTON_DRIVER_H

class PushButtonDriver
{
public:
    PushButtonDriver(int pin);
    ~PushButtonDriver();

    bool isPressed() const;

private:
    PushButtonDriver(); // intentionally not implemented

    const int buttonPin;
};

#endif