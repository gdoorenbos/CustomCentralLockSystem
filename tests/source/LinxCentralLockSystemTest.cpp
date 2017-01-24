#include "LinxCentralLockSystem.h"
#include "MockLinxRxModule.h"
#include "MockPowerLocksDriver.h"
#include "MockPushButtonDriver.h"
#include "MockGpioDriver.h"
#include "gtest/gtest.h"

class LinxCentralLockSystemTest : public ::testing::Test
{
protected:
    LinxCentralLockSystemTest()
        : rxer()
        , locksDriver()
        , lockButton()
        , unlockButton()
        , lcs(&rxer, &locksDriver, &lockButton, &unlockButton)
    {
    }

    ~LinxCentralLockSystemTest()
    {
    }

    void assertDoorsAreLocked()
    {
        ASSERT_TRUE(locksDriver.areDoorsLocked());
    }

    void assertDoorsAreUnlocked()
    {
        ASSERT_FALSE(locksDriver.areDoorsLocked());
    }

    MockLinxRxModule rxer;
    MockPowerLocksDriver locksDriver;
    MockPushButtonDriver lockButton;
    MockPushButtonDriver unlockButton;
    LinxCentralLockSystem lcs;
};

TEST_F(LinxCentralLockSystemTest, verifyButtonsWork)
{
    lockButton.press();
    lcs.run();
    lockButton.release();
    assertDoorsAreLocked();

    unlockButton.press();
    lcs.run();
    unlockButton.release();
    assertDoorsAreUnlocked();

    lockButton.press();
    lcs.run();
    lockButton.release();
    assertDoorsAreLocked();

    unlockButton.press();
    lcs.run();
    unlockButton.release();
    assertDoorsAreUnlocked();
}

TEST_F(LinxCentralLockSystemTest, verifyRxModuleWorks)
{
    rxer.raiseLockRequest();
    lcs.run();
    rxer.clearLockRequest();
    assertDoorsAreLocked();

    rxer.raiseUnlockRequest();
    lcs.run();
    rxer.clearUnlockRequest();
    assertDoorsAreUnlocked();

    rxer.raiseLockRequest();
    lcs.run();
    rxer.clearLockRequest();
    assertDoorsAreLocked();

    rxer.raiseUnlockRequest();
    lcs.run();
    rxer.clearUnlockRequest();
    assertDoorsAreUnlocked();
}

TEST_F(LinxCentralLockSystemTest, verifyLockHigherPriorityThanUnlock)
{
    lockButton.press();
    unlockButton.press();
    lcs.run();
    lockButton.release();
    unlockButton.release();
    assertDoorsAreLocked();
}

TEST_F(LinxCentralLockSystemTest, verifyButtonHigherPriorityThanWireless)
{
    lockButton.press();
    rxer.raiseUnlockRequest();
    lcs.run();
    rxer.clearUnlockRequest();
    lockButton.release();
    assertDoorsAreLocked();
}

