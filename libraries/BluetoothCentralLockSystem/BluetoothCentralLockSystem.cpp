#include "BluetoothCentralLockSystem.h"
#include <BluetoothDriver.h>
#include <PowerLocksDriver.h>
#include <PushButtonDriver.h>
#include "UserLogin.h"
#include <string.h>

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
    , clientState(stateSendGreetingMessage)
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

void BluetoothCentralLockSystem::run()
{
    if( lockButton->isPressed() )
        locks->lockDoors();
    else if( unlockButton->isPressed() )
        locks->unlockDoors();
    else if( bluetooth->isClientConnected() )
        handleBluetoothClient();

    if( needToResetClientState() )
        clientState = stateSendGreetingMessage;
}

void BluetoothCentralLockSystem::handleBluetoothClient()
{
    if( clientState == stateSendGreetingMessage )
        sendGreetingMessage();
    else if( clientState == stateRequestUsername && bluetooth->hasMessage() )
        checkEnteredUsername();
    else if( clientState == stateRequestPassword && bluetooth->hasMessage() )
        checkEnteredPassword();
    else if( clientState == stateUserLoggedIn && bluetooth->hasMessage() )
        handleUserCommands();
}

void BluetoothCentralLockSystem::checkEnteredUsername()
{
    if( bluetoothMessageEquals(ALLOWED_USER) )
        sendPasswordPrompt();
    else
        sendPrompt();
}

void BluetoothCentralLockSystem::sendPasswordPrompt()
{
    clientState = stateRequestPassword;
    bluetooth->sendString(passwordPrompt);
}

void BluetoothCentralLockSystem::checkEnteredPassword()
{
    if( bluetoothMessageEquals(ALLOWED_USER_PASSWORD) )
        sendLoginSuccessfulMessage();
    else
        sendLoginUnsuccessfulMessage();
}

void BluetoothCentralLockSystem::sendLoginSuccessfulMessage()
{
    clientState = stateUserLoggedIn;
    bluetooth->sendString(loginSuccessfulMessage);
    sendPrompt();
}

void BluetoothCentralLockSystem::sendLoginUnsuccessfulMessage()
{
    clientState = stateRequestUsername;
    bluetooth->sendString(loginUnsuccessfulMessage);
    sendPrompt();
}

void BluetoothCentralLockSystem::handleUserCommands()
{
    const char* command = bluetooth->getMessage();
    if( strcmp(command, lockDoorsCommand) == 0 )
        lockDoorsAndNotifyClient();
    else if( strcmp(command, unlockDoorsCommand) == 0 )
        unlockDoorsAndNotifyClient();

    sendPrompt();
    delete[] command;
}

void BluetoothCentralLockSystem::lockDoorsAndNotifyClient()
{
    locks->lockDoors();
    bluetooth->sendString(lockDoorsResponse);
}

void BluetoothCentralLockSystem::unlockDoorsAndNotifyClient()
{
    locks->unlockDoors();
    bluetooth->sendString(unlockDoorsResponse);
}

void BluetoothCentralLockSystem::sendGreetingMessage()
{
    clientState = stateRequestUsername;
    bluetooth->sendString(greetingMessage);
    sendPrompt();
}

void BluetoothCentralLockSystem::sendPrompt()
{
    if( clientState == stateUserLoggedIn )
        bluetooth->sendString( userPrompt );
    else
        bluetooth->sendString( basePrompt );
}

bool BluetoothCentralLockSystem::bluetoothMessageEquals(const char* str)
{
    const char* message = bluetooth->getMessage();
    int result = strcmp(message, str);
    delete[] message;

    return (result == 0);
}

bool BluetoothCentralLockSystem::needToResetClientState()
{
    return ( !bluetooth->isClientConnected() || 
             clientState > stateUserLoggedIn || 
             clientState < stateSendGreetingMessage );
}
