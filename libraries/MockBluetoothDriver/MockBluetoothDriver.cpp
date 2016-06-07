#include "MockBluetoothDriver.h"
#include <cstring>
#include <cstdio>
#include <cstdlib>

MockBluetoothDriver::MockBluetoothDriver()
    : deviceIsConnected(false)
    , messageFromDevice(0)
    , messageForClient(0)
{
}

MockBluetoothDriver::~MockBluetoothDriver()
{
    if( hasMessage() )
        deleteMessageFromDevice();
}

bool MockBluetoothDriver::isDeviceConnected() const
{
    return deviceIsConnected;
}

void MockBluetoothDriver::sendString(const char* message)
{
    if( messageForClient == 0 )
    {
        messageForClient = makeCopyOfStringOnHeap(message);
    }
    else
    {
        // need to combine the strings
        int newStringLength = strlen(messageForClient) + strlen(message) + 1;
        char* combinedStr = new char[newStringLength];
        memset(combinedStr, 0, newStringLength);
        strncpy(combinedStr, messageForClient, strlen(messageForClient));
        strcat(combinedStr, message);

        // delete old string
        delete[] messageForClient;

        // assign new string
        messageForClient = combinedStr;
    }
}

bool MockBluetoothDriver::hasMessage() const
{
    return (messageFromDevice != 0);
}

const char* MockBluetoothDriver::getMessage()
{
    if( hasMessage() )
        return makeCopyOfMessageFromDeviceAndDelete();
    else
        return makeCopyOfStringOnHeap("");
}

bool MockBluetoothDriver::hasMessageForClient() const
{
    return (messageForClient != 0);
}

const char* MockBluetoothDriver::getMessageForClient()
{
    if( hasMessageForClient() )
    {
        const char* returnStr = makeCopyOfStringOnHeap(messageForClient);
        delete[] messageForClient;
        messageForClient = 0;
        return returnStr;
    }
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

char* MockBluetoothDriver::makeCopyOfStringOnHeap(const char* originalStr) const
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

void MockBluetoothDriver::updateMessageFromDevice(const char* message)
{
    if( messageFromDevice == 0 )
    {
        messageFromDevice = makeCopyOfStringOnHeap(message);
    }
    // else
    // {
    //     // need to concatenate the strings together
    //     // new string will be of the form: string1 + '\n' + string2
    //     int newStringLength = strlen(messageFromDevice) + 1 + strlen(message) + 1;
    //     char* combinedStr = new char[newStringLength];
    //     memset(combinedStr, 0, newStringLength);
    //     strncpy(combinedStr, messageFromDevice, strlen(messageFromDevice));
    //     strcat(combinedStr, "\n");
    //     strcat(combinedStr, message);

    //     // delete old string
    //     delete[] messageFromDevice;

    //     // assign new string
    //     messageFromDevice = combinedStr;
    // }
}
