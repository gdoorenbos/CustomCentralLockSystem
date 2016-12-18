#include "LinxKh3RxModule.h"
#include "ArduinoGpioHandler.h"
#include "Arduino.h"

LinxKh3RxModule::LinxKh3RxModule(LinxAddrBus addrBus, LinxDataBus dataBus, int vtPin)
    : LinxRxModule(new ArduinoGpioHandler(), addrBus, dataBus, vtPin)
{
}

LinxKh3RxModule::~LinxKh3RxModule()
{
}
