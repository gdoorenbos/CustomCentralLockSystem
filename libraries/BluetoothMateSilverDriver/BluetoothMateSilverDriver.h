#ifndef BLUETOOTH_MATE_SILVER_DRIVER_H
#define BLUETOOTH_MATE_SILVER_DRIVER_H

#include <BluetoothDriver.h>

class BluetoothMateSilverDriver : public BluetoothDriver 
{
public:
	BluetoothMateSilverDriver();
	~BluetoothMateSilverDriver();

    bool isDeviceConnected() const;
    void print(const char* message) const;
    void printLine(const char* message) const;
    bool hasMessage() const;
    const char* getMessage() const; 
};

#endif
