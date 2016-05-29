// Bluetooth Central Lock System

#ifndef BLUETOOTH_CENTRAL_LOCK_SYSTEM_H
#define BLUETOOTH_CENTRAL_LOCK_SYSTEM_H

// forward declarations
class BluetoothDriver;
class PowerLocksDriver;

class BluetoothCentralLockSystem
{
public:
    BluetoothCentralLockSystem(BluetoothDriver* bluetoothDriver);
    ~BluetoothCentralLockSystem();

private:
    // intentionally unimplemented
    BluetoothCentralLockSystem();

    // methods

    // members
    BluetoothDriver* bluetooth;
    PowerLocksDriver* locks;
};

#endif
