#include "ArduinoLinxRxModule.h"
#include "ArduinoGpioDriver.h"

ArduinoLinxRxModule::ArduinoLinxRxModule(int lockReqPin, int unlockReqPin)
    : ArduinoLinxRxModule(ArduinoGpioDriver(lockReqPin), ArduinoGpioDriver(unlockReqPin))
{
}

ArduinoLinxRxModule::~ArduinoLinxRxModule()
{
}
