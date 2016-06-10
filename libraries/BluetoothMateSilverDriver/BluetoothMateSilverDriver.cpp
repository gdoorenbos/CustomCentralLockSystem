#include "BluetoothMateSilverDriver.h"
#include "BluetoothMessageParser.h"
#include <SoftwareSerial.h>
#include "Arduino.h"

BluetoothMateSilverDriver::BluetoothMateSilverDriver(int rxPin, int txPin)
	: _rxPin(rxPin)
	, _txPin(txPin)
	, clientConnected(false)
	, serialIfc(new SoftwareSerial(_rxPin, _txPin))
	, parser(new BluetoothMessageParser())
{
	serialIfc->begin(115200);  // The Bluetooth Mate defaults to 115200bps
	setBaudTo9600();
	serialIfc->begin(9600);  // Start bluetooth serial at 9600

	// eventually we will want to change this so that we can't configure the bluetooth module remotely
	disableCommandTimer();
	// setDeviceName("Batmobile");
}

BluetoothMateSilverDriver::~BluetoothMateSilverDriver()
{
	delete serialIfc;
	delete parser;
}

void BluetoothMateSilverDriver::enterCommandMode()
{
	serialIfc->print("$");  // Print three times individually
	serialIfc->print("$");
	serialIfc->print("$");  // Enter command mode
	delay(100);  // Short delay, wait for the Mate to send back CMD
}

void BluetoothMateSilverDriver::exitCommandMode()
{
	serialIfc->println("---");
}

void BluetoothMateSilverDriver::setBaudTo9600()
{
	enterCommandMode();
	serialIfc->println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
	// 115200 can be too fast at times for NewSoftSerial to relay the data reliably
	exitCommandMode();
}

void BluetoothMateSilverDriver::setDeviceName(const char* name)
{
	enterCommandMode();
	serialIfc->print("SN,");
	serialIfc->println(name);
	exitCommandMode();
}

void BluetoothMateSilverDriver::disableCommandTimer()
{
	// config timer settings on pg. 44
	// 255 disables the config timer
	enterCommandMode();
	serialIfc->println("ST,255");
	exitCommandMode();
}

bool BluetoothMateSilverDriver::isClientConnected()
{
    // return false;
    if( parser->hasMessage() )
    {
    	const char* message = parser->peekMessage();
    	if( strstr(message, "CONNECT") != 0 && strstr(message, "DISCONNECT") == 0 )
    	{
    		clientConnected = true;
    	}
    	else if( strstr(message, "DISCONNECT") != 0 )
    	{
    		clientConnected = false;
    	}
    }
    return clientConnected;
}

void BluetoothMateSilverDriver::sendString(const char* message)
{
	serialIfc->print(message);
}

bool BluetoothMateSilverDriver::hasMessage() const
{
    return parser->hasMessage();
}

const char* BluetoothMateSilverDriver::getMessage()
{
    return parser->getMessage();
}

void BluetoothMateSilverDriver::run()
{
	if( serialIfc->available() )
	{
		parser->giveCharacter(serialIfc->read());
	}
}
