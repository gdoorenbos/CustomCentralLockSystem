#include "BluetoothMateSilverDriver.h"
#include "BluetoothMessageParser.h"
#include "Arduino.h"

/* 
Using the SoftwareSerial library on an ATTiny platform may cause problems. 
The ATTiny84 has 8,192 bytes of program storage, and 512 bytes of SRAM. 
Software Serial takes up 2,270 bytes (28%) of program storage and 112 bytes (22%) of dynamic memory.

This is the current space usage of the BluetoothCentralLockSystem on the ATTiny84:
Sketch uses 6,200 bytes (75%) of program storage space. Maximum is 8,192 bytes.
Global variables use 371 bytes (72%) of dynamic memory, leaving 141 bytes for local variables. Maximum is 512 bytes.

This is very cramped. If there's a smaller library that accomplishes the same thing, it should be used instead.
 */
#include <SoftwareSerial.h>

BluetoothMateSilverDriver::BluetoothMateSilverDriver(int rxPin, int txPin)
	: _rxPin(rxPin)
	, _txPin(txPin)
	, clientConnected(false)
	, serialIfc(new SoftwareSerial(_txPin, _rxPin))
	, parser(new BluetoothMessageParser())
{
    serialIfc->begin(115200);  // The Bluetooth Mate defaults to 115200bps
	setBaudTo9600();
	serialIfc->begin(9600);  // Start bluetooth serial at 9600

	// eventually we will want to change this so that we can't configure the bluetooth module remotely
	// disableCommandTimer();
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
    return parser->isClientConnected();
}

void BluetoothMateSilverDriver::sendString(const char* message)
{
	serialIfc->write(message);
    delay(10);
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
        parser->giveCharacter(serialIfc->read());
}
