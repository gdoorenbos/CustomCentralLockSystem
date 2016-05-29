#ifndef CENTRAL_LOCK_SYSTEM_F150_CUSTOM_H
#define CENTRAL_LOCK_SYSTEM_F150_CUSTOM_H

// forward declarations
class BluetoothDriver;
class PowerLocksDriver;

class CentralLockSystemF150Custom
{
public:
    CentralLockSystemF150Custom(BluetoothDriver* bluetoothDriver);
    ~CentralLockSystemF150Custom();

private:
    // intentionally unimplemented
    CentralLockSystemF150Custom();

    // methods

    // members
    BluetoothDriver* bluetooth;
    PowerLocksDriver* locks;
};

#endif
