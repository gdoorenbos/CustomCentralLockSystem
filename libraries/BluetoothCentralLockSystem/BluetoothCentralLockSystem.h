// Bluetooth Central Lock System

#ifndef BLUETOOTH_CENTRAL_LOCK_SYSTEM_H
#define BLUETOOTH_CENTRAL_LOCK_SYSTEM_H

// forward declarations
class BluetoothDriver;
class PowerLocksDriver;
class PushButtonDriver;

class BluetoothCentralLockSystem
{
public:
    BluetoothCentralLockSystem( BluetoothDriver* bluetoothDriver
                              , PowerLocksDriver* locksDriver
                              , PushButtonDriver* lockButton
                              , PushButtonDriver* unlockButton );
    ~BluetoothCentralLockSystem();

    // periodically polled method - does the real work of the system
    void run();

private:
    // intentionally unimplemented
    BluetoothCentralLockSystem();

    // methods
    void sendGreetingMessage();
    void sendPrompt();
    void handleBluetoothMessage();
    void resetBluetoothConnectionParameters();

    // members
    BluetoothDriver* bluetooth;
    PowerLocksDriver* locks;
    const PushButtonDriver* lockButton;
    const PushButtonDriver* unlockButton;
    bool sentGreetingMessage;
    bool requestingUsername;
    bool requestingPassword;
    bool userLoggedIn;

    // string constants
    const char* greetingMessage;
    const char* basePrompt;
    const char* userPrompt;
    const char* passwordPrompt;
    const char* loginSuccessfulMessage;
    const char* loginUnsuccessfulMessage;
    const char* lockDoorsCommand;
    const char* lockDoorsResponse;
    const char* unlockDoorsCommand;
    const char* unlockDoorsResponse;
};

#endif
