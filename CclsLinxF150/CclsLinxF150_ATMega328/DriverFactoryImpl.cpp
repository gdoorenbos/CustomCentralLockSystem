#include "DriverFactoryImpl.h"
#include "PinDefines.h"
#include <LinxKh3RxModule.h>
#include <PowerLocksDriverF150Custom.h>
#include <PushButtonInternalPullupDriver.h>

DriverFactoryImpl::DriverFactoryImpl()
    : powerLocksDriver(new PowerLocksDriverF150Custom(POWER_LOCKS_LOCK_PIN, POWER_LOCKS_UNLOCK_PIN))
    , lockButton(new PushButtonInternalPullupDriver(PUSH_BUTTON_LOCK_PIN))
    , unlockButton(new PushButtonInternalPullupDriver(PUSH_BUTTON_UNLOCK_PIN))
{
    LinxAddrBus addrBus;
    addrBus.a[0] = LINX_A0;
    addrBus.a[1] = LINX_A1;
    addrBus.a[2] = LINX_A2;
    addrBus.a[3] = LINX_A3;
    addrBus.a[4] = LINX_A4;
    addrBus.a[5] = LINX_A5;
    addrBus.a[6] = LINX_A6;
    addrBus.a[7] = LINX_A7;
    addrBus.a[8] = LINX_A8;
    addrBus.a[9] = LINX_A9;

    LinxDataBus dataBus;
    dataBus.d[0] = LINX_D0;
    dataBus.d[1] = LINX_D1;
    dataBus.d[2] = LINX_D2;
    dataBus.d[3] = LINX_D3;
    dataBus.d[4] = LINX_D4;

    rxModule = new LinxKh3RxModule(addrBus, dataBus, LINX_VT);
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

