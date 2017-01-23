#include "GenericOutputPin.h"
#include "MockGpioDriver.h"
#include "gtest/gtest.h"

TEST(GenericOutputPin, initialConfiguration)
{
    MockGpioDriver* pinDriver = new MockGpioDriver();
    GenericOutputPin outputPin(pinDriver);

    ASSERT_TRUE(pinDriver->isConfiguredForOutput());
    ASSERT_TRUE(pinDriver->isLow());
}

TEST(GenericOutputPin, setLowHigh)
{
    MockGpioDriver* pinDriver = new MockGpioDriver();
    GenericOutputPin outputPin(pinDriver);

    outputPin.setHigh();
    ASSERT_FALSE(pinDriver->isLow());
    ASSERT_TRUE(pinDriver->isHigh());

    outputPin.setLow();
    ASSERT_TRUE(pinDriver->isLow());
    ASSERT_FALSE(pinDriver->isHigh());
}
