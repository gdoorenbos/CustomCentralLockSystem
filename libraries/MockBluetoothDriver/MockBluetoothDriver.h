#ifndef MOCK_BLUETOOTH_DRIVER_H
#define MOCK_BLUETOOTH_DRIVER_H

#include <BluetoothDriver.h>

class MockBluetoothDriver : public BluetoothDriver
{
public:
    MockBluetoothDriver();
    ~MockBluetoothDriver();

    // inherited methods
    bool isDeviceConnected() const;
    void sendString(const char* message);
    bool hasMessage() const;
    const char* getMessage();

    // mock methods
    void connectDevice();
    void disconnectDevice();
    void sendMessageFromDevice(const char* message);
    bool hasMessageForClient() const;
    const char* getMessageForClient();

private:
    void deleteMessageFromDevice();
    char* makeCopyOfMessageFromDeviceAndDelete();

    // DO NOT pass null to these methods 
    char* makeCopyOfStringOnHeap(const char* original) const;
    void updateMessageFromDevice(const char* message);

    bool deviceIsConnected;
    const char* messageFromDevice;
    const char* messageForClient;
};

#endif
