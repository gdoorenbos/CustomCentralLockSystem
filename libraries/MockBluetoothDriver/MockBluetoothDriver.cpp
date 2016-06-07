#include "MockBluetoothDriver.h"
#include <cstring>

MockBluetoothDriver::MockBluetoothDriver()
    : clientIsConnected(false)
    , messageFromClient(0)
    , messageForClient(0)
{
}

MockBluetoothDriver::~MockBluetoothDriver()
{
    if( hasMessage() )
        deleteMessageFromClient();

    if( hasMessageForClient() )
        deleteMessageForClient();
}

bool MockBluetoothDriver::isClientConnected() const
{
    return clientIsConnected;
}

void MockBluetoothDriver::sendString(const char* message)
{
    if( message != 0 )
        updateMessageForClient(message);
}

bool MockBluetoothDriver::hasMessage() const
{
    return (messageFromClient != 0);
}

const char* MockBluetoothDriver::getMessage()
{
    if( hasMessage() )
        return makeCopyOfMessageFromClientAndDelete();
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
        return makeCopyOfMessageForClientAndDelete();
    else
        return makeCopyOfStringOnHeap("");
}

void MockBluetoothDriver::connectClient()
{
    clientIsConnected = true;
}

void MockBluetoothDriver::disconnectClient()
{
    clientIsConnected = false;
}

void MockBluetoothDriver::sendMessageFromClient(const char* message)
{
    if( message != 0 )
        updateMessageFromClient(message);
}

void MockBluetoothDriver::deleteMessageFromClient()
{
    delete [] messageFromClient;
    messageFromClient = 0;
}

void MockBluetoothDriver::deleteMessageForClient()
{
    delete[] messageForClient;
    messageForClient = 0;
}

const char* MockBluetoothDriver::makeCopyOfStringOnHeap(const char* originalStr) const
{
    char* newStr = new char[strlen(originalStr)+1];
    strncpy(newStr, originalStr, strlen(originalStr)+1);
    return newStr;
}

const char* MockBluetoothDriver::makeCopyOfMessageFromClientAndDelete()
{
    const char* returnStr = makeCopyOfStringOnHeap(messageFromClient);
    deleteMessageFromClient();
    return returnStr;
}

const char* MockBluetoothDriver::makeCopyOfMessageForClientAndDelete()
{
    const char* returnStr = makeCopyOfStringOnHeap(messageForClient);
    deleteMessageForClient();
    return returnStr;
}

void MockBluetoothDriver::updateMessageFromClient(const char* message)
{
    if( messageFromClient == 0 )
        messageFromClient = makeCopyOfStringOnHeap(message);
}

void MockBluetoothDriver::updateMessageForClient(const char* message)
{
    if( messageForClient == 0 )
        messageForClient = makeCopyOfStringOnHeap(message);
    else
        appendToMessageForClient(message);
}

void MockBluetoothDriver::appendToMessageForClient(const char* message)
{
    // create new string for combining
    int combinedStrLength = strlen(messageForClient) + strlen(message) + 1;
    char* combinedStr = new char[combinedStrLength];
    memset(combinedStr, 0, combinedStrLength);
    strncpy(combinedStr, messageForClient, strlen(messageForClient));
    strcat(combinedStr, message);

    // delete old string
    delete[] messageForClient;

    // assign new string
    messageForClient = combinedStr;
}
