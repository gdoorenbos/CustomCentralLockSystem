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
