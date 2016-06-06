#include "gtest/gtest.h"
#include "MockBluetoothDriver.h"

TEST(MockBluetoothDriver, noDeviceConnectedOnInitialization)
{
	MockBluetoothDriver bluetooth;
	EXPECT_FALSE(bluetooth.isDeviceConnected());
}

TEST(MockBluetoothDriver, flagSetWhenDeviceConnected)
{
	MockBluetoothDriver bluetooth;
	bluetooth.connectDevice();
	EXPECT_TRUE(bluetooth.isDeviceConnected());
}

TEST(MockBluetoothDriver, flagClearedWhenDeviceDisconnected)
{
	MockBluetoothDriver bluetooth;
	bluetooth.connectDevice();
	bluetooth.disconnectDevice();
	EXPECT_FALSE(bluetooth.isDeviceConnected());
}

TEST(MockBluetoothDriver, repetitiveDeviceConnectsAndDisconnects)
{
	MockBluetoothDriver bluetooth;
	EXPECT_FALSE(bluetooth.isDeviceConnected());
	bluetooth.connectDevice();
	EXPECT_TRUE(bluetooth.isDeviceConnected());
	bluetooth.disconnectDevice();
	EXPECT_FALSE(bluetooth.isDeviceConnected());
	bluetooth.connectDevice();
	EXPECT_TRUE(bluetooth.isDeviceConnected());
	bluetooth.disconnectDevice();
	EXPECT_FALSE(bluetooth.isDeviceConnected());
}

TEST(MockBluetoothDriver, properBehaviorWhenClientSendsMessage)
{
	MockBluetoothDriver bluetooth;
	const char* clientMessage = "hello world";

	EXPECT_FALSE(bluetooth.hasMessage());
	bluetooth.sendMessageFromDevice(clientMessage);
	EXPECT_TRUE(bluetooth.hasMessage());
	const char* reportedMessage = bluetooth.getMessage();
	EXPECT_FALSE(bluetooth.hasMessage());

	// string comparisons
	ASSERT_STREQ(reportedMessage, clientMessage);
	EXPECT_EQ(0, strcmp(reportedMessage, clientMessage));
}
