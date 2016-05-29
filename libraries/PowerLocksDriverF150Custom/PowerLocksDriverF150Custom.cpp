#include "PowerLocksDriverF150Custom.h"
#include "Arduino.h"

PowerLocksDriverF150Custom::PowerLocksDriverF150Custom(int lockPin, int unlockPin)
    : lockPin(lockPin)
    , unlockPin(unlockPin)
{
}

PowerLocksDriverF150Custom::~PowerLocksDriverF150Custom()
{
}

void PowerLocksDriverF150Custom::lockDoors()
{
    digitalWrite(lockPin, HIGH);
    waitForLocksToSettle();
    digitalWrite(lockPin, LOW);
}

void PowerLocksDriverF150Custom::unlockDoors()
{
    digitalWrite(unlockPin, HIGH);
    waitForLocksToSettle();
    digitalWrite(unlockPin, LOW);
}

void PowerLocksDriverF150Custom::waitForLocksToSettle()
{
    // 0.7 seconds is OEM standard
    delay(700);
}
