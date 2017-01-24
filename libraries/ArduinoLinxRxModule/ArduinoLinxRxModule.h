#ifndef ARDUINO_LINX_RX_MODULE_H
#define ARDUINO_LINX_RX_MODULE_H

#include "LinxRxModule.h"

class ArduinoLinxRxModule : public LinxRxModule
{
public:
    ArduinoLinxRxModule(int lockReqPin, int unlockReqPin);
    ~ArduinoLinxRxModule();
};

#endif
