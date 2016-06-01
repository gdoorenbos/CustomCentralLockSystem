#include "BluetoothCentralLockSystem.h"
#include <BluetoothDriver.h>
#include <PowerLocksDriver.h>
#include <PushButtonDriver.h>
#include "UserLogin.h"

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
{
}

BluetoothCentralLockSystem::~BluetoothCentralLockSystem()
{
}

void BluetoothCentralLockSystem::sendGreetingMessage()
{
    bluetooth->printLine("________            ________");
    bluetooth->printLine("\       \___/\/\___/       /");
    bluetooth->printLine(" \                        / ");
    bluetooth->printLine("  \__________  __________/  ");
    bluetooth->printLine("             \/             ");
    sentGreetingMessage = true;
}

void BluetoothCentralLockSystem::sendPrompt()
{
    if( userLoggedIn )
        bluetooth->print("#");
    else
        bluetooth->print(">");
}

void BluetoothCentralLockSystem::handleBluetoothMessage()
{
    if( !userLoggedIn )
    {
        if( requestingUsername )
        {
            const char* currentUser = bluetooth->getMessage();
            if( currentUser == ALLOWED_USER )
            {
                requestingUsername = false;
                requestingPassword = true;
                bluetooth->print("Enter password: ");
            }
            else
            {
                sendPrompt();
            }
        }
        else if( requestingPassword )
        {
            const char* enteredPassword = bluetooth->getMessage();
            if( enteredPassword == ALLOWED_USER_PASSWORD )
            {
                userLoggedIn = true;
                requestingPassword = false;
                bluetooth->printLine("Welcome Back, Master Wayne");
                sendPrompt();
            }
            else
            {
                bluetooth->printLine("Denied");
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
        if( command == "lock" )
        {
            locks->lockDoors();
        }
        else if( command == "unlock" )
        {
            locks->unlockDoors();
        }
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
    else if( bluetooth->isDeviceConnected() )
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

    if( !bluetooth->isDeviceConnected() && userLoggedIn )
    {
        resetBluetoothConnectionParameters();
    }
}
