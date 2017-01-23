#include "MockPowerLocksDriver.h"
#include "MockGpioDriver.h"
#include "gtest/gtest.h"

class MockPowerLocksDriverTest : public ::testing::Test
{
public:
    MockPowerLocksDriverTest()
        : lockCmdPin(new MockGpioDriver())
        , unlockCmdPin(new MockGpioDriver())
        , powerLocks(lockCmdPin, unlockCmdPin)
    {
        lockCmdPin->clearLog();
        unlockCmdPin->clearLog();
    }

    void assertLocked()
    {
        ASSERT_TRUE(powerLocks.areDoorsLocked());
        ASSERT_STREQ("", unlockCmdPin->getLog().c_str());
        ASSERT_STREQ("HL", lockCmdPin->getLog().c_str());
        lockCmdPin->clearLog();
    }

    void assertUnlocked()
    {
        ASSERT_FALSE(powerLocks.areDoorsLocked());
        ASSERT_STREQ("", lockCmdPin->getLog().c_str());
        ASSERT_STREQ("HL", unlockCmdPin->getLog().c_str());
        unlockCmdPin->clearLog();
    }

    MockGpioDriver* lockCmdPin;
    MockGpioDriver* unlockCmdPin;
    MockPowerLocksDriver powerLocks;
};

// tests
TEST_F(MockPowerLocksDriverTest, initialConfiguration)
{
    ASSERT_TRUE(lockCmdPin->isConfiguredForOutput());
    ASSERT_TRUE(unlockCmdPin->isConfiguredForOutput());
}

TEST_F(MockPowerLocksDriverTest, properBehaviorWhenLocked)
{
    powerLocks.lockDoors();
    assertLocked();
}

TEST_F(MockPowerLocksDriverTest, properBehaviorWhenUnlocked)
{
    powerLocks.unlockDoors();
    assertUnlocked();
}

TEST_F(MockPowerLocksDriverTest, repetitiveLockss)
{
    powerLocks.lockDoors();
    assertLocked();
    powerLocks.lockDoors();
    assertLocked();
    powerLocks.lockDoors();
    assertLocked();
    powerLocks.lockDoors();
    assertLocked();
    powerLocks.lockDoors();
    assertLocked();
}

TEST_F(MockPowerLocksDriverTest, repetitiveUnlocks)
{
    powerLocks.unlockDoors();
    assertUnlocked();
    powerLocks.unlockDoors();
    assertUnlocked();
    powerLocks.unlockDoors();
    assertUnlocked();
    powerLocks.unlockDoors();
    assertUnlocked();
    powerLocks.unlockDoors();
    assertUnlocked();
}

TEST_F(MockPowerLocksDriverTest, repetitiveLockAndUnlockCycles)
{
    powerLocks.lockDoors();
    assertLocked();
    powerLocks.unlockDoors();
    assertUnlocked();
    powerLocks.lockDoors();
    assertLocked();
    powerLocks.unlockDoors();
    assertUnlocked();
    powerLocks.lockDoors();
    assertLocked();
    powerLocks.unlockDoors();
    assertUnlocked();
    powerLocks.lockDoors();
    assertLocked();
    powerLocks.unlockDoors();
    assertUnlocked();
    powerLocks.lockDoors();
    assertLocked();
    powerLocks.unlockDoors();
    assertUnlocked();
}
