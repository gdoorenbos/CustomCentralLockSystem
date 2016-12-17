#include "DriverFactoryImpl.h"
#include "PinDefines.h"
#include "LinxKh3RxModule.h"
#include "PowerLocksDriverF150Custom.h"

DriverFactoryImpl::DriverFactoryImpl()
    : powerLocksDriver(new PowerLocksDriverF150Custom(POWER_LOCKS_LOCK_PIN, POWER_LOCKS_UNLOCK_PIN))
{
    int addrBus[LINX_ADDR_BUS_SIZE];
    addrBus[0] = LINX_A0;
    addrBus[1] = LINX_A1;
    addrBus[2] = LINX_A2;
    addrBus[3] = LINX_A3;
    addrBus[4] = LINX_A4;
    addrBus[5] = LINX_A5;
    addrBus[6] = LINX_A6;
    addrBus[7] = LINX_A7;
    addrBus[8] = LINX_A8;
    addrBus[9] = LINX_A9;

    int dataBus[LINX_DATA_BUS_SIZE];
    dataBus[0] = LINX_D0;
    dataBus[1] = LINX_D1;
    dataBus[2] = LINX_D2;
    dataBus[3] = LINX_D3;
    dataBus[4] = LINX_D4;

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
