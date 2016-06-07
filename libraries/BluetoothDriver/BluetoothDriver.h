#ifndef BLUETOOTH_DRIVER_H
#define BLUETOOTH_DRIVER_H

class BluetoothDriver
{
protected:
    // don't instantiate this class directly
    BluetoothDriver();

public:
	virtual ~BluetoothDriver();
    virtual bool isClientConnected() const = 0;
    virtual void sendString(const char* message) = 0;
    virtual bool hasMessage() const = 0;
    virtual const char* getMessage() = 0;
};

#endif
