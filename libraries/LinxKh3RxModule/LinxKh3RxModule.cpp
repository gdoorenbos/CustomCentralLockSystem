#include "LinxKh3RxModule.h"
#include "ArduinoPinHandler.h"
#include "Arduino.h"

LinxKh3RxModule::LinxKh3RxModule(int _addrBus[LINX_ADDR_BUS_SIZE], int _dataBus[LINX_DATA_BUS_SIZE], int _vtPin)
    : LinxRxModule(new ArduinoPinHandler(), _addrBus, _dataBus, _vtPin)
{
}

LinxKh3RxModule::~LinxKh3RxModule()
{
}
