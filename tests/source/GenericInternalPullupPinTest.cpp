#include "GenericInternalPullupPin.h"
#include "MockGpioDriver.h"
#include "gtest/gtest.h"

TEST(GenericInternalPullupPin, basicFunction)
{
    MockGpioDriver* pinDriver = new MockGpioDriver(0);
    GenericInternalPullupPin testPin(pinDriver);

    // assert pin configuration
    ASSERT_TRUE(pinDriver->isConfiguredForInputPullup());

    // assert idle state: voltage high, logic low
    ASSERT_TRUE(pinDriver->isHigh());
    ASSERT_TRUE(testPin.isLogicLow());

    // artificially pull voltage low, assert logic high
    pinDriver->setLow();
    ASSERT_TRUE(pinDriver->isLow());
    ASSERT_TRUE(testPin.isLogicHigh());
}
