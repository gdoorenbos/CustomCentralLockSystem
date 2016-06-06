#ifndef BLUETOOTH_DRIVER_H
#define BLUETOOTH_DRIVER_H

class BluetoothDriver
{
protected:
    // don't instantiate this class directly
    BluetoothDriver();

public:
	virtual ~BluetoothDriver();
    virtual bool isDeviceConnected() const = 0;
    virtual void print(const char* message) const = 0;
    virtual void printLine(const char* message) const = 0;
    virtual bool hasMessage() const = 0;
    virtual const char* getMessage() = 0;
};

#endif
