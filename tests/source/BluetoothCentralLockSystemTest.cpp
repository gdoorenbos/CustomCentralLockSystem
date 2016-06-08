#include "gtest/gtest.h"
#include "MockBluetoothDriver.h"
#include "MockPowerLocksDriver.h"
#include "MockPushButtonDriver.h"
#include "BluetoothCentralLockSystem.h"
#include "UserLogin.h"

// These may change. update as needed. 
const char* greetingMessage = "________            ________\n\\       \\___/\\/\\___/       /\n \\                        /\n  \\__________  __________/\n             \\/\n>";
const char* basePrompt = ">";
const char* userPrompt = "#";
const char* passwordPrompt = "Enter password: ";
const char* loginSuccessfulMessage = "Welcome Back, Master Wayne\n#";
const char* loginUnsuccessfulMessage = "Denied\n>";

// utility methods
void expectResponseForMessageFromClient( const char* messageFromClient
									   , const char* expectedResponse
									   , BluetoothCentralLockSystem &cls
									   , MockBluetoothDriver &bluetooth )
{
	bluetooth.sendMessageFromClient(messageFromClient);
	cls.run();
	const char* reportedStr = bluetooth.getMessageForClient();
	EXPECT_STREQ(expectedResponse, reportedStr);
	delete[] reportedStr;
}

TEST(BluetoothCentralLockSystemTest, lockAndUnlockButtonsWork)
{
	MockBluetoothDriver bluetooth;
	MockPowerLocksDriver locks;
	MockPushButtonDriver lockButton;
	MockPushButtonDriver unlockButton;
	BluetoothCentralLockSystem cls(&bluetooth, &locks, &lockButton, &unlockButton);
	EXPECT_FALSE(locks.areDoorsLocked());

	// lock doors
	lockButton.press();
	cls.run();
	EXPECT_TRUE(locks.areDoorsLocked());
	lockButton.release();

	// unlock doors
	unlockButton.press();
	cls.run();
	EXPECT_FALSE(locks.areDoorsLocked());
	unlockButton.release();

	// lockButton precedence over unlockButton
	lockButton.press();
	unlockButton.press();
	cls.run();
	EXPECT_TRUE(locks.areDoorsLocked());
	cls.run();
	EXPECT_TRUE(locks.areDoorsLocked());
	cls.run();
	EXPECT_TRUE(locks.areDoorsLocked());
	lockButton.release();
	unlockButton.release();
}

TEST(BluetoothCentralLockSystem, successfulClientAuthentication)
{
	MockBluetoothDriver bluetooth;
	MockPowerLocksDriver locks;
	MockPushButtonDriver lockButton;
	MockPushButtonDriver unlockButton;
	BluetoothCentralLockSystem cls(&bluetooth, &locks, &lockButton, &unlockButton);

	bluetooth.connectClient();
	cls.run();
	const char* reportedStr = bluetooth.getMessageForClient();
	EXPECT_STREQ(reportedStr, greetingMessage);
	delete[] reportedStr;

	// bluetooth.sendMessageFromClient(ALLOWED_USER);
	// cls.run();
	// reportedStr = bluetooth.getMessageForClient();
	// EXPECT_STREQ(reportedStr, passwordPrompt);
	// delete[] reportedStr;
	expectResponseForMessageFromClient(ALLOWED_USER, passwordPrompt, cls, bluetooth);

	// bluetooth.sendMessageFromClient(ALLOWED_USER_PASSWORD);
	// cls.run();
	// reportedStr = bluetooth.getMessageForClient();
	// EXPECT_STREQ(reportedStr, loginSuccessfulMessage);
	// delete[] reportedStr;
	expectResponseForMessageFromClient(ALLOWED_USER_PASSWORD, loginSuccessfulMessage, cls, bluetooth);

	// add some carriage returns for good measure
	for(int i=0; i<3; ++i)
	{
		// bluetooth.sendMessageFromClient("");
		// cls.run();
		// reportedStr = bluetooth.getMessageForClient();
		// EXPECT_STREQ(reportedStr, userPrompt);
		// delete[] reportedStr;
		expectResponseForMessageFromClient("", userPrompt, cls, bluetooth);
	}
}

TEST(BluetoothCentralLockSystem, unsuccessfulClientAuthentication)
{
	MockBluetoothDriver bluetooth;
	MockPowerLocksDriver locks;
	MockPushButtonDriver lockButton;
	MockPushButtonDriver unlockButton;
	BluetoothCentralLockSystem cls(&bluetooth, &locks, &lockButton, &unlockButton);

	bluetooth.connectClient();
	cls.run();
	cls.run();
	cls.run();
	const char* reportedStr = bluetooth.getMessageForClient();
	EXPECT_STREQ(reportedStr, greetingMessage);
	delete[] reportedStr;

	for(int i= 0; i<3; ++i)
	{
		// bluetooth.sendMessageFromClient("");
		// cls.run();
		// reportedStr = bluetooth.getMessageForClient();
		// EXPECT_STREQ(reportedStr, basePrompt);
		// delete[] reportedStr;
		expectResponseForMessageFromClient("", basePrompt, cls, bluetooth);
	}

	bluetooth.sendMessageFromClient("ls");
	cls.run();
	cls.run();
	cls.run();
	reportedStr = bluetooth.getMessageForClient();
	EXPECT_STREQ(reportedStr, basePrompt);
	delete[] reportedStr;

	bluetooth.sendMessageFromClient("pwd");
	cls.run();
	cls.run();
	cls.run();
	reportedStr = bluetooth.getMessageForClient();
	EXPECT_STREQ(reportedStr, basePrompt);
	delete[] reportedStr;

	// bluetooth.sendMessageFromClient(ALLOWED_USER);
	// cls.run();
	// reportedStr = bluetooth.getMessageForClient();
	// EXPECT_STREQ(reportedStr, passwordPrompt);
	expectResponseForMessageFromClient(ALLOWED_USER, passwordPrompt, cls, bluetooth);

	expectResponseForMessageFromClient("badpassword", loginUnsuccessfulMessage, cls, bluetooth);

	for(int i=0; i<3; ++i)
	{
		expectResponseForMessageFromClient("", basePrompt, cls, bluetooth);
	}
}
