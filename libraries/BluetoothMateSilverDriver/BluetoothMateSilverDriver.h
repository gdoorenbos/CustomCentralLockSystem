#ifndef BLUETOOTH_MATE_SILVER_DRIVER_H
#define BLUETOOTH_MATE_SILVER_DRIVER_H

#include <BluetoothDriver.h>

class BluetoothMateSilverDriver : public BluetoothDriver 
{
public:
	BluetoothMateSilverDriver();
	~BluetoothMateSilverDriver();

    bool isClientConnected() const;
    void sendString(const char* message);
    bool hasMessage() const;
    const char* getMessage(); 
};

#endif
