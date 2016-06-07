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

TEST(MockBluetoothDriver, singleClientMessageSentAndReceived)
{
	MockBluetoothDriver bluetooth;
	const char* clientMessage = "hello world";

	EXPECT_FALSE(bluetooth.hasMessage());
	bluetooth.sendMessageFromDevice(clientMessage);
	EXPECT_TRUE(bluetooth.hasMessage());
	const char* reportedMessage = bluetooth.getMessage();
	EXPECT_FALSE(bluetooth.hasMessage());
	EXPECT_STREQ(reportedMessage, clientMessage);

	delete[] reportedMessage;
}

/* When a client device sends a second message before the first one
 * gets read, the second message should be ignored. 
 */
TEST(MockBluetoothDriver, twoMessagesFromClientBeforeRead)
{
	const char* firstMessage = "foo";
	const char* secondMessage = "bar";
	MockBluetoothDriver bluetooth;

	EXPECT_FALSE(bluetooth.hasMessage());
	bluetooth.sendMessageFromDevice(firstMessage);
	EXPECT_TRUE(bluetooth.hasMessage());
	bluetooth.sendMessageFromDevice(secondMessage);
	EXPECT_TRUE(bluetooth.hasMessage());
	const char* reportedMessage = bluetooth.getMessage();
	EXPECT_FALSE(bluetooth.hasMessage());
	EXPECT_STREQ(reportedMessage, firstMessage);

	delete[] reportedMessage;
}

TEST(MockBluetoothDriver, twoMessagesFromClientReadOnTime)
{
	const char* firstMessage = "foo";
	const char* secondMessage = "bar";
	MockBluetoothDriver bluetooth;

	EXPECT_FALSE(bluetooth.hasMessage());
	bluetooth.sendMessageFromDevice(firstMessage);
	EXPECT_TRUE(bluetooth.hasMessage());
	const char* reportedMessage = bluetooth.getMessage();
	EXPECT_FALSE(bluetooth.hasMessage());
	EXPECT_STREQ(reportedMessage, firstMessage);
	delete[] reportedMessage;

	bluetooth.sendMessageFromDevice(secondMessage);
	EXPECT_TRUE(bluetooth.hasMessage());
	reportedMessage = bluetooth.getMessage();
	EXPECT_FALSE(bluetooth.hasMessage());
	EXPECT_STREQ(reportedMessage, secondMessage);
	delete[] reportedMessage;
}

TEST(MockBluetoothDriver, singleMessageToClient)
{
	const char* messageForClient = "foo";
	MockBluetoothDriver bluetooth;

	EXPECT_FALSE(bluetooth.hasMessageForClient());
	bluetooth.sendString(messageForClient);
	EXPECT_TRUE(bluetooth.hasMessageForClient());
	const char* reportedMessage = bluetooth.getMessageForClient();
	EXPECT_FALSE(bluetooth.hasMessageForClient());
	EXPECT_STREQ(reportedMessage, messageForClient);
	delete[] reportedMessage;
}

TEST(MockBluetoothDriver, twoMessagesSentToClient)
{
	const char* firstMessage = "foo";
	const char* secondMessage = "bar";
	const char* expectedMessage = "foobar";
	MockBluetoothDriver bluetooth;

	EXPECT_FALSE(bluetooth.hasMessageForClient());
	bluetooth.sendString(firstMessage);
	EXPECT_TRUE(bluetooth.hasMessageForClient());
	bluetooth.sendString(secondMessage);
	EXPECT_TRUE(bluetooth.hasMessageForClient());
	const char* reportedMessage = bluetooth.getMessageForClient();
	EXPECT_FALSE(bluetooth.hasMessageForClient());
	EXPECT_STREQ(reportedMessage, expectedMessage);
	delete[] reportedMessage;
}
