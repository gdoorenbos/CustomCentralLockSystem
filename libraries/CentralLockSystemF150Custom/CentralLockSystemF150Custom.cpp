#include "CentralLockSystemF150Custom.h"
#include <BluetoothDriver.h>
#include <PowerLocksDriver.h>

CentralLockSystemF150Custom::CentralLockSystemF150Custom(BluetoothDriver* bluetoothDriver)
    : bluetooth(bluetoothDriver)
{
}

CentralLockSystemF150Custom::~CentralLockSystemF150Custom()
{
}
