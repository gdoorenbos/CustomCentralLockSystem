#include "BluetoothCentralLockSystem.h"
#include <BluetoothDriver.h>
#include <PowerLocksDriver.h>
#include <PushButtonDriver.h>
#include "UserLogin.h"
#include <cstring>

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
    //bluetooth->sendString("________            ________\n");
    //bluetooth->sendString("\       \___/\/\___/       /\n");
    //bluetooth->sendString(" \                        / \n");
    //bluetooth->sendString("  \__________  __________/  \n");
    //bluetooth->sendString("             \/             \n");
    
    bluetooth->sendString("________            ________\n");
    bluetooth->sendString("\\       \\___/\\/\\___/       /\n");
    bluetooth->sendString(" \\                        / \n");
    bluetooth->sendString("  \\__________  __________/  \n");
    bluetooth->sendString("             \\/             \n");
    sentGreetingMessage = true;
}

void BluetoothCentralLockSystem::sendPrompt()
{
    if( userLoggedIn )
        bluetooth->sendString("#");
    else
        bluetooth->sendString(">");
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
                bluetooth->sendString("Enter password: ");
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
                bluetooth->sendString("Welcome Back, Master Wayne\n");
                sendPrompt();
            }
            else
            {
                bluetooth->sendString("Denied\n");
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
        if( strcmp(command, "lock") == 0 )
        {
            locks->lockDoors();
        }
        else if( strcmp(command, "unlock") == 0 )
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

    if( !bluetooth->isClientConnected() && userLoggedIn )
    {
        resetBluetoothConnectionParameters();
    }
}
