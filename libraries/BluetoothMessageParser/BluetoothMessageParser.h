#ifndef BLUETOOTH_MESSAGE_PARSER
#define BLUETOOTH_MESSAGE_PARSER

/* This class is intended to help BluetoothDrivers build up client messages one character at a time.
 * Separating this logic from the hardware specific BluetoothDriver class makes this unit-testable.
 */
class BluetoothMessageParser
{
public:
	BluetoothMessageParser();
	~BluetoothMessageParser();

	void giveCharacter(const char inputChar);
	bool hasMessage() const;
	const char* getMessage();

private:
	char* finishedMessage;
	char* inputBuffer;
	bool hasMessageFlag;
};

#endif BLUETOOTH_MESSAGE_PARSER
