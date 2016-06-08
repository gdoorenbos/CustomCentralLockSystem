#include "BluetoothCentralLockSystem.h"
#include <BluetoothDriver.h>
#include <PowerLocksDriver.h>
#include <PushButtonDriver.h>
#include "UserLogin.h"
#include <cstring>

/* Greeting message:
________            ________
\       \___/\/\___/       /
 \                        /
  \__________  __________/
             \/
*/

BluetoothCentralLockSystem::BluetoothCentralLockSystem( BluetoothDriver* bluetoothDriver
                                                      , PowerLocksDriver* locksDriver
                                                      , PushButtonDriver* lockButton
                                                      , PushButtonDriver* unlockButton )
    : bluetooth(bluetoothDriver)
    , locks(locksDriver)
    , lockButton(lockButton)
    , unlockButton(unlockButton)
    , sentGreetingMessage(false)
    , requestingUsername(false)
    , requestingPassword(false)
    , userLoggedIn(false)
    , greetingMessage("________            ________\n\\       \\___/\\/\\___/       /\n \\                        /\n  \\__________  __________/\n             \\/\n")
    , basePrompt(">")
    , userPrompt("#")
    , passwordPrompt("Enter password: ")
    , loginSuccessfulMessage("Welcome Back, Master Wayne\n")
    , loginUnsuccessfulMessage("Denied\n")
    , lockDoorsCommand("lockdoors")
    , unlockDoorsCommand("unlockdoors")
    , lockDoorsResponse("success!\n")
    , unlockDoorsResponse("success!\n")
{
}

BluetoothCentralLockSystem::~BluetoothCentralLockSystem()
{
}

void BluetoothCentralLockSystem::sendGreetingMessage()
{
    bluetooth->sendString(greetingMessage);
    sentGreetingMessage = true;
}

void BluetoothCentralLockSystem::sendPrompt()
{
    bluetooth->sendString(userLoggedIn ? userPrompt : basePrompt);
}

void BluetoothCentralLockSystem::handleBluetoothMessage()
{
    if( !userLoggedIn )
    {
        if( requestingUsername )
        {
            const char* currentUser = bluetooth->getMessage();
            if( strcmp(currentUser, ALLOWED_USER) == 0 )
            {
                requestingUsername = false;
                requestingPassword = true;
                bluetooth->sendString(passwordPrompt);
            }
            else
            {
                sendPrompt();
            }
        }
        else if( requestingPassword )
        {
            const char* enteredPassword = bluetooth->getMessage();
            if( strcmp(enteredPassword, ALLOWED_USER_PASSWORD) == 0 )
            {
                userLoggedIn = true;
                requestingPassword = false;
                bluetooth->sendString(loginSuccessfulMessage);
                sendPrompt();
            }
            else
            {
                bluetooth->sendString(loginUnsuccessfulMessage);
                sendPrompt();
                requestingUsername = true;
                requestingPassword = false;
            }
        }
    }
    else
    {
        // awaiting commands to either lock or unlock the doors
        const char* command = bluetooth->getMessage();
        if( strcmp(command, lockDoorsCommand) == 0 )
        {
            locks->lockDoors();
            bluetooth->sendString(lockDoorsResponse);
        }
        else if( strcmp(command, unlockDoorsCommand) == 0 )
        {
            locks->unlockDoors();
            bluetooth->sendString(unlockDoorsResponse);
        }
        sendPrompt();
    }
}

void BluetoothCentralLockSystem::resetBluetoothConnectionParameters()
{
    sentGreetingMessage = false;
    requestingUsername = false;
    requestingPassword = false;
    userLoggedIn = false;
}

void BluetoothCentralLockSystem::run()
{
    if( lockButton->isPressed() )
    {
        locks->lockDoors();
    }
    else if( unlockButton->isPressed() )
    {
        locks->unlockDoors();
    }
    else if( bluetooth->isClientConnected() )
    {
        if( !userLoggedIn )
        {
            if( !sentGreetingMessage )
            {
                sendGreetingMessage();
                sendPrompt();
                requestingUsername = true;
            }
            else if( bluetooth->hasMessage() )
            {
                handleBluetoothMessage();
            }
        }
        else if( userLoggedIn )
        {
            if( bluetooth->hasMessage() )
            {
                handleBluetoothMessage();
            }
        }
    }

    if( !bluetooth->isClientConnected() )
    {
        resetBluetoothConnectionParameters();
    }
}
