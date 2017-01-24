#include "MockLinxRxModule.h"
#include "MockGpioDriver.h"
#include "gtest/gtest.h"

class MockLinxRxModuleTest : public ::testing::Test
{
protected:
    MockLinxRxModuleTest()
        : rxer()
    {
    }

    MockLinxRxModule rxer;
};

TEST_F(MockLinxRxModuleTest, initialConditions)
{
    ASSERT_FALSE(rxer.isLockRequested());
    ASSERT_FALSE(rxer.isUnlockRequested());
}

TEST_F(MockLinxRxModuleTest, lockAndUnlockCycles)
{
    rxer.raiseLockRequest();
    ASSERT_TRUE(rxer.isLockRequested());
    ASSERT_FALSE(rxer.isUnlockRequested());
    rxer.clearLockRequest();

    rxer.raiseUnlockRequest();
    ASSERT_FALSE(rxer.isLockRequested());
    ASSERT_TRUE(rxer.isUnlockRequested());
    rxer.clearUnlockRequest();

    rxer.raiseLockRequest();
    ASSERT_TRUE(rxer.isLockRequested());
    ASSERT_FALSE(rxer.isUnlockRequested());
    rxer.clearLockRequest();

    rxer.raiseUnlockRequest();
    ASSERT_FALSE(rxer.isLockRequested());
    ASSERT_TRUE(rxer.isUnlockRequested());
    rxer.clearUnlockRequest();
}
