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
    void handleBluetoothClient();
    void checkEnteredUsername();
    void checkEnteredPassword();
    void handleUserCommands();
    void sendPrompt();
    void sendGreetingMessage();
    void sendPasswordPrompt();
    void sendLoginSuccessfulMessage();
    void sendLoginUnsuccessfulMessage();
    void lockDoorsAndNotifyClient();
    void unlockDoorsAndNotifyClient();

    /** 
     * Returns true if the c string returned by bluetooth->getMessage() equals the 
     * string given by str in value
     */
    bool bluetoothMessageEquals(const char* str);

    // members
    BluetoothDriver* bluetooth;
    PowerLocksDriver* locks;
    const PushButtonDriver* lockButton;
    const PushButtonDriver* unlockButton;

    enum BluetoothClientState
    {
        stateSendGreetingMessage,
        stateRequestUsername,
        stateRequestPassword,
        stateUserLoggedIn
    } clientState;
    bool needToResetClientState();
};

#endif
