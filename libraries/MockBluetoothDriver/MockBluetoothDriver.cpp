#include "MockBluetoothDriver.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

MockBluetoothDriver::MockBluetoothDriver()
    : deviceIsConnected(false)
    , messageFromDevice(0)
{
}

MockBluetoothDriver::~MockBluetoothDriver()
{
    deleteMessageFromDeviceIfPresent();
}

bool MockBluetoothDriver::isDeviceConnected() const
{
    return deviceIsConnected;
}

void MockBluetoothDriver::print(const char* message) const
{
    printf("%s", message);
}

void MockBluetoothDriver::printLine(const char* message) const
{
    printf("%s\n", message);
}

bool MockBluetoothDriver::hasMessage() const
{
    return (messageFromDevice != 0);
}

const char* MockBluetoothDriver::getMessage() const
{
    if( hasMessage() )
        return makeCopyOfMessageFromDeviceAndDelete();
    else
        return makeCopyOfStringOnHeap("");
}

void MockBluetoothDriver::connectDevice()
{
    deviceIsConnected = true;
}

void MockBluetoothDriver::disconnectDevice()
{
    deviceIsConnected = false;
}

void MockBluetoothDriver::sendMessageFromDevice(const char* message)
{
    if( message != 0 )
        updateMessageFromDevice(message);
}

void MockBluetoothDriver::deleteMessageFromDevice()
{
    delete [] messageFromDevice;
    messageFromDevice = 0;
}

void MockBluetoothDriver::deleteMessageFromDeviceIfPresent()
{
    if( hasMessage() ) // User didn't read it in time!
        deleteMessageFromDevice();
}

char* MockBluetoothDriver::makeCopyOfStringOnHeap(char* originalStr)
{
    char* newStr = new char[strlen(originalStr)+1];
    strncpy(newStr, originalStr, strlen(originalStr)+1);
    return newStr;
}

char* MockBluetoothDriver::makeCopyOfMessageFromDeviceAndDelete()
{
    char* returnStr = makeCopyOfStringOnHeap(messageFromDevice);
    deleteMessageFromDevice();
    return returnStr;
}

void MockBluetoothDriver::updateMessageFromDevice(char* message)
{
    deleteMessageFromDeviceIfPresent();
    messageFromDevice = makeCopyOfStringOnHeap(message);
}
