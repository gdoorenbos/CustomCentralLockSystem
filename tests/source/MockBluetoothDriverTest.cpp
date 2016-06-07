#include "gtest/gtest.h"
#include "MockBluetoothDriver.h"

TEST(MockBluetoothDriver, noClientConnectedOnInitialization)
{
	MockBluetoothDriver bluetooth;
	EXPECT_FALSE(bluetooth.isClientConnected());
}

TEST(MockBluetoothDriver, flagSetWhenClientConnected)
{
	MockBluetoothDriver bluetooth;
	bluetooth.connectClient();
	EXPECT_TRUE(bluetooth.isClientConnected());
}

TEST(MockBluetoothDriver, flagClearedWhenClientDisconnected)
{
	MockBluetoothDriver bluetooth;
	bluetooth.connectClient();
	bluetooth.disconnectClient();
	EXPECT_FALSE(bluetooth.isClientConnected());
}

TEST(MockBluetoothDriver, repetitiveClientConnectsAndDisconnects)
{
	MockBluetoothDriver bluetooth;
	EXPECT_FALSE(bluetooth.isClientConnected());
	bluetooth.connectClient();
	EXPECT_TRUE(bluetooth.isClientConnected());
	bluetooth.disconnectClient();
	EXPECT_FALSE(bluetooth.isClientConnected());
	bluetooth.connectClient();
	EXPECT_TRUE(bluetooth.isClientConnected());
	bluetooth.disconnectClient();
	EXPECT_FALSE(bluetooth.isClientConnected());
}

TEST(MockBluetoothDriver, singleClientMessageSentAndReceived)
{
	MockBluetoothDriver bluetooth;
	const char* clientMessage = "hello world";

	EXPECT_FALSE(bluetooth.hasMessage());
	bluetooth.sendMessageFromClient(clientMessage);
	EXPECT_TRUE(bluetooth.hasMessage());
	const char* reportedMessage = bluetooth.getMessage();
	EXPECT_FALSE(bluetooth.hasMessage());
	EXPECT_STREQ(reportedMessage, clientMessage);

	delete[] reportedMessage;
}

/* When a client sends a second message before the first one
 * gets read, the second message should be ignored. 
 */
TEST(MockBluetoothDriver, twoMessagesFromClientBeforeRead)
{
	const char* firstMessage = "foo";
	const char* secondMessage = "bar";
	MockBluetoothDriver bluetooth;

	EXPECT_FALSE(bluetooth.hasMessage());
	bluetooth.sendMessageFromClient(firstMessage);
	EXPECT_TRUE(bluetooth.hasMessage());
	bluetooth.sendMessageFromClient(secondMessage);
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
	bluetooth.sendMessageFromClient(firstMessage);
	EXPECT_TRUE(bluetooth.hasMessage());
	const char* reportedMessage = bluetooth.getMessage();
	EXPECT_FALSE(bluetooth.hasMessage());
	EXPECT_STREQ(reportedMessage, firstMessage);
	delete[] reportedMessage;

	bluetooth.sendMessageFromClient(secondMessage);
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

TEST(MockBluetoothDriver, sendThreeMessagesToClient)
{
	const char* firstMessage = "foo";
	const char* secondMessage = "bar";
	const char* thirdMessage = "ded";
	const char* expectedMessage = "foobarded";
	MockBluetoothDriver bluetooth;

	EXPECT_FALSE(bluetooth.hasMessageForClient());
	bluetooth.sendString(firstMessage);
	EXPECT_TRUE(bluetooth.hasMessageForClient());
	bluetooth.sendString(secondMessage);
	EXPECT_TRUE(bluetooth.hasMessageForClient());
	bluetooth.sendString(thirdMessage);
	EXPECT_TRUE(bluetooth.hasMessageForClient());
	const char* reportedMessage = bluetooth.getMessageForClient();
	EXPECT_FALSE(bluetooth.hasMessageForClient());
	EXPECT_STREQ(reportedMessage, expectedMessage);
	delete[] reportedMessage;
}
