#include "ArduinoPowerLocksDriver.h"
#include "ArduinoGpioDriver.h"
#include "Arduino.h"

ArduinoPowerLocksDriver::ArduinoPowerLocksDriver(int lockPin, int unlockPin)
    : PowerLocksDriver(new ArduinoGpioDriver(lockPin), new ArduinoGpioDriver(unlockPin))
{
}

ArduinoPowerLocksDriver::~ArduinoPowerLocksDriver()
{
}

void ArduinoPowerLocksDriver::waitForLocksToSettle()
{
    delay(700);
}
