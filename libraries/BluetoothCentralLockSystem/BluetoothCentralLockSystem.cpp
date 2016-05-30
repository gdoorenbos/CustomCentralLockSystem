#include "BluetoothCentralLockSystem.h"
#include <BluetoothDriver.h>
#include <PowerLocksDriver.h>

BluetoothCentralLockSystem::BluetoothCentralLockSystem(BluetoothDriver* bluetoothDriver, PowerLocksDriver* locksDriver)
    : bluetooth(bluetoothDriver)
    , locks(locksDriver)
{
}

BluetoothCentralLockSystem::~BluetoothCentralLockSystem()
{
}
