#include "gtest/gtest.h"
#include "MockPowerLocksDriver.h"

// helper functions
void expectLocked(MockPowerLocksDriver powerLocks)
{
	EXPECT_TRUE(powerLocks.areDoorsLocked());
}

void expectUnlocked(MockPowerLocksDriver powerLocks)
{
	EXPECT_FALSE(powerLocks.areDoorsLocked());
}

// tests
TEST(MockPowerLocksDriver, initializedUnlocked)
{
	MockPowerLocksDriver powerLocks;
	expectUnlocked(powerLocks);
}

TEST(MockPowerLocksDriver, properBehaviorWhenLocked)
{
	MockPowerLocksDriver powerLocks;
	powerLocks.lockDoors();
	expectLocked(powerLocks);
}

TEST(MockPowerLocksDriver, properBehaviorWhenUnlocked)
{
	MockPowerLocksDriver powerLocks;
	powerLocks.lockDoors();
	powerLocks.unlockDoors();
	expectUnlocked(powerLocks);
}

TEST(MockPowerLocksDriver, repetitiveLockss)
{
	MockPowerLocksDriver powerLocks;
	expectUnlocked(powerLocks);
	powerLocks.lockDoors();
	expectLocked(powerLocks);
	powerLocks.lockDoors();
	expectLocked(powerLocks);
	powerLocks.lockDoors();
	expectLocked(powerLocks);
	powerLocks.lockDoors();
	expectLocked(powerLocks);
	powerLocks.lockDoors();
	expectLocked(powerLocks);
}

TEST(MockPowerLocksDriver, repetitiveUnlocks)
{
	MockPowerLocksDriver powerLocks;
	expectUnlocked(powerLocks);
	powerLocks.unlockDoors();
	expectUnlocked(powerLocks);
	powerLocks.unlockDoors();
	expectUnlocked(powerLocks);
	powerLocks.unlockDoors();
	expectUnlocked(powerLocks);
	powerLocks.unlockDoors();
	expectUnlocked(powerLocks);
	powerLocks.unlockDoors();
	expectUnlocked(powerLocks);
}

TEST(MockPowerLocksDriver, repetitiveLockAndUnlockCycles)
{
	MockPowerLocksDriver powerLocks;
	expectUnlocked(powerLocks);
	powerLocks.lockDoors();
	expectLocked(powerLocks);
	powerLocks.unlockDoors();
	expectUnlocked(powerLocks);
	powerLocks.lockDoors();
	expectLocked(powerLocks);
	powerLocks.unlockDoors();
	expectUnlocked(powerLocks);
	powerLocks.lockDoors();
	expectLocked(powerLocks);
	powerLocks.unlockDoors();
	expectUnlocked(powerLocks);
	powerLocks.lockDoors();
	expectLocked(powerLocks);
	powerLocks.unlockDoors();
	expectUnlocked(powerLocks);
	powerLocks.lockDoors();
	expectLocked(powerLocks);
	powerLocks.unlockDoors();
	expectUnlocked(powerLocks);
}
