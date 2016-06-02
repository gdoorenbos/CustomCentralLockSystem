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
    void print(const char* message) const;
    void printLine(const char* message) const;
    bool hasMessage() const;
    const char* getMessage() const;

    // mock methods
    void connectDevice();
    void disconnectDevice();
    void sendMessageFromDevice(const char* message);

private:
    void deleteMessageFromDevice();
    void deleteMessageFromDeviceIfPresent();
    char* makeCopyOfMessageFromDeviceAndDelete();

    // DO NOT pass null to these methods 
    char* makeCopyOfStringOnHeap(char* original);
    void updateMessageFromDevice(char* message);

    bool deviceIsConnected;
    const char* messageFromDevice;
};

#endif
