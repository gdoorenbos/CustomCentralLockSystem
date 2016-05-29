#ifndef BLUETOOTH_DRIVER_H
#define BLUETOOTH_DRIVER_H

class BluetoothDriver
{
protected:
    // don't instantiate this class directly
    BluetoothDriver();
    
public:
	virtual ~BluetoothDriver();
    virtual bool isDeviceConnected() = 0;
};

#endif