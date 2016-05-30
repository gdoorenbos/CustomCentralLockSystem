#ifndef PUSH_BUTTON_DRIVER_H
#define PUSH_BUTTON_DRIVER_H

class PushButtonDriver
{
public:
    PushButtonDriver(int pin, bool isPullDown=true);
    ~PushButtonDriver();

    bool isButtonPressed();

private:
    PushButtonDriver(); // intentionally not implemented

    const int buttonPin;
    const bool isPullDown;
};

#endif