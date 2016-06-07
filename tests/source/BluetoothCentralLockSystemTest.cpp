#include "gtest/gtest.h"
#include "MockBluetoothDriver.h"
#include "MockPowerLocksDriver.h"
#include "MockPushButtonDriver.h"
// #include "BluetoothCentralLockSystem.h"

// todo: replace with real tests
TEST(BluetoothCentralLockSystemTest, dummy)
{
	MockBluetoothDriver bluetooth;
	MockPowerLocksDriver locks;
	MockPushButtonDriver lockButton;
	MockPushButtonDriver unlockButton;
	// BluetoothCentralLockSystem cls(&bluetooth, &locks, &lockButton, &unlockButton);
	EXPECT_TRUE(true);
}
