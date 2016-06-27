#include "gtest/gtest.h"
#include "MockBluetoothDriver.h"
#include "MockPowerLocksDriver.h"
#include "MockPushButtonDriver.h"
#include "BluetoothCentralLockSystem.h"
#include "UserLogin.h"

/*
General process for cls:
1. connect client to bluetooth
2. cls sends greeting and prompt
3. client enters username
4. cls sends password prompt
5. client enters password
6. cls sends confirmation
7. client enters command to either lock or unlock doors
8. cls locks/unlocks doors and sends user confirmation
*/

// These may change. update as needed. 
// const char* greetingMessage = ".     ________            ________\r\n.     \\       \\___/\\/\\___/       /\r\n.      \\                        /\r\n.       \\__________  __________/\r\n.                  \\/\r\n~\r\n";
const char* greetingMessage = "Hello\r\n~\r\n";
const char* basePrompt = "~\r\n";
const char* userPrompt = "#\r\n";
const char* passwordPrompt = "password: \r\n";
const char* loginSuccessfulMessage = "Welcome Back, Master Wayne\r\n#\r\n";
const char* loginUnsuccessfulMessage = "Denied\r\n~\r\n";
const char* lockDoorsCommand = "lockdoors";
const char* unlockDoorsCommand = "unlockdoors";
const char* lockDoorsReponse = "success!\r\n#\r\n";
const char* unlockDoorsResponse = "success!\r\n#\r\n";

// utility methods
void expectMessageForClient( const char* expectedMessage, MockBluetoothDriver &bluetooth )
{
	const char* reportedStr = bluetooth.getMessageForClient();
	EXPECT_STREQ(expectedMessage, reportedStr);
	delete[] reportedStr;
}

void expectResponseForMessageFromClient( const char* messageFromClient
									   , const char* expectedResponse
									   , BluetoothCentralLockSystem &cls
									   , MockBluetoothDriver &bluetooth )
{
	bluetooth.sendMessageFromClient(messageFromClient);
	cls.run();
	cls.run();
	cls.run();
	expectMessageForClient(expectedResponse, bluetooth);
}

void sendThreeCarriageReturns( const char* expectedPrompt, BluetoothCentralLockSystem &cls, MockBluetoothDriver &bluetooth )
{
	for(int i=0; i<3; ++i)
		expectResponseForMessageFromClient("", expectedPrompt, cls, bluetooth);
}

void connectClientAndLogIn( BluetoothCentralLockSystem &cls, MockBluetoothDriver &bluetooth )
{
	bluetooth.connectClient();
	cls.run();
	expectMessageForClient(greetingMessage, bluetooth);
	expectResponseForMessageFromClient(ALLOWED_USER, passwordPrompt, cls, bluetooth);
	expectResponseForMessageFromClient(ALLOWED_USER_PASSWORD, loginSuccessfulMessage, cls, bluetooth);
	sendThreeCarriageReturns(userPrompt, cls, bluetooth);
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
	EXPECT_STREQ(greetingMessage, reportedStr);
	delete[] reportedStr;

	expectResponseForMessageFromClient(ALLOWED_USER, passwordPrompt, cls, bluetooth);
	expectResponseForMessageFromClient(ALLOWED_USER_PASSWORD, loginSuccessfulMessage, cls, bluetooth);
	sendThreeCarriageReturns(userPrompt, cls, bluetooth);
}

TEST(BluetoothCentralLockSystem, unsuccessfulClientAuthentication)
{
	MockBluetoothDriver bluetooth;
	MockPowerLocksDriver locks;
	MockPushButtonDriver lockButton;
	MockPushButtonDriver unlockButton;
	BluetoothCentralLockSystem cls(&bluetooth, &locks, &lockButton, &unlockButton);

	// unsuccessful attempt to connect and login
	bluetooth.connectClient();
	cls.run();
	cls.run();
	cls.run();
	expectMessageForClient(greetingMessage, bluetooth);
	sendThreeCarriageReturns(basePrompt, cls, bluetooth);
	expectResponseForMessageFromClient("ls", basePrompt, cls, bluetooth);
	expectResponseForMessageFromClient("pwd", basePrompt, cls, bluetooth);
	expectResponseForMessageFromClient(ALLOWED_USER, passwordPrompt, cls, bluetooth);
	expectResponseForMessageFromClient("badpassword", loginUnsuccessfulMessage, cls, bluetooth);
	sendThreeCarriageReturns(basePrompt, cls, bluetooth);
	bluetooth.disconnectClient();

	// make sure a valid user can log in afterwards
	cls.run();
	connectClientAndLogIn(cls, bluetooth);
}

TEST(BluetoothCentralLockSystem, gracefulUserLogout)
{
	MockBluetoothDriver bluetooth;
	MockPowerLocksDriver locks;
	MockPushButtonDriver lockButton;
	MockPushButtonDriver unlockButton;
	BluetoothCentralLockSystem cls(&bluetooth, &locks, &lockButton, &unlockButton);

	// first, log in
	connectClientAndLogIn(cls, bluetooth);

	// disconnect a client and wait some time
	bluetooth.disconnectClient();
	for(int i=0; i<10; ++i)
		cls.run();

	// logout is considered graceful if we can successfully login again
	connectClientAndLogIn(cls, bluetooth);
}

TEST(BluetoothCentralLockSystem, bluetoothUserCanLockAndUnlockDoors)
{
	MockBluetoothDriver bluetooth;
	MockPowerLocksDriver locks;
	MockPushButtonDriver lockButton;
	MockPushButtonDriver unlockButton;
	BluetoothCentralLockSystem cls(&bluetooth, &locks, &lockButton, &unlockButton);

	connectClientAndLogIn(cls, bluetooth);
	expectResponseForMessageFromClient(lockDoorsCommand, lockDoorsReponse, cls, bluetooth);
	EXPECT_TRUE(locks.areDoorsLocked());
	expectResponseForMessageFromClient(unlockDoorsCommand, unlockDoorsResponse, cls, bluetooth);
	EXPECT_FALSE(locks.areDoorsLocked());
	expectResponseForMessageFromClient(lockDoorsCommand, lockDoorsReponse, cls, bluetooth);
	EXPECT_TRUE(locks.areDoorsLocked());
	expectResponseForMessageFromClient(unlockDoorsCommand, unlockDoorsResponse, cls, bluetooth);
	EXPECT_FALSE(locks.areDoorsLocked());
}
