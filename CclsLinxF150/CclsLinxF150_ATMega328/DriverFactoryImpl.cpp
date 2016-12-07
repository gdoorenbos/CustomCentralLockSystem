#include "DriverFactoryImpl.h"
#include "PinDefines.h"
#include <LinxKh3RxModule.h>
#include <PowerLocksDriverF150Custom.h>

DriverFactoryImpl::DriverFactoryImpl()
    : powerLocksDriver(new PowerLocksDriverF150Custom(POWER_LOCKS_LOCK_PIN, POWER_LOCKS_UNLOCK_PIN))
{
    LinxAddrBus addrBus;
    addrBus.a0 = LINX_A0;
    addrBus.a1 = LINX_A1;
    addrBus.a2 = LINX_A2;
    addrBus.a3 = LINX_A3;
    addrBus.a4 = LINX_A4;
    addrBus.a5 = LINX_A5;
    addrBus.a6 = LINX_A6;
    addrBus.a7 = LINX_A7;
    addrBus.a8 = LINX_A8;
    addrBus.a9 = LINX_A9;

    LinxDataBus dataBus;
    dataBus.d0 = LINX_D0;
    dataBus.d1 = LINX_D1;
    dataBus.d2 = LINX_D2;
    dataBus.d3 = LINX_D3;
    dataBus.d4 = LINX_D4;

    rxModule = new LinxKh3RxModule(addrBus, dataBus, LINX_VT);
}

DriverFactoryImpl::~DriverFactoryImpl()
{
    delete rxModule;
    delete powerLocksDriver;
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
