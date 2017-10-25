#include "MockLinxRxModule.h"
#include "gtest/gtest.h"

class LinxRxModuleTest : public ::testing::Test
{
protected:
    LinxRxModuleTest()
        : rxer()
    {
    }

    ~LinxRxModuleTest()
    {
    }

    MockLinxRxModule rxer;
};

TEST_F(LinxRxModuleTest, verifyLockUnlockRequests)
{
    ASSERT_FALSE(rxer.isLockRequested());
    ASSERT_FALSE(rxer.isUnlockRequested());

    rxer.raiseLockRequest();
    ASSERT_TRUE(rxer.isLockRequested());
    ASSERT_FALSE(rxer.isUnlockRequested());
    rxer.clearLockRequest();

    rxer.raiseUnlockRequest();
    ASSERT_FALSE(rxer.isLockRequested());
    ASSERT_TRUE(rxer.isUnlockRequested());
    rxer.clearUnlockRequest();
}
