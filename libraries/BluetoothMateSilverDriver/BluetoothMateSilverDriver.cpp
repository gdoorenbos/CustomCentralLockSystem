#include "BluetoothMateSilverDriver.h"

BluetoothMateSilverDriver::BluetoothMateSilverDriver()
{
}

BluetoothMateSilverDriver::~BluetoothMateSilverDriver()
{
}

bool BluetoothMateSilverDriver::isClientConnected() const
{
    return false;
}

void BluetoothMateSilverDriver::sendString(const char* message)
{
}

bool BluetoothMateSilverDriver::hasMessage() const
{
    return false;
}

const char* BluetoothMateSilverDriver::getMessage()
{
    return "";
}
