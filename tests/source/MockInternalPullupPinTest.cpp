#include "MockInternalPullupPin.h"
#include "MockGpioDriver.h"
#include "gtest/gtest.h"

class MockInternalPullupPinTest : public ::testing::Test
{
protected:
    MockInternalPullupPinTest()
        : pinDriver(new MockGpioDriver())
        , testPin(pinDriver)
    {
    }

    ~MockInternalPullupPinTest()
    {
    }

    void assertLogicLow()
    {
        ASSERT_TRUE(pinDriver->isHigh());
        ASSERT_TRUE(testPin.isLogicLow());
    }

    void assertLogicHigh()
    {
        ASSERT_TRUE(pinDriver->isLow());
        ASSERT_TRUE(testPin.isLogicHigh());
    }

    MockGpioDriver* pinDriver;
    MockInternalPullupPin testPin;
};

TEST_F(MockInternalPullupPinTest, initialConfiguration)
{
    ASSERT_TRUE(pinDriver->isConfiguredForInputPullup());
    assertLogicLow();
}

TEST_F(MockInternalPullupPinTest, togglePin)
{
    testPin.setLogicHigh();
    assertLogicHigh();

    testPin.setLogicLow();
    assertLogicLow();

    testPin.setLogicHigh();
    assertLogicHigh();

    testPin.setLogicLow();
    assertLogicLow();
}
