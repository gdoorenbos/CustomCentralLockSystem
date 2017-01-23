#include "ArduinoPowerLocksDriver.h"

ArduinoPowerLocksDriver::ArduinoPowerLocksDriver(int lockPin, int unlockPin)
    : PowerLocksDriver(new ArdinoGpioDriver(lockPin), new ArduinoGpioDriver(unlockPin))
{
}

ArduinoPowerLocksDriver::~ArduinoPowerLocksDriver()
{
}

ArduinoPowerLocksDriver::waitForLocksToSettle()
{
    delay(700);
}
