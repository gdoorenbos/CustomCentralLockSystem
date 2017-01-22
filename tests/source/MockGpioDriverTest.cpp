#include "MockGpioDriver.h"
#include "gtest/gtest.h"

void assertPinIsNotConfigured(MockGpioDriver &pin)
{
    ASSERT_FALSE(pin.isConfiguredForOutput());
    ASSERT_FALSE(pin.isConfiguredForInput());
    ASSERT_FALSE(pin.isConfiguredForInputPullup());
}

void assertPinIsConfiguredForOutput(MockGpioDriver &pin)
{
    ASSERT_TRUE(pin.isConfiguredForOutput());
    ASSERT_FALSE(pin.isConfiguredForInput());
    ASSERT_FALSE(pin.isConfiguredForInputPullup());
}

void assertPinIsConfiguredForInput(MockGpioDriver &pin)
{
    ASSERT_FALSE(pin.isConfiguredForOutput());
    ASSERT_TRUE(pin.isConfiguredForInput());
    ASSERT_FALSE(pin.isConfiguredForInputPullup());
}

void assertPinIsConfiguredForInputPullup(MockGpioDriver &pin)
{
    ASSERT_FALSE(pin.isConfiguredForOutput());
    ASSERT_FALSE(pin.isConfiguredForInput());
    ASSERT_TRUE(pin.isConfiguredForInputPullup());
}

TEST(MockGpioDriver, configureForOutput)
{
    MockGpioDriver testPin;

    assertPinIsNotConfigured(testPin);
    testPin.configureForOutput();
    assertPinIsConfiguredForOutput(testPin);
}

TEST(MockGpioDriver, configureForInput)
{
    MockGpioDriver testPin;

    assertPinIsNotConfigured(testPin);
    testPin.configureForInput();
    assertPinIsConfiguredForInput(testPin);
}

TEST(MockGpioDriver, configureForInputPullup)
{
    MockGpioDriver testPin;
    assertPinIsNotConfigured(testPin);
    testPin.configureForInputPullup();
    assertPinIsConfiguredForInputPullup(testPin);
    ASSERT_TRUE(testPin.isHigh());
}

TEST(MockGpioDriver, setHighLow)
{
    MockGpioDriver testPin;
    testPin.configureForOutput();
    ASSERT_TRUE(testPin.isLow());
    ASSERT_FALSE(testPin.isHigh());

    testPin.setHigh();
    ASSERT_FALSE(testPin.isLow());
    ASSERT_TRUE(testPin.isHigh());

    testPin.setLow();
    ASSERT_TRUE(testPin.isLow());
    ASSERT_FALSE(testPin.isHigh());
}
