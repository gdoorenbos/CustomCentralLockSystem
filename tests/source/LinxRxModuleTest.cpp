#include "LinxRxModule.h"
#include "MockGpioDriver.h"
#include "gtest/gtest.h"

TEST(LinxRxModule, initialConditions)
{
    MockGpioDriver* lockReqPin = new MockGpioDriver();
    MockGpioDriver* unlockReqPin = new MockGpioDriver();
    LinxRxModule rxer(lockReqPin, unlockReqPin);

    ASSERT_FALSE(rxer.isLockRequested());
    ASSERT_FALSE(rxer.isUnlockRequested());
}

TEST(LinxRxModule, lockAndUnlockCycles)
{
    MockGpioDriver* lockReqPin = new MockGpioDriver();
    MockGpioDriver* unlockReqPin = new MockGpioDriver();
    LinxRxModule rxer(lockReqPin, unlockReqPin);

    lockReqPin->setLow();
    ASSERT_TRUE(rxer.isLockRequested());
    ASSERT_FALSE(rxer.isUnlockRequested());
    lockReqPin->setHigh();

    unlockReqPin->setLow();
    ASSERT_FALSE(rxer.isLockRequested());
    ASSERT_TRUE(rxer.isUnlockRequested());
    unlockReqPin->setHigh();

    lockReqPin->setLow();
    ASSERT_TRUE(rxer.isLockRequested());
    ASSERT_FALSE(rxer.isUnlockRequested());
    lockReqPin->setHigh();

    unlockReqPin->setLow();
    ASSERT_FALSE(rxer.isLockRequested());
    ASSERT_TRUE(rxer.isUnlockRequested());
    unlockReqPin->setHigh();
}
