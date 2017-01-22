#ifndef MOCK_PUSH_BUTTON_DRIVER_H
#define MOCK_PUSH_BUTTON_DRIVER_H

#include "PushButtonDriver.h"

class MockPushButtonDriver : public PushButtonDriver
{
public:
    MockPushButtonDriver();
    ~MockPushButtonDriver();

    void press();
    void release();
};

#endif
