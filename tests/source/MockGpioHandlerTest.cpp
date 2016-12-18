#include "MockGpioHandler.h"
#include "gtest/gtest.h"

TEST(MockGpioHandler, configurePinForOutput)
{
    MockGpioHandler gpioHandler;

    for( int i=0; i<10; ++i )
    {
        ASSERT_FALSE(gpioHandler.isPinConfiguredForOutput(i));
        gpioHandler.configurePinForOutput(i);
        ASSERT_TRUE(gpioHandler.isPinConfiguredForOutput(i));
    }
}

TEST(MockGpioHandler, configurePinForInput)
{
    MockGpioHandler gpioHandler;

    for( int i=0; i<10; ++i )
    {
        ASSERT_FALSE(gpioHandler.isPinConfiguredForInput(i));
        gpioHandler.configurePinForInput(i);
        ASSERT_TRUE(gpioHandler.isPinConfiguredForInput(i));
    }
}

TEST(MockGpioHandler, inputOutputClash)
{
    MockGpioHandler pinHandler;

    pinHandler.configurePinForInput(1);
    pinHandler.configurePinForOutput(1);
    ASSERT_FALSE(pinHandler.isPinConfiguredForInput(1));
    ASSERT_TRUE(pinHandler.isPinConfiguredForOutput(1));

    pinHandler.configurePinForOutput(2);
    pinHandler.configurePinForInput(2);
    ASSERT_FALSE(pinHandler.isPinConfiguredForOutput(2));
    ASSERT_TRUE(pinHandler.isPinConfiguredForInput(2));
}

TEST(MockGpioHandler, setPinHigh)
{
    MockGpioHandler gpioHandler;

    gpioHandler.setPinHigh(1);
    ASSERT_TRUE(gpioHandler.isPinHigh(1));
}

TEST(MockGpioHandler, setPinLow)
{
    MockGpioHandler pinHandler;
    pinHandler.setPinLow(1);
    ASSERT_TRUE(pinHandler.isPinLow(1));
}

TEST(MockGpioHandler, togglePinHighAndLow)
{
    MockGpioHandler pinHandler;

    pinHandler.setPinLow(1);
    ASSERT_TRUE(pinHandler.isPinLow(1));
    ASSERT_FALSE(pinHandler.isPinHigh(1));

    pinHandler.setPinHigh(1);
    ASSERT_TRUE(pinHandler.isPinHigh(1));
    ASSERT_FALSE(pinHandler.isPinLow(1));

    pinHandler.setPinLow(1);
    ASSERT_TRUE(pinHandler.isPinLow(1));
    ASSERT_FALSE(pinHandler.isPinHigh(1));
}
