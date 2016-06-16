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

// utility class for dealing with strings from the bluetoothDriver
class SmartCharPtr
{
public:
    SmartCharPtr(const char* ptr) : _ptr(ptr) {}
    ~SmartCharPtr() {delete[] _ptr;}
    const char* pointer() {return _ptr;}

private:
    SmartCharPtr(); // intentionally not implemented
    const char* _ptr;
};

BluetoothCentralLockSystem::BluetoothCentralLockSystem( BluetoothDriver* bluetoothDriver
                                                      , PowerLocksDriver* locksDriver
                                                      , PushButtonDriver* lockButton
                                                      , PushButtonDriver* unlockButton )
    : bluetooth(bluetoothDriver)
    , locks(locksDriver)
    , lockButton(lockButton)
    , unlockButton(unlockButton)
    , clientState(stateSendGreetingMessage)
{
}

BluetoothCentralLockSystem::~BluetoothCentralLockSystem()
{
}

void BluetoothCentralLockSystem::run()
{
    bluetooth->run();
    
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

void BluetoothCentralLockSystem::sendGreetingMessage()
{
    clientState = stateRequestUsername;
    bluetooth->sendString("Hello\r\n");
    sendPrompt();
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
    bluetooth->sendString("password: \r\n");
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
    bluetooth->sendString("Welcome Back, Master Wayne\r\n");
    sendPrompt();
}

void BluetoothCentralLockSystem::sendLoginUnsuccessfulMessage()
{
    clientState = stateRequestUsername;
    bluetooth->sendString("Denied\r\n");
    sendPrompt();
}

void BluetoothCentralLockSystem::handleUserCommands()
{
    SmartCharPtr command = bluetooth->getMessage();
    if( strcmp(command.pointer(), "lockdoors") == 0 )
        lockDoorsAndNotifyClient();
    else if( strcmp(command.pointer(), "unlockdoors") == 0 )
        unlockDoorsAndNotifyClient();

    sendPrompt();
}

void BluetoothCentralLockSystem::lockDoorsAndNotifyClient()
{
    locks->lockDoors();
    bluetooth->sendString("success!\r\n");
}

void BluetoothCentralLockSystem::unlockDoorsAndNotifyClient()
{
    locks->unlockDoors();
    bluetooth->sendString("success!\r\n");
}

void BluetoothCentralLockSystem::sendPrompt()
{
    if( clientState == stateUserLoggedIn )
        bluetooth->sendString( "#\r\n" );
    else
        bluetooth->sendString( "~\r\n" );
}

bool BluetoothCentralLockSystem::bluetoothMessageEquals(const char* str)
{
    SmartCharPtr message = bluetooth->getMessage();
    return (strcmp(message.pointer(), str) == 0);
}

bool BluetoothCentralLockSystem::needToResetClientState()
{
    return ( !bluetooth->isClientConnected() || 
             clientState > stateUserLoggedIn || 
             clientState < stateSendGreetingMessage );
}
