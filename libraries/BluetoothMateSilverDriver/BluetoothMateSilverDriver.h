#ifndef BLUETOOTH_MATE_SILVER_DRIVER_H
#define BLUETOOTH_MATE_SILVER_DRIVER_H

#include <BluetoothDriver.h>

class SoftwareSerial;
class BluetoothMessageParser;

class BluetoothMateSilverDriver : public BluetoothDriver 
{
public:
	BluetoothMateSilverDriver(int rxPin, int txPin);
	~BluetoothMateSilverDriver();

	void run();
    bool isClientConnected();
    void sendString(const char* message);
    bool hasMessage() const;
    const char* getMessage();

private:
	BluetoothMateSilverDriver();	// intentionally not implemented

	// methods
	void enterCommandMode();
	void exitCommandMode();
	void setBaudTo9600();
	void setDeviceName(const char* name);
	void disableCommandTimer();

	// member variables
	const int _txPin;
	const int _rxPin;
	SoftwareSerial* serialIfc;
	BluetoothMessageParser* parser;
	bool clientConnected;
};

#endif
