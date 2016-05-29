#include "BluetoothCentralLockSystem.h"
#include <BluetoothDriver.h>
#include <PowerLocksDriver.h>

BluetoothCentralLockSystem::BluetoothCentralLockSystem(BluetoothDriver* bluetoothDriver)
    : bluetooth(bluetoothDriver)
{
}

BluetoothCentralLockSystem::~BluetoothCentralLockSystem()
{
}
