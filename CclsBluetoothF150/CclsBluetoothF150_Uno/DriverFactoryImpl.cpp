#include "DriverFactoryImpl.h"
#include "PinDefines.h"
#include <BluetoothMateSilverDriver.h>
#include <ArduinoPowerLocksDriver.h>
#include <ArduinoPushButtonDriver.h>

DriverFactoryImpl::DriverFactoryImpl()
    : bluetoothDriver(new BluetoothMateSilverDriver(BLUETOOTH_SERIAL_RX_PIN, BLUETOOTH_SERIAL_TX_PIN))
    , powerLocksDriver(new ArduinoPowerLocksDriver(POWER_LOCKS_LOCK_PIN, POWER_LOCKS_UNLOCK_PIN))
    , lockButton(new ArduinoPushButtonDriver(PUSH_BUTTON_LOCK_PIN))
    , unlockButton(new ArduinoPushButtonDriver(PUSH_BUTTON_UNLOCK_PIN))
{
}

DriverFactoryImpl::~DriverFactoryImpl()
{
    delete bluetoothDriver;
    delete powerLocksDriver;
    delete lockButton;
    delete unlockButton;
}

DriverFactory* DriverFactoryImpl::getInstance()
{
    static DriverFactory* singleton = 0;

    if( singleton == 0 )
        singleton = new DriverFactoryImpl();

    return singleton;
}

BluetoothDriver* DriverFactoryImpl::getBluetoothDriver()
{
    return bluetoothDriver;
}

PowerLocksDriver* DriverFactoryImpl::getPowerLocksDriver()
{
    return powerLocksDriver;
}

PushButtonDriver* DriverFactoryImpl::getLockButton()
{
    return lockButton;
}

PushButtonDriver* DriverFactoryImpl::getUnlockButton()
{
    return unlockButton;
}

