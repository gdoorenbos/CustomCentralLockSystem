#include "BluetoothCentralLockSystem.h"
#include <BluetoothDriver.h>
#include <PowerLocksDriver.h>
#include <PushButtonDriver.h>

BluetoothCentralLockSystem::BluetoothCentralLockSystem( BluetoothDriver* bluetoothDriver
                                                      , PowerLocksDriver* locksDriver
                                                      , PushButtonDriver* lockButton
                                                      , PushButtonDriver* unlockButton )
    : bluetooth(bluetoothDriver)
    , locks(locksDriver)
    , lockButton(lockButton)
    , unlockButton(unlockButton)
{
}

BluetoothCentralLockSystem::~BluetoothCentralLockSystem()
{
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
}
