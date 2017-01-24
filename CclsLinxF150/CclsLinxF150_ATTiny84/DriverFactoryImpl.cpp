#include "PinDefines.h"
#include "DriverFactoryImpl.h"
#include "ArduinoLinxRxModule.h"
#include "ArduinoPowerLocksDriver.h"
#include "ArduinoPushButtonDriver.h"

DriverFactoryImpl::DriverFactoryImpl()
    : rxModule(new ArduinoLinxRxModule(LOCK_REQ_RF_PIN, UNLOCK_REQ_RF_PIN))
    , powerLocksDriver(new ArduinoPowerLocksDriver(LOCK_CMD_PIN, UNLOCK_CMD_PIN))
    , lockButton(new ArduinoPushButtonDriver(LOCK_REQ_BTN_PIN))
    , unlockButton(new ArduinoPushButtonDriver(UNLOCK_REQ_BTN_PIN))
{
}

DriverFactoryImpl::~DriverFactoryImpl()
{
    delete rxModule;
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

LinxRxModule* DriverFactoryImpl::getLinxRxModule()
{
    return rxModule;
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

