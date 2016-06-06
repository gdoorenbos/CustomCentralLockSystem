#ifndef MOCK_PUSH_BUTTON_DRIVER
#define MOCK_PUSH_BUTTON_DRIVER

#include <PushButtonDriver.h>

class MockPushButtonDriver : public PushButtonDriver
{
public:
    MockPushButtonDriver();
    ~MockPushButtonDriver();

    void press();
    void release();
    bool isPressed() const;

private:
    bool buttonIsPressed;
};

#endif
