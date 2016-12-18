#include "LinxKh3RxModule.h"
#include "ArduinoPinHandler.h"
#include "Arduino.h"

LinxKh3RxModule::LinxKh3RxModule(LinxAddrBus addrBus, LinxDataBus dataBus, int vtPin)
    : LinxRxModule(new ArduinoPinHandler(), addrBus, dataBus, vtPin)
{
}

LinxKh3RxModule::~LinxKh3RxModule()
{
}
