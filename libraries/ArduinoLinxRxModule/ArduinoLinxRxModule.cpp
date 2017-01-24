#include "ArduinoLinxRxModule.h"
#include "ArduinoInternalPullupPin.h"

ArduinoLinxRxModule::ArduinoLinxRxModule(int lockReqPin, int unlockReqPin)
    : LinxRxModule(new ArduinoInternalPullupPin(lockReqPin), new ArduinoInternalPullupPin(unlockReqPin))
{
}

ArduinoLinxRxModule::~ArduinoLinxRxModule()
{
}
