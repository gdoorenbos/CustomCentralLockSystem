#ifndef MOCK_BLUETOOTH_DRIVER_H
#define MOCK_BLUETOOTH_DRIVER_H

#include <BluetoothDriver.h>

class MockBluetoothDriver : public BluetoothDriver
{
public:
    MockBluetoothDriver();
    ~MockBluetoothDriver();

    // client connection
    bool isClientConnected() const;
    void connectClient();
    void disconnectClient();
    
    // messages for client
    void sendString(const char* message);
    bool hasMessageForClient() const;
    const char* getMessageForClient();

    // messages from client
    void sendMessageFromClient(const char* message);
    bool hasMessage() const;
    const char* getMessage();

private:
    // message from client
    void deleteMessageFromClient();
    void updateMessageFromClient(const char* message);
    const char* makeCopyOfMessageFromClientAndDelete();

    // message for client
    void deleteMessageForClient();
    void updateMessageForClient(const char* message);
    void appendToMessageForClient(const char* message);
    const char* makeCopyOfMessageForClientAndDelete();

    // helper methods
    const char* makeCopyOfStringOnHeap(const char* original) const;

    // private members
    bool clientIsConnected;
    const char* messageFromClient;
    const char* messageForClient;
};

#endif
